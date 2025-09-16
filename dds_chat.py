# -*- coding: utf-8 -*-
# DDS聊天功能模块
import os, sys, time
from PySide6.QtCore import QObject, Signal

# ========== ZRDDS 模块加载 ==========
current_dir = os.path.dirname(os.path.abspath(__file__))
zrpy_dir = os.path.join(current_dir, 'zrpy')
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, zrpy_dir)
sys.path.insert(0, build_release_dir)

import _zrdds_basic as basic
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
import _zrdds_listener as listener
import _zrdds_subscribe as subscribe
import _zrdds_shapetype as shapetype

def safe_str(s):
    """安全字符串转换"""
    if s is None: return "<None>"
    if isinstance(s, str): return s
    if isinstance(s, bytes):
        try: return s.rstrip(b"\x00").decode("utf-8")
        except: return s.rstrip(b"\x00").decode("latin-1", errors="ignore")
    return str(s)

class SignalProxy(QObject):
    """信号代理类，用于跨线程通信"""
    newMessage = Signal(str, str, str)  # topic, sender_name, msg
    userJoined = Signal(str, str)  # topic, username
    userLeft = Signal(str, str)  # topic, username
    newTopicCreated = Signal(str)  # topic_name
    topicDiscovered = Signal(str)  # topic_name
    topicDeleted = Signal(str)  # topic_name

class ChatListener(listener.DataReaderListener):
    """DDS消息监听器"""
    def __init__(self, self_id, proxy: SignalProxy, topic_name, dds_manager=None):
        super().__init__()
        self.self_id = self_id
        self.proxy = proxy
        self.topic_name = topic_name
        self.dds_manager = dds_manager

    def on_data_available(self, reader):
        """当有数据可用时调用"""
        try:
            print(f"[调试] 收到数据，主题: {self.topic_name}")
            while True:
                data = shapetype.ShapeType()
                sample_info = shapetype.SampleInfo()
                ret = reader.read_next_sample(data, sample_info)
                if ret == basic.RETCODE_OK and sample_info.valid_data:
                    sender_id = data.x
                    msg_content = safe_str(data.z)
                    print(f"[调试] 收到消息: 发送者ID={sender_id}, 自己ID={self.self_id}, 内容={msg_content}")
                    
                    if sender_id != self.self_id:
                        # 解析用户名和消息内容
                        if "|" in msg_content:
                            parts = msg_content.split("|", 1)
                            sender_name = parts[0]
                            actual_message = parts[1]
                        else:
                            # 兼容旧格式，如果没有分隔符则使用用户ID
                            sender_name = f"用户{sender_id}"
                            actual_message = msg_content
                        
                        # 检查是否是上线消息
                        if sender_name == "ONLINE":
                            print(f"[调试] 收到上线消息: {actual_message}")
                            # 处理用户上线，不转发为普通消息
                            if self.dds_manager:
                                self.dds_manager.check_and_handle_user_join(self.topic_name, sender_id, actual_message)
                                # 当有新用户上线时，向该用户发送我们的在线状态
                                self.dds_manager.send_user_discovery_message(self.topic_name)
                        elif sender_name == "DISCOVERY":
                            print(f"[调试] 收到用户发现消息: {actual_message}")
                            # 处理用户发现消息，不转发为普通消息
                            if self.dds_manager:
                                # DISCOVERY消息也用于处理用户加入，确保用户可见
                                self.dds_manager.check_and_handle_user_join(self.topic_name, sender_id, actual_message)
                        elif sender_name == "OFFLINE":
                            print(f"[调试] 收到离线消息: {actual_message}")
                            # 处理用户离线，不转发为普通消息
                            if self.dds_manager:
                                self.dds_manager.handle_user_leave(self.topic_name, actual_message)
                        elif sender_name == "TOPIC_DELETED":
                            print(f"[调试] 收到主题删除消息: {actual_message}")
                            # 处理主题删除，不转发为普通消息
                            if self.dds_manager:
                                self.dds_manager.handle_topic_deleted(actual_message)
                        elif sender_name == "NEW_TOPIC":
                            print(f"[调试] 收到新主题创建消息: {actual_message}")
                            # 处理新主题创建消息，不转发为普通消息
                            if self.dds_manager:
                                # 自动为新主题创建发布者和订阅者
                                self.dds_manager._create_topic_publisher_subscriber(actual_message)
                                # 将当前用户添加到新主题的在线用户列表
                                if actual_message not in self.dds_manager.online_users:
                                    self.dds_manager.online_users[actual_message] = set()
                                self.dds_manager.online_users[actual_message].add(self.dds_manager.username)
                                # 发送自己的在线状态到新主题
                                self.dds_manager.send_online_message(actual_message)
                                # 通知UI
                                self.proxy.newTopicCreated.emit(actual_message)
                        elif sender_name == "TOPIC_DISCOVERY_REQUEST":
                            print(f"[调试] 收到主题发现请求: {actual_message}")
                            # 处理主题发现请求，不转发为普通消息
                            if self.dds_manager:
                                self.dds_manager.handle_topic_discovery_request(actual_message)
                        elif sender_name == "TOPIC_DISCOVERY_RESPONSE":
                            print(f"[调试] 收到主题发现响应: {actual_message}")
                            # 处理主题发现响应，不转发为普通消息
                            if self.dds_manager:
                                # 从发送者ID获取用户名（这里简化处理，实际应该维护ID到用户名的映射）
                                sender_username = f"user_{sender_id}"  # 临时方案
                                self.dds_manager.handle_topic_discovery_response(actual_message, sender_username)
                        else:
                            # 检查是否为新用户（普通消息）
                            if self.dds_manager:
                                self.dds_manager.check_and_handle_user_join(self.topic_name, sender_id, sender_name)
                            
                            print(f"[调试] 转发消息到UI: {self.topic_name} - {sender_name} - {actual_message}")
                            self.proxy.newMessage.emit(self.topic_name, sender_name, actual_message)
                    else:
                        print(f"[调试] 忽略自己的消息")
                else:
                    break
        except Exception as e:
            print(f"[错误] 接收消息出错: {e}")
            import traceback
            traceback.print_exc()

