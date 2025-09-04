#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
测试DDS双向通信
"""

import os
import sys
import time
import threading
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
import _zrdds_subscribe as subscribe
import _zrdds_shapetype as shapetype

def test_sender(name, duration=10):
    """发送者线程"""
    print(f"[{name}] 启动发送者...")
    
    try:
        # 创建域参与者
        factory = domain.DomainParticipantFactory.get_instance()
        qos = domain.DomainParticipantQos()
        participant = factory.create_participant(80, qos)
        
        # 注册类型
        type_support = shapetype.ShapeTypeTypeSupport.get_instance()
        type_support.register_type(participant, "ShapeType")
        
        # 创建主题
        topic_obj = participant.create_topic("TEST_TOPIC", "ShapeType", topic.Topic.get_default_qos())
        
        # 创建发布者
        publisher = participant.create_publisher(publish.Publisher.get_default_qos())
        
        # 创建数据写者
        datawriter = publisher.create_datawriter(topic_obj, publish.DataWriter.get_default_qos())
        
        # 发送消息
        start_time = time.time()
        counter = 0
        
        while time.time() - start_time < duration:
            # 创建数据
            send_data = shapetype.ShapeType()
            send_data.x = counter
            send_data.y = counter
            send_data.z = f"{name}:消息{counter}"
            
            # 发送
            ret = datawriter.write(send_data, domain.HANDLE_NIL_NATIVE)
            if ret == basic.RETCODE_OK:
                print(f"[{name}] 发送: {send_data.z}")
            else:
                print(f"[{name}] 发送失败: {ret}")
            
            counter += 1
            time.sleep(1)
        
        print(f"[{name}] 发送者完成")
        
    except Exception as e:
        print(f"[{name}] 发送者错误: {e}")

def test_receiver(name, duration=10):
    """接收者线程"""
    print(f"[{name}] 启动接收者...")
    
    try:
        # 创建域参与者
        factory = domain.DomainParticipantFactory.get_instance()
        qos = domain.DomainParticipantQos()
        participant = factory.create_participant(80, qos)
        
        # 注册类型
        type_support = shapetype.ShapeTypeTypeSupport.get_instance()
        type_support.register_type(participant, "ShapeType")
        
        # 创建主题
        topic_obj = participant.create_topic("TEST_TOPIC", "ShapeType", topic.Topic.get_default_qos())
        
        # 创建订阅者
        subscriber = participant.create_subscriber(subscribe.Subscriber.get_default_qos())
        
        # 创建数据读者
        datareader = subscriber.create_datareader(topic_obj, subscribe.DataReader.get_default_qos())
        
        # 接收消息
        start_time = time.time()
        
        while time.time() - start_time < duration:
            # 创建数据对象
            data = shapetype.ShapeType()
            sample_info = shapetype.SampleInfo()
            
            # 读取数据
            ret = datareader.read_next_sample(data, sample_info)
            
            if ret == basic.RETCODE_OK and sample_info.valid_data:
                print(f"[{name}] 接收: {data.z}")
            
            time.sleep(0.1)
        
        print(f"[{name}] 接收者完成")
        
    except Exception as e:
        print(f"[{name}] 接收者错误: {e}")

def main():
    print("=== DDS双向通信测试 ===")
    print("测试10秒...")
    
    # 创建发送者和接收者线程
    sender_thread = threading.Thread(target=test_sender, args=("发送者", 10))
    receiver_thread = threading.Thread(target=test_receiver, args=("接收者", 10))
    
    # 启动线程
    sender_thread.start()
    receiver_thread.start()
    
    # 等待完成
    sender_thread.join()
    receiver_thread.join()
    
    print("测试完成！")

if __name__ == "__main__":
    main()
