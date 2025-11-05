#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
DDS 性能测试 - 发送端
专门用于发送消息，测试发送性能
"""

import sys
import os
import time
import threading
from datetime import datetime
import queue

# 添加模块路径
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(current_dir)  # 回到project目录
zrpy_dir = os.path.join(parent_dir, 'zrpy')
build_release_dir = os.path.join(parent_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, zrpy_dir)
sys.path.insert(0, build_release_dir)

# 导入DDS模块
import _zrdds_basic as basic
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
import _zrdds_listener as listener
import _zrdds_subscribe as subscribe
import _zrdds_shapetype as shapetype

class DDSSender:
    """DDS发送端"""
    
    def __init__(self, domain_id=80, topic_name="PERF_TEST"):
        self.domain_id = domain_id
        self.topic_name = topic_name
        self.participant = None
        self.publisher = None
        self.datawriter = None
        
        # 发送统计 - 使用线程安全的方式
        self.sent_count = 0
        self.start_time = None
        self.end_time = None
        self.stats_lock = threading.Lock()  # 用于保护统计数据的锁
        
        # 多线程控制
        self.threads = []
        self.stop_event = threading.Event()
        self.message_queue = queue.Queue()
        
    def initialize_dds(self):
        """初始化DDS组件"""
        try:
            print("🚀 初始化DDS发送端...")
            
            # 获取域参与者工厂
            factory = domain.TheParticipantFactory
            if factory is None:
                raise Exception("获取工厂实例失败")
            
            # 创建域参与者
            qos = domain.DomainParticipantQos()
            ret = factory.get_default_participant_qos(qos)
            if ret != basic.RETCODE_OK:
                raise Exception(f"获取默认 QoS 失败: {ret}")
            
            self.participant = factory.create_participant(self.domain_id, qos, None, 0)
            if self.participant is None:
                raise Exception("创建域参与者失败")
            
            # 注册数据类型
            shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
            ret = shapetype_support.register_type(self.participant, None)
            if ret != basic.RETCODE_OK:
                raise Exception(f"注册类型失败: {ret}")
            
            # 创建主题
            topic_qos = domain.TopicQos()
            ret = self.participant.get_default_topic_qos(topic_qos)
            if ret != basic.RETCODE_OK:
                raise Exception(f"获取默认主题 QoS 失败: {ret}")
            
            topic_obj = self.participant.create_topic(
                self.topic_name,
                shapetype_support.get_type_name(),
                topic_qos,
                None,
                0
            )
            if topic_obj is None:
                raise Exception("创建主题失败")
            
            print("✅ DDS发送端初始化成功")
            return topic_obj
            
        except Exception as e:
            print(f"❌ DDS初始化失败: {e}")
            raise
    
    def setup_sender(self, topic_obj):
        """设置发送端"""
        try:
            print("📤 设置发送端...")
            
            # 创建发布者
            publisher_qos = domain.PublisherQos()
            ret = self.participant.get_default_publisher_qos(publisher_qos)
            if ret != basic.RETCODE_OK:
                raise Exception(f"获取默认发布者 QoS 失败: {ret}")
            
            self.publisher = self.participant.create_publisher(publisher_qos, None, 0)
            if self.publisher is None:
                raise Exception("创建发布者失败")
            
            # 创建数据写者
            ret, datawriter_qos = self.publisher.get_default_datawriter_qos()
            if ret != basic.RETCODE_OK:
                raise Exception(f"获取默认 DataWriter QoS 失败: {ret}")
            
            self.datawriter = self.publisher.create_datawriter(topic_obj, datawriter_qos, None, 0)
            if self.datawriter is None:
                raise Exception("创建数据写者失败")
            
            print("✅ 发送端设置完成")
            
        except Exception as e:
            print(f"❌ 发送端设置失败: {e}")
            raise
    
    def _sender_worker(self, thread_id, messages_per_thread, interval):
        """单个发送线程的工作函数"""
        try:
            print(f"🚀 发送线程 {thread_id} 开始工作，将发送 {messages_per_thread} 条消息")
            
            for i in range(messages_per_thread):
                if self.stop_event.is_set():
                    break
                
                # 创建测试数据
                data = shapetype.ShapeType()
                data.x = thread_id * 1000000 + i  # 确保消息ID唯一
                data.y = int(time.time() * 1000) % 1000000  # 时间戳
                data.z = f"Thread-{thread_id} message {i}"
                
                # 发送数据
                ret = self.datawriter.write(data, domain.HANDLE_NIL_NATIVE)
                if ret == basic.RETCODE_OK:
                    with self.stats_lock:
                        self.sent_count += 1
                    
                    if i % 50 == 0 or i < 5:  # 减少打印频率
                        print(f"📤 线程{thread_id}: 已发送 {i+1}/{messages_per_thread} 条消息")
                else:
                    print(f"❌ 线程{thread_id}: 发送消息 {i} 失败: {ret}")
                
                time.sleep(interval)
            
            print(f"✅ 发送线程 {thread_id} 完成工作")
            
        except Exception as e:
            print(f"❌ 发送线程 {thread_id} 出错: {e}")
    
    def send_messages_multithread(self, total_count=100, thread_count=1, interval=0.01):
        """多线程发送消息"""
        print(f"📤 开始多线程发送 {total_count} 条消息...")
        print(f"🧵 使用 {thread_count} 个发送线程")
        print(f"📊 发送间隔: {interval} 秒")
        print(f"📊 预计发送时间: {total_count * interval / thread_count:.1f} 秒")
        print("-" * 50)
        
        self.start_time = time.time()
        self.stop_event.clear()
        
        # 计算每个线程发送的消息数量
        messages_per_thread = total_count // thread_count
        remaining_messages = total_count % thread_count
        
        # 创建并启动发送线程
        for i in range(thread_count):
            # 前几个线程多发送一条消息来处理余数
            thread_message_count = messages_per_thread + (1 if i < remaining_messages else 0)
            
            thread = threading.Thread(
                target=self._sender_worker,
                args=(i, thread_message_count, interval),
                name=f"SenderThread-{i}"
            )
            thread.daemon = True
            self.threads.append(thread)
            thread.start()
        
        # 等待所有线程完成
        for thread in self.threads:
            thread.join()
        
        self.end_time = time.time()
        print("✅ 多线程发送完成")
        self.print_sender_stats()
    
    def send_messages(self, count=100, interval=0.01):
        """发送消息"""
        print(f"📤 开始发送 {count} 条消息...")
        print(f"📊 发送间隔: {interval} 秒")
        print(f"📊 预计发送时间: {count * interval:.1f} 秒")
        print("-" * 50)
        
        self.start_time = time.time()
        
        for i in range(count):
            # 创建测试数据
            data = shapetype.ShapeType()
            data.x = i  # 消息ID
            data.y = int(time.time() * 1000) % 1000000  # 时间戳(毫秒，取模避免溢出)
            data.z = f"Test message {i}"
            
            # 发送数据
            ret = self.datawriter.write(data, domain.HANDLE_NIL_NATIVE)
            if ret == basic.RETCODE_OK:
                self.sent_count += 1
                if i % 100 == 0 or i < 10:
                    print(f"📤 已发送 {i+1}/{count} 条消息")
            else:
                print(f"❌ 发送消息 {i} 失败: {ret}")
            
            time.sleep(interval)
        
        self.end_time = time.time()
        print("✅ 发送完成")
        self.print_sender_stats()
    
    def print_sender_stats(self):
        """打印发送端统计"""
        if not self.start_time or not self.end_time:
            print("❌ 没有发送数据")
            return
        
        duration = self.end_time - self.start_time
        with self.stats_lock:
            total_sent = self.sent_count
        
        throughput = total_sent / duration if duration > 0 else 0
        
        print("\n" + "="*60)
        print("📊 发送端统计")
        print("="*60)
        print(f"发送时长: {duration:.2f} 秒")
        print(f"发送消息: {total_sent} 条")
        print(f"发送频率: {throughput:.2f} 消息/秒")
        if total_sent > 0:
            print(f"平均间隔: {duration/total_sent*1000:.2f} ms/条")
        print(f"活跃线程: {len([t for t in self.threads if t.is_alive()])} 个")
        print("="*60)
    
    def cleanup(self):
        """清理DDS资源"""
        print("🧹 清理发送端资源...")
        
        try:
            # 停止所有发送线程
            self.stop_event.set()
            
            # 等待所有线程结束
            for thread in self.threads:
                if thread.is_alive():
                    thread.join(timeout=5)  # 最多等待5秒
            
            # 清理DDS资源
            if self.participant:
                ret = self.participant.delete_contained_entities()
                if ret != basic.RETCODE_OK:
                    print(f"⚠️ 删除包含实体失败: {ret}")
                
                factory = domain.TheParticipantFactory
                ret = factory.delete_participant(self.participant)
                if ret != basic.RETCODE_OK:
                    print(f"⚠️ 删除域参与者失败: {ret}")
            
            print("✅ 发送端资源清理完成")
            
        except Exception as e:
            print(f"⚠️ 清理资源时出错: {e}")

def main():
    """主函数"""
    print("="*60)
    print("🚀 DDS 性能测试 - 发送端 (支持多线程)")
    print("="*60)
    
    # 获取用户输入
    domain_id = int(input("输入DDS域ID (默认80): ") or "80")
    topic_name = input("输入主题名称 (默认PERF_TEST): ") or "PERF_TEST"
    
    # 选择发送模式
    print("\n选择发送模式:")
    print("1. 单线程发送")
    print("2. 多线程发送")
    mode = input("请选择模式 (1/2, 默认1): ").strip() or "1"
    
    if mode == "2":
        # 多线程模式
        count = int(input("输入总发送消息数量 (默认1000): ") or "1000")
        thread_count = int(input("输入发送线程数量 (默认3): ") or "3")
        interval = float(input("输入发送间隔秒数 (默认0.001): ") or "0.001")
    else:
        # 单线程模式
        count = int(input("输入发送消息数量 (默认100): ") or "100")
        interval = float(input("输入发送间隔秒数 (默认0.01): ") or "0.01")
        thread_count = 1
    
    sender = DDSSender(domain_id, topic_name)
    
    try:
        # 初始化DDS
        topic_obj = sender.initialize_dds()
        
        # 设置发送端
        sender.setup_sender(topic_obj)
        
        print("等待DDS发现完成...")
        time.sleep(3)
        
        # 根据模式发送消息
        if mode == "2":
            sender.send_messages_multithread(count, thread_count, interval)
        else:
            sender.send_messages(count, interval)
        
    except KeyboardInterrupt:
        print("\n⏹️ 发送被中断")
    except Exception as e:
        print(f"❌ 发送失败: {e}")
        import traceback
        traceback.print_exc()
    finally:
        sender.cleanup()

if __name__ == "__main__":
    main()
