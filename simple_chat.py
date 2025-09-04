#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
简化版双向聊天示例
基于您的shape_publisher.py和shape_subscriber.py实现
"""

import sys
import os
import time
import textwrap
from datetime import datetime

# 添加模块路径
current_dir = os.path.dirname(os.path.abspath(__file__))
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, build_release_dir)

# 导入DDS模块
import _zrdds_basic as basic
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
import _zrdds_listener as listener
import _zrdds_subscribe as subscribe
import _zrdds_shapetype as shapetype

def safe_str(s):
    """
    将数据安全转换为字符串，处理DDS字符串字段
    支持UTF-8和系统编码（GBK）的回退机制
    """
    if s is None:
        return "<None>"
    if isinstance(s, str):
        return s
    if isinstance(s, bytes):
        # 去掉末尾的 \x00 填充
        raw = s.rstrip(b"\x00")
        
        # 首先尝试UTF-8解码
        try:
            return raw.decode("utf-8")
        except UnicodeDecodeError:
            # 回退到系统编码（Windows下通常是GBK/CP936）
            try:
                return raw.decode("gbk", errors="ignore")
            except Exception:
                # 最后的回退：使用latin-1（不会失败）
                return raw.decode("latin-1", errors="ignore")
    
    return str(s)

class ChatListener(listener.DataReaderListener):
    """聊天监听器，处理接收到的消息"""
    
    def __init__(self, self_name):
        super().__init__()
        self.self_name = self_name
    
    def on_data_available(self, reader):
        """当有新数据可用时调用"""
        try:
            # 循环读取所有可用的数据样本
            while True:
                data = shapetype.ShapeType()
                sample_info = shapetype.SampleInfo()
                
                # 使用 take_next_sample 方法
                ret = reader.take_next_sample(data, sample_info)
                
                if ret == basic.RETCODE_OK and sample_info.valid_data:
                    # 解析消息格式: "名字:消息"
                    message = safe_str(data.z)
                    sep_pos = message.find(':')
                    
                    if sep_pos != -1:
                        sender_name = message[:sep_pos]
                        msg_content = message[sep_pos + 1:]
                        
                        # 只显示对方的消息，不显示自己的
                        if sender_name != self.self_name:
                            # 先清除当前输入行，然后显示消息
                            print("\r" + " " * 80 + "\r", end="", flush=True)
                            print_message(sender_name, msg_content, is_self=False)
                else:
                    # 没有更多数据了
                    break
                    
        except Exception as e:
            print(f"[错误] 处理接收消息时出错: {e}")

def print_message(sender_name, message, is_self=True):
    """打印消息，支持自动换行"""
    timestamp = datetime.now().strftime("%H:%M:%S")
    
    if is_self:
        prefix = f"[{timestamp}][你] "
    else:
        prefix = f"[{timestamp}][对方 {sender_name}] "
    
    # 自动换行显示
    lines = textwrap.wrap(message, width=80 - len(prefix))
    if not lines:
        lines = [""]
    
    for i, line in enumerate(lines):
        if i == 0:
            print(f"{prefix}{line}")
        else:
            print(f"{' ' * len(prefix)}{line}")
    
    # 确保消息后有换行，避免与输入提示混在一起
    print()
    sys.stdout.flush()

def main():
    try:
        print("=== ZRDDS Python 简化聊天示例 ===")
        print("基于ShapeType数据类型的聊天系统")
        print("=" * 40)
        
        # 获取用户名
        self_name = input("请输入你的名字: ").strip()
        if not self_name:
            self_name = "匿名用户"
        
        print("🚀 启动聊天系统...")

        
        print("✅ 所有模块导入成功")
        
        # 域号
        domain_id = 80
        topic_name = "CHAT_TOPIC"
        
        # 获取域参与者工厂
        factory = domain.TheParticipantFactory
        if factory is None:
            raise Exception("获取工厂实例失败")
        print("✅ 获取域参与者工厂成功")
        
        # 创建域参与者
        qos = domain.DomainParticipantQos()
        ret = factory.get_default_participant_qos(qos)
        if ret != basic.RETCODE_OK:
            raise Exception(f"获取默认 QoS 失败: {ret}")
            
        participant = factory.create_participant(domain_id, qos, None, 0)
        if participant is None:
            raise Exception("创建域参与者失败")
        print("✅ 创建域参与者成功")
        
        # 注册数据类型
        shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
        ret = shapetype_support.register_type(participant, None)
        if ret != basic.RETCODE_OK:
            raise Exception(f"注册类型失败: {ret}")
        print("✅ 注册 ShapeType 类型成功")
        
        # 创建主题
        topic_qos = domain.TopicQos()
        ret = participant.get_default_topic_qos(topic_qos)
        if ret != basic.RETCODE_OK:
            raise Exception(f"获取默认主题 QoS 失败: {ret}")
            
        topic = participant.create_topic(
            topic_name,
            shapetype_support.get_type_name(),
            topic_qos,
            None,
            0
        )
        if topic is None:
            raise Exception("创建主题失败")
        print("✅ 创建主题成功")
        
        # 创建发布者
        publisher_qos = domain.PublisherQos()
        ret = participant.get_default_publisher_qos(publisher_qos)
        if ret != basic.RETCODE_OK:
            raise Exception(f"获取默认发布者 QoS 失败: {ret}")
            
        publisher = participant.create_publisher(publisher_qos, None, 0)
        if publisher is None:
            raise Exception("创建发布者失败")
        print("✅ 创建发布者成功")
        
        # 创建数据写者
        ret, datawriter_qos = publisher.get_default_datawriter_qos()
        if ret != basic.RETCODE_OK:
            raise Exception(f"获取默认 DataWriter QoS 失败: {ret}")
            
        datawriter = publisher.create_datawriter(topic, datawriter_qos, None, 0)
        if datawriter is None:
            raise Exception("创建数据写者失败")
        print("✅ 创建数据写者成功")
        
        # 创建订阅者
        subscriber_qos = domain.SubscriberQos()
        ret = participant.get_default_subscriber_qos(subscriber_qos)
        if ret != basic.RETCODE_OK:
            raise Exception(f"获取默认订阅者 QoS 失败: {ret}")
            
        subscriber = participant.create_subscriber(subscriber_qos, None, 0)
        if subscriber is None:
            raise Exception("创建订阅者失败")
        print("✅ 创建订阅者成功")
        
        # 创建聊天监听器
        chat_listener = ChatListener(self_name)
        
        # 创建数据读者
        ret, datareader_qos = subscriber.get_default_datareader_qos()
        if ret != basic.RETCODE_OK:
            raise Exception(f"获取默认 DataReader QoS 失败: {ret}")
        
        # 使用监听器创建 DataReader
        # 关键修复：使用正确的状态掩码 DATA_AVAILABLE_STATUS = 0x0001 << 10 = 1024
        datareader = subscriber.create_datareader(topic, datareader_qos, chat_listener, 1024)
        if datareader is None:
            raise Exception("创建数据读者失败")
        print("✅ 创建数据读者成功")
        
        print(f"\n[系统] 欢迎 {self_name}！")
        print("[系统] 输入消息开始聊天，输入 'exit' 退出")
        print(f"[系统] 域ID: {domain_id}, 主题: {topic_name}")
        print("-" * 40)
        
        # 等待 DDS 发现完成
        print("[系统] 等待 DDS 发现完成...")
        import time
        time.sleep(2)  # 等待2秒让DDS发现其他参与者
        print("[系统] 开始聊天！")
        
        # 主循环 - 只处理用户输入，消息接收由监听器处理
        try:
            while True:
                # 获取用户输入
                user_input = input(f"[{self_name}] 请输入消息: ").strip()
                
                if user_input.lower() == 'exit':
                    break
                
                if user_input:
                    # 创建数据
                    send_data = shapetype.ShapeType()
                    # 使用用户名作为实例键值，确保每个用户的消息是不同实例
                    send_data.x = hash(self_name) % 1000  # 使用用户名哈希作为x值
                    send_data.y = int(time.time() * 1000) % 1000  # 使用时间戳作为y值
                    # 直接赋值字符串，绑定会自动处理内存管理
                    message = f"{self_name}:{user_input}"
                    send_data.z = message
                    
                    # 发送数据
                    ret = datawriter.write(send_data, domain.HANDLE_NIL_NATIVE)
                    if ret == basic.RETCODE_OK:
                        print_message(self_name, user_input, is_self=True)
                    else:
                        print(f"[错误] 发送消息失败: {ret}")
            
        except EOFError:
            print("\n[系统] 输入结束，正在退出...")
                
        except KeyboardInterrupt:
            print("\n⏹️  收到停止信号，开始清理...")
        
        # 清理资源
        print("🧹 清理资源...")
        
        ret = participant.delete_contained_entities()
        if ret != basic.RETCODE_OK:
            print(f"⚠️  删除包含实体失败: {ret}")
            
        ret = factory.delete_participant(participant)
        if ret != basic.RETCODE_OK:
            print(f"⚠️  删除域参与者失败: {ret}")
            
        print("✅ 聊天系统已关闭")
        
    except Exception as e:
        print(f"❌ 发生异常: {e}")
        import traceback
        traceback.print_exc()
        return 1
    
    return 0

if __name__ == "__main__":
    sys.exit(main())