class DDSChatManager:
    """DDS聊天管理器"""
    
    def __init__(self, username, user_id):
        self.username = username
        self.user_id = user_id
        self.participant = None
        self.writers = {}
        self.listeners = {}
        self.proxy = SignalProxy()
        self.online_users = {}  # 存储每个主题的在线用户 {topic: {username}}
        self.discovered_topics = set()  # 存储发现的主题
        self.topic_creators = {}  # 存储主题创建者 {topic: username}
        
    def initialize_dds(self):
        """初始化DDS系统"""
        try:
            factory = domain.TheParticipantFactory
            qos = domain.DomainParticipantQos()
            factory.get_default_participant_qos(qos)
            self.participant = factory.create_participant(80, qos, None, 0)

            shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
            shapetype_support.register_type(self.participant, None)

            # 每个主题分别创建 publisher & subscriber
            topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3", "SHARED_CANVAS_TOPIC"]
            for topic_name in topics:
                self._create_topic_publisher_subscriber(topic_name)

            print(f"[调试] DDS初始化成功，用户名: {self.username}, 用户ID: {self.user_id}")
            
            # 初始化在线用户列表
            topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3", "SHARED_CANVAS_TOPIC"]
            for topic_name in topics:
                self.online_users[topic_name] = set()
                # 将自己添加到在线用户列表
                self.online_users[topic_name].add(self.username)
                
                # 发送上线消息，让其他用户知道我们加入了
                self.send_online_message(topic_name)
                
                # 发送用户发现消息，主动发现其他在线用户
                self.send_user_discovery_message(topic_name)
            
            # 延迟发送额外的发现消息，确保跨网络延迟情况下的可见性
            import threading
            def delayed_discovery():
                import time
                time.sleep(0.5)  # 延迟500毫秒
                for topic_name in topics:
                    self.send_user_discovery_message(topic_name)
                time.sleep(1.0)  # 再延迟1秒
                for topic_name in topics:
                    self.send_user_discovery_message(topic_name)
            
            threading.Thread(target=delayed_discovery, daemon=True).start()
            
            return True
            
        except Exception as e:
            print(f"DDS 初始化失败: {e}")
            return False

    def _create_topic_publisher_subscriber(self, topic_name):
        """为指定主题创建发布者和订阅者"""
        try:
            # 创建主题
            topic_qos = domain.TopicQos()
            self.participant.get_default_topic_qos(topic_qos)
            shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
            topic_obj = self.participant.create_topic(topic_name, shapetype_support.get_type_name(), topic_qos, None, 0)

            # 创建发布者
            pub_qos = domain.PublisherQos()
            self.participant.get_default_publisher_qos(pub_qos)
            publisher = self.participant.create_publisher(pub_qos, None, 0)

            ret, dw_qos = publisher.get_default_datawriter_qos()
            writer = publisher.create_datawriter(topic_obj, dw_qos, None, 0)
            self.writers[topic_name] = writer

            # 创建订阅者
            sub_qos = domain.SubscriberQos()
            self.participant.get_default_subscriber_qos(sub_qos)
            subscriber = self.participant.create_subscriber(sub_qos, None, 0)

            listener_obj = ChatListener(self.user_id, self.proxy, topic_name, self)
            ret, dr_qos = subscriber.get_default_datareader_qos()
            datareader = subscriber.create_datareader(topic_obj, dr_qos, listener_obj, 1024)
            print(f"[调试] 创建数据读取器成功，主题: {topic_name}")
            self.listeners[topic_name] = listener_obj
            
        except Exception as e:
            print(f"[错误] 创建主题 {topic_name} 失败: {e}")
            raise

    def send_online_message(self, topic):
        """发送上线消息"""
        try:
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = 888  # 特殊标识，表示上线消息
            send_data.z = f"ONLINE|{self.username}"
            
            writer = self.writers.get(topic)
            if writer:
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 发送上线消息: {topic} - {self.username}")
        except Exception as e:
            print(f"[错误] 发送上线消息失败: {e}")

    def send_user_discovery_message(self, topic):
        """发送用户发现消息，让新用户知道我们在线"""
        try:
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = 889  # 特殊标识，表示用户发现消息
            send_data.z = f"DISCOVERY|{self.username}"
            
            writer = self.writers.get(topic)
            if writer:
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 发送用户发现消息: {topic} - {self.username}")
        except Exception as e:
            print(f"[错误] 发送用户发现消息失败: {e}")

    def send_message(self, topic, message):
        """发送消息到指定主题"""
        try:
            if len(message) > 512: 
                message = message[:512]
                
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = int(time.time() * 1000) % 1000
            # 将用户名和消息内容组合发送
            combined_message = f"{self.username}|{message}"
            send_data.z = combined_message
            
            writer = self.writers.get(topic)
            if writer:
                ret = writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                if ret == basic.RETCODE_OK:
                    print(f"[调试] 消息发送成功: {topic} - {message}")
                    # 发送成功后立即显示自己的消息
                    self.proxy.newMessage.emit(topic, self.username, message)
                    return True
                else:
                    print(f"消息发送失败: {ret}")
                    return False
            else:
                print(f"找不到主题 {topic} 的写入器")
                return False
                
        except Exception as e:
            print(f"DDS 写入异常: {e}")
            import traceback
            traceback.print_exc()
            return False

    
    def check_and_handle_user_join(self, topic, user_id, username):
        """检查并处理用户加入"""
        if user_id != self.user_id:  # 不是自己
            if topic not in self.online_users:
                self.online_users[topic] = set()
            if username not in self.online_users[topic]:
                self.online_users[topic].add(username)
                print(f"[调试] 用户加入: {username} 加入 {topic}")
                self.proxy.userJoined.emit(topic, username)
                
                # 主动发送发现消息，确保新用户能看到我们
                self.send_user_discovery_message(topic)
    
    def handle_user_join(self, topic, user_id, username):
        """处理用户加入（与check_and_handle_user_join相同）"""
        self.check_and_handle_user_join(topic, user_id, username)
    
    def handle_user_leave(self, topic, username):
        """处理用户离开"""
        if topic in self.online_users and username in self.online_users[topic]:
            self.online_users[topic].remove(username)
            print(f"[调试] 用户离开: {username} 离开 {topic}")
            self.proxy.userLeft.emit(topic, username)
            
            # 不立即检查域状态，只在程序退出时检查
            print(f"[调试] 用户 {username} 已离开，不检查域状态")
            
    
    def check_domain_status(self):
        """检查域状态：如果域中没有其他用户了，删除所有创建的主题"""
        try:
            # 防止重复调用
            if not hasattr(self, '_domain_check_in_progress'):
                self._domain_check_in_progress = False
            
            if self._domain_check_in_progress:
                print(f"[调试] 域状态检查正在进行中，跳过重复调用")
                return
                
            self._domain_check_in_progress = True
            
            # 收集所有主题中的所有用户（除了自己）
            all_other_users = set()
            print(f"[调试] 开始检查域状态，当前在线用户状态:")
            for topic, users in self.online_users.items():
                other_users = users - {self.username}
                all_other_users.update(other_users)
                print(f"[调试] 主题 '{topic}': {users} (其他用户: {other_users})")
            
            print(f"[调试] 域中所有其他用户: {all_other_users}")
            
            # 如果整个域中没有任何其他用户，则域为空
            if len(all_other_users) == 0:
                print(f"[调试] 检测到域已空，删除所有创建的主题")
                self.delete_all_created_topics()
            else:
                print(f"[调试] 域中还有其他用户: {all_other_users}，不删除主题")
            
            # 重置标志
            self._domain_check_in_progress = False
                
        except Exception as e:
            print(f"[错误] 检查域状态失败: {e}")
            import traceback
            traceback.print_exc()
            # 确保在异常情况下也重置标志
            self._domain_check_in_progress = False
    
    def handle_topic_deleted(self, topic_name):
        """处理主题删除"""
        if topic_name in self.discovered_topics:
            self.discovered_topics.remove(topic_name)
            print(f"[调试] 主题删除: {topic_name}")
            # 通知UI主题被删除
            self.proxy.topicDeleted.emit(topic_name)
    
    def send_topic_deleted_message(self, topic_name):
        """发送主题删除消息"""
        try:
            # 向所有现有主题发送主题删除通知
            for target_topic in self.writers.keys():
                if target_topic != topic_name:  # 不向被删除的主题发送
                    writer = self.writers[target_topic]
                    send_data = shapetype.ShapeType()
                    send_data.x = self.user_id
                    send_data.y = 894  # 特殊标识，表示主题删除消息
                    send_data.z = f"TOPIC_DELETED|{topic_name}"
                    writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                    print(f"[调试] 发送主题删除消息: {target_topic} - {topic_name}")
        except Exception as e:
            print(f"[错误] 发送主题删除消息失败: {e}")
    
    def delete_topic(self, topic_name):
        """删除主题（只有创建者才能删除）"""
        try:
            print(f"[调试] 尝试删除主题: {topic_name}")
            
            # 检查是否是主题创建者
            if topic_name not in self.topic_creators:
                print(f"[错误] 主题 '{topic_name}' 不存在或未创建")
                return False
            
            if self.topic_creators[topic_name] != self.username:
                print(f"[错误] 只有主题创建者 '{self.topic_creators[topic_name]}' 才能删除主题 '{topic_name}'")
                return False
            
            print(f"[调试] 用户 '{self.username}' 是主题 '{topic_name}' 的创建者，允许删除")
            
            # 发送主题删除通知
            self.send_topic_deleted_message(topic_name)
            
            # 从发现的主题列表中移除
            if topic_name in self.discovered_topics:
                self.discovered_topics.remove(topic_name)
            
            # 从在线用户列表中移除
            if topic_name in self.online_users:
                del self.online_users[topic_name]
            
            # 从创建者列表中移除
            del self.topic_creators[topic_name]
            
            # 清理DDS资源
            if topic_name in self.writers:
                del self.writers[topic_name]
            if topic_name in self.listeners:
                del self.listeners[topic_name]
            
            print(f"[调试] 主题 '{topic_name}' 删除成功")
            return True
            
        except Exception as e:
            print(f"[错误] 删除主题失败: {e}")
            return False
    
    def auto_delete_topic(self, topic_name):
        """自动删除主题（当主题无在线用户时）"""
        try:
            print(f"[调试] 自动删除主题: {topic_name}")
            
            # 发送主题删除通知
            self.send_topic_deleted_message(topic_name)
            
            # 执行删除操作
            self._perform_topic_deletion(topic_name)
            
            print(f"[调试] 主题 '{topic_name}' 自动删除成功")
            return True
            
        except Exception as e:
            print(f"[错误] 自动删除主题失败: {e}")
            return False
    
    def _perform_topic_deletion(self, topic_name):
        """执行主题删除的通用操作"""
        # 从发现的主题列表中移除
        if topic_name in self.discovered_topics:
            self.discovered_topics.remove(topic_name)
        
        # 从在线用户列表中移除
        if topic_name in self.online_users:
            del self.online_users[topic_name]
        
        # 从主题创建者列表中移除
        if topic_name in self.topic_creators:
            del self.topic_creators[topic_name]
        
        # 清理DDS资源
        if topic_name in self.writers:
            del self.writers[topic_name]
        if topic_name in self.listeners:
            del self.listeners[topic_name]
        
        # 通知UI主题被删除
        self.proxy.topicDeleted.emit(topic_name)
    

    def get_online_users(self, topic):
        """获取指定主题的在线用户列表"""
        return self.online_users.get(topic, set())
    
    def get_discovered_topics(self):
        """获取已发现的主题列表"""
        return list(self.discovered_topics)
    
    def send_topic_announcement(self, target_topic, new_topic_name):
        """发送新主题通知"""
        try:
            print(f"[调试] 发送新主题通知: {target_topic} -> {new_topic_name}")
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = 890  # 特殊标识，表示新主题创建消息
            send_data.z = f"NEW_TOPIC|{new_topic_name}"
            
            writer = self.writers.get(target_topic)
            if writer:
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 新主题通知发送成功: {target_topic}")
        except Exception as e:
            print(f"[错误] 发送新主题通知失败: {e}")
    
    def create_new_topic(self, topic_name):
        """创建新主题"""
        try:
            print(f"[调试] DDS创建新主题: {topic_name}")
            
            # 为新主题创建发布者和订阅者（和预定义主题完全一样）
            self._create_topic_publisher_subscriber(topic_name)
            
            # 初始化新主题的在线用户列表（和预定义主题完全一样）
            self.online_users[topic_name] = set()
            self.online_users[topic_name].add(self.username)
            
            # 记录主题创建者
            self.topic_creators[topic_name] = self.username
            print(f"[调试] 记录主题创建者: '{topic_name}' -> '{self.username}'")
            
            # 发送上线消息到新主题（和预定义主题完全一样）
            self.send_online_message(topic_name)
            
            # 向所有现有主题发送用户发现消息，确保其他用户能快速发现我们
            existing_topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
            for existing_topic in existing_topics:
                if existing_topic in self.writers:
                    self.send_user_discovery_message(existing_topic)
            
            print(f"[调试] 新主题 '{topic_name}' DDS创建成功")
            return True
            
        except Exception as e:
            print(f"[错误] DDS创建新主题失败: {e}")
            import traceback
            traceback.print_exc()
            return False
    
    def send_topic_creation_message(self, target_topic, new_topic_name):
        """发送新主题创建消息"""
        try:
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = 890  # 特殊标识，表示新主题创建消息
            send_data.z = f"NEW_TOPIC|{new_topic_name}"
            
            writer = self.writers.get(target_topic)
            if writer:
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 发送新主题创建消息: {target_topic} - {new_topic_name}")
        except Exception as e:
            print(f"[错误] 发送新主题创建消息失败: {e}")

    def request_topic_discovery(self):
        """请求主题发现"""
        try:
            print(f"[调试] 请求主题发现")
            
            # 向所有现有主题发送主题发现请求
            existing_topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
            for topic in existing_topics:
                if topic in self.writers:
                    self.send_topic_discovery_request(topic)
        except Exception as e:
            print(f"[错误] 请求主题发现失败: {e}")

    def send_topic_discovery_request(self, target_topic):
        """发送主题发现请求"""
        try:
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = 891  # 特殊标识，表示主题发现请求
            send_data.z = f"TOPIC_DISCOVERY_REQUEST|{self.username}"
            
            writer = self.writers.get(target_topic)
            if writer:
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 发送主题发现请求: {target_topic}")
        except Exception as e:
            print(f"[错误] 发送主题发现请求失败: {e}")

    def send_topic_discovery_response(self, target_topic, topic_list):
        """发送主题发现响应"""
        try:
            # 将主题列表转换为字符串
            topics_str = ",".join(topic_list)
            send_data = shapetype.ShapeType()
            send_data.x = self.user_id
            send_data.y = 892  # 特殊标识，表示主题发现响应
            send_data.z = f"TOPIC_DISCOVERY_RESPONSE|{topics_str}"
            
            writer = self.writers.get(target_topic)
            if writer:
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 发送主题发现响应: {target_topic} - {topics_str}")
        except Exception as e:
            print(f"[错误] 发送主题发现响应失败: {e}")

    def handle_topic_discovery_request(self, requester_username):
        """处理主题发现请求"""
        try:
            print(f"[调试] 处理主题发现请求，来自: {requester_username}")
            
            # 获取我们创建的所有主题
            our_topics = []
            for topic_name in self.writers.keys():
                if topic_name not in ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]:
                    our_topics.append(topic_name)
            
            if our_topics:
                # 向请求者发送主题列表
                # 这里简化处理，向所有现有主题发送响应
                existing_topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
                for topic in existing_topics:
                    if topic in self.writers:
                        self.send_topic_discovery_response(topic, our_topics)
        except Exception as e:
            print(f"[错误] 处理主题发现请求失败: {e}")

    def handle_topic_discovery_response(self, topics_str, sender_username=None):
        """处理主题发现响应"""
        try:
            print(f"[调试] 处理主题发现响应: {topics_str}")
            
            # 解析主题列表
            if topics_str:
                topics = topics_str.split(",")
                for topic_name in topics:
                    topic_name = topic_name.strip()
                    if topic_name and topic_name not in self.writers and topic_name not in self.discovered_topics:
                        print(f"[调试] 发现新主题: {topic_name}")
                        self.discovered_topics.add(topic_name)
                        
                        # 记录主题创建者（如果提供了发送者信息）
                        if sender_username:
                            self.topic_creators[topic_name] = sender_username
                            print(f"[调试] 记录主题创建者: '{topic_name}' -> '{sender_username}'")
                        
                        self.proxy.topicDiscovered.emit(topic_name)
        except Exception as e:
            print(f"[错误] 处理主题发现响应失败: {e}")

    def subscribe_to_topic(self, topic_name):
        """订阅主题"""
        try:
            print(f"[调试] 订阅主题: {topic_name}")
            
            # 如果主题不存在，创建它
            if topic_name not in self.writers:
                self._create_topic_publisher_subscriber(topic_name)
                
                # 初始化新主题的在线用户列表
                self.online_users[topic_name] = set()
                self.online_users[topic_name].add(self.username)
            
            # 无论主题是否存在，都发送上线消息，确保其他用户能发现我们
            self.send_online_message(topic_name)
            
            # 发送用户发现消息到新主题，确保其他用户能快速发现我们
            self.send_user_discovery_message(topic_name)
            
            # 同时向所有预定义主题发送发现消息，确保主题创建者能发现我们
            predefined_topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
            for topic in predefined_topics:
                if topic in self.writers:
                    self.send_user_discovery_message(topic)
            
            # 延迟发送额外的发现消息，确保跨网络延迟情况下的可见性
            import threading
            def delayed_subscription_discovery():
                import time
                time.sleep(0.3)  # 延迟300毫秒
                self.send_online_message(topic_name)
                self.send_user_discovery_message(topic_name)
                for topic in predefined_topics:
                    if topic in self.writers:
                        self.send_user_discovery_message(topic)
                time.sleep(0.7)  # 再延迟700毫秒
                self.send_user_discovery_message(topic_name)
            
            threading.Thread(target=delayed_subscription_discovery, daemon=True).start()
            
            print(f"[调试] 主题 '{topic_name}' 订阅成功")
            return True
            
        except Exception as e:
            print(f"[错误] 订阅主题失败: {e}")
            import traceback
            traceback.print_exc()
            return False
    
    def get_signal_proxy(self):
        """获取信号代理对象"""
        return self.proxy

    def send_offline_message(self, topic):
        """发送离线消息"""
        try:
            if topic in self.writers:
                writer = self.writers[topic]
                send_data = shapetype.ShapeType()
                send_data.x = self.user_id
                send_data.y = 893  # 特殊标识，表示离线消息
                send_data.z = f"OFFLINE|{self.username}"
                writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                print(f"[调试] 发送离线消息: {topic} - {self.username}")
        except Exception as e:
            print(f"[错误] 发送离线消息失败: {e}")
    
    def send_offline_to_all_topics(self):
        """向所有主题发送离线消息"""
        try:
            print(f"[调试] 向所有主题发送离线消息")
            for topic in list(self.writers.keys()):
                self.send_offline_message(topic)
            print(f"[调试] 离线消息发送完成")
        except Exception as e:
            print(f"[错误] 向所有主题发送离线消息失败: {e}")

    
    def delete_all_created_topics(self):
        """删除所有创建的主题"""
        try:
            # 获取所有创建的主题（排除预定义主题）
            predefined_topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3", "多功能聊天室"]
            created_topics = []
            
            # 从所有主题中找出非预定义的主题
            for topic_name in list(self.writers.keys()):
                if topic_name not in predefined_topics:
                    created_topics.append(topic_name)
            
            print(f"[调试] 准备删除所有创建的主题: {created_topics}")
            
            # 删除每个创建的主题
            for topic_name in created_topics:
                print(f"[调试] 删除创建主题: {topic_name}")
                self._perform_topic_deletion(topic_name)
            
            print(f"[调试] 所有创建主题删除完成")
            
        except Exception as e:
            print(f"[错误] 删除创建主题失败: {e}")
            import traceback
            traceback.print_exc()

    def cleanup(self):
        """清理DDS资源"""
        try:
            # 发送离线消息到所有主题
            self.send_offline_to_all_topics()
            
            # 检查域状态：如果域中没有其他用户了，删除所有创建的主题
            self.check_domain_status()
            
            if self.participant:
                # 这里可以添加更详细的清理逻辑
                print("[调试] DDS资源清理完成")
        except Exception as e:
            print(f"[错误] DDS资源清理失败: {e}")
