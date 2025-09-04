#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
双向聊天示例：
- 每个进程既能发，也能收
- 支持消息长度 512
- 自动换行显示
- 每条消息带时间戳
- 区分自己和对方
- 使用ZRDDS Python绑定
"""

import sys
import time
import threading
import textwrap
from datetime import datetime
import os

# 添加模块路径
current_dir = os.path.dirname(os.path.abspath(__file__))
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, build_release_dir)

# 导入ZRDDS Python绑定
import _zrdds_basic as basic
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
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
    
    sys.stdout.flush()

def main():
    """主函数"""
    try:
        print("=== ZRDDS Python 双向聊天示例 ===")
        print("基于ShapeType数据类型的聊天系统")
        print("支持长消息自动换行显示")
        print("=" * 50)
        
        # 获取用户名
        self_name = input("请输入你的名字: ").strip()
        if not self_name:
            self_name = "匿名用户"
        
        print("🚀 启动聊天系统...")
        
        # 导入必要的模块
        import _zrdds_basic
        import _zrdds_domain
        import _zrdds_topic
        import _zrdds_publish
        import _zrdds_listener
        import _zrdds_subscribe
        import _zrdds_shapetype
        
        print("✅ 所有模块导入成功")
        
        # 域号
        domain_id = 80
        topic_name = "CHAT_TOPIC"
        
        # 获取域参与者工厂
        factory = _zrdds_domain.TheParticipantFactory
        if factory is None:
            raise Exception("获取工厂实例失败")
        print("✅ 获取域参与者工厂成功")
        
        # 创建域参与者
        qos = _zrdds_domain.DomainParticipantQos()
        ret = factory.get_default_participant_qos(qos)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认 QoS 失败: {ret}")
            
        participant = factory.create_participant(domain_id, qos, None, 0)
        if participant is None:
            raise Exception("创建域参与者失败")
        print("✅ 创建域参与者成功")
        
        # 注册数据类型
        shapetype_support = _zrdds_shapetype.ShapeTypeTypeSupport.get_instance()
        ret = shapetype_support.register_type(participant, None)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"注册类型失败: {ret}")
        print("✅ 注册 ShapeType 类型成功")
        
        # 创建主题
        topic_qos = _zrdds_domain.TopicQos()
        ret = participant.get_default_topic_qos(topic_qos)
        if ret != _zrdds_basic.RETCODE_OK:
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
        publisher_qos = _zrdds_domain.PublisherQos()
        ret = participant.get_default_publisher_qos(publisher_qos)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认发布者 QoS 失败: {ret}")
            
        publisher = participant.create_publisher(publisher_qos, None, 0)
        if publisher is None:
            raise Exception("创建发布者失败")
        print("✅ 创建发布者成功")
        
        # 创建数据写者
        ret, datawriter_qos = publisher.get_default_datawriter_qos()
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认 DataWriter QoS 失败: {ret}")
            
        datawriter = publisher.create_datawriter(topic, datawriter_qos, None, 0)
        if datawriter is None:
            raise Exception("创建数据写者失败")
        print("✅ 创建数据写者成功")
        
        # 创建订阅者
        subscriber_qos = _zrdds_domain.SubscriberQos()
        ret = participant.get_default_subscriber_qos(subscriber_qos)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认订阅者 QoS 失败: {ret}")
            
        subscriber = participant.create_subscriber(subscriber_qos, None, 0)
        if subscriber is None:
            raise Exception("创建订阅者失败")
        print("✅ 创建订阅者成功")
        
        # 创建数据读者
        ret, datareader_qos = subscriber.get_default_datareader_qos()
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认 DataReader QoS 失败: {ret}")
        
        datareader = subscriber.create_datareader(topic, datareader_qos, None, 0)
        if datareader is None:
            raise Exception("创建数据读者失败")
        print("✅ 创建数据读者成功")
        
        print(f"\n[系统] 欢迎 {self_name}！")
        print("[系统] 输入消息开始聊天，输入 'exit' 退出")
        print("[系统] 支持长消息，会自动换行显示")
        print(f"[系统] 域ID: {domain_id}, 主题: {topic_name}")
        print("-" * 50)
        
        # 主循环
        try:
            while True:
                # 检查是否有新消息
                data = _zrdds_shapetype.ShapeType()
                sample_info = _zrdds_shapetype.SampleInfo()
                
                ret = datareader.read_next_sample(data, sample_info)
                
                if ret == _zrdds_basic.RETCODE_OK and sample_info.valid_data:
                    # 解析消息格式: "名字:消息"
                    message = safe_str(data.z)
                    sep_pos = message.find(':')
                    
                    if sep_pos != -1:
                        sender_name = message[:sep_pos]
                        msg_content = message[sep_pos + 1:]
                        
                        # 只显示对方的消息
                        if sender_name != self_name:
                            print_message(sender_name, msg_content, is_self=False)
                    else:
                        # 没有冒号分隔符，直接显示
                        print_message("未知", message, is_self=False)
                
                # 简单的阻塞输入
                try:
                    user_input = input(f"[{self_name}] 请输入消息: ").strip()
                    
                    if user_input.lower() == 'exit':
                        break
                    
                    if user_input:
                        # 创建数据
                        send_data = _zrdds_shapetype.ShapeType()
                        send_data.x = 0
                        send_data.y = 0
                        # 确保发送时使用UTF-8编码
                        message = f"{self_name}:{user_input}"
                        send_data.z = message.encode("utf-8")[:255]
                        
                        # 发送数据
                        ret = datawriter.write(send_data, _zrdds_domain.HANDLE_NIL_NATIVE)
                        if ret == _zrdds_basic.RETCODE_OK:
                            print_message(self_name, user_input, is_self=True)
                        else:
                            print(f"[错误] 发送消息失败: {ret}")
                
                except EOFError:
                    print("\n[系统] 输入结束，正在退出...")
                    break
                
        except KeyboardInterrupt:
            print("\n⏹️  收到停止信号，开始清理...")
        
        # 清理资源
        print("🧹 清理资源...")
        
        ret = participant.delete_contained_entities()
        if ret != _zrdds_basic.RETCODE_OK:
            print(f"⚠️  删除包含实体失败: {ret}")
            
        ret = factory.delete_participant(participant)
        if ret != _zrdds_basic.RETCODE_OK:
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
