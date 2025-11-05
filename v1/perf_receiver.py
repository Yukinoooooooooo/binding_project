#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
DDS 性能测试 - 接收端
专门用于接收消息，测试接收性能和延迟
"""

import sys
import os
import time
import statistics
from datetime import datetime

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

class DDSReceiver:
    """DDS接收端"""
    
    def __init__(self, domain_id=80, topic_name="PERF_TEST"):
        self.domain_id = domain_id
        self.topic_name = topic_name
        self.participant = None
        self.subscriber = None
        self.datareader = None
        
        # 接收统计
        self.received_count = 0
        self.latencies = []
        self.message_times = []
        self.start_time = None
        self.end_time = None
        self.last_message_time = None  # 最后一条消息的接收时间
        self.expected_count = 0
        
    def initialize_dds(self):
        """初始化DDS组件"""
        try:
            print("🚀 初始化DDS接收端...")
            
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
            
            print("✅ DDS接收端初始化成功")
            return topic_obj
            
        except Exception as e:
            print(f"❌ DDS初始化失败: {e}")
            raise
    
    def setup_receiver(self, topic_obj):
        """设置接收端"""
        try:
            print("📥 设置接收端...")
            
            # 创建订阅者
            subscriber_qos = domain.SubscriberQos()
            ret = self.participant.get_default_subscriber_qos(subscriber_qos)
            if ret != basic.RETCODE_OK:
                raise Exception(f"获取默认订阅者 QoS 失败: {ret}")
            
            self.subscriber = self.participant.create_subscriber(subscriber_qos, None, 0)
            if self.subscriber is None:
                raise Exception("创建订阅者失败")
            
            # 创建数据读者
            ret, datareader_qos = self.subscriber.get_default_datareader_qos()
            if ret != basic.RETCODE_OK:
                raise Exception(f"获取默认 DataReader QoS 失败: {ret}")
            
            self.datareader = self.subscriber.create_datareader(topic_obj, datareader_qos, None, 0)
            if self.datareader is None:
                raise Exception("创建数据读者失败")
            
            print("✅ 接收端设置完成")
            
        except Exception as e:
            print(f"❌ 接收端设置失败: {e}")
            raise
    
    def receive_messages(self, expected_count=100, timeout=60):
        """接收消息"""
        print(f"📥 开始接收消息，期望接收 {expected_count} 条...")
        print(f"⏰ 接收超时时间: {timeout} 秒")
        print("-" * 50)
        
        self.expected_count = expected_count
        self.start_time = None  # 将在接收到第一条消息时设置
        end_time = time.time() + timeout
        
        while self.received_count < expected_count and time.time() < end_time:
            # 读取数据
            data = shapetype.ShapeType()
            sample_info = shapetype.SampleInfo()
            
            ret = self.datareader.read_next_sample(data, sample_info)
            
            if ret == basic.RETCODE_OK and sample_info.valid_data:
                # 记录当前消息接收时间
                current_time = time.time()
                
                # 如果是第一条消息，设置开始时间
                if self.start_time is None:
                    self.start_time = current_time
                    print(f"📥 开始接收消息，第一条消息到达")
                
                # 更新最后一条消息的接收时间
                self.last_message_time = current_time
                
                # 计算延迟 - 使用消息接收时间作为延迟
                # 由于时间戳取模运算会影响精度，我们使用接收间隔作为延迟参考
                if len(self.message_times) > 0:
                    # 计算与上一条消息的接收间隔作为延迟参考
                    last_receive_time = self.message_times[-1]
                    latency = (current_time - last_receive_time) * 1000  # 转换为毫秒
                else:
                    # 第一条消息，延迟为0
                    latency = 0
                
                # 记录延迟（限制在合理范围内）
                if 0 <= latency <= 1000:
                    self.latencies.append(latency)
                
                self.message_times.append(current_time)
                self.received_count += 1
                
                if self.received_count % 50 == 0 or self.received_count < 10:
                    print(f"📥 已接收 {self.received_count}/{expected_count} 条消息 (间隔: {latency:.1f}ms)")
            else:
                time.sleep(0.001)  # 短暂休眠
        
        self.end_time = time.time()
        
        if self.received_count >= expected_count:
            print(f"✅ 接收完成，共接收 {self.received_count} 条消息")
        else:
            print(f"⏰ 接收超时，共接收 {self.received_count} 条消息")
        
        self.print_receiver_stats()
    
    def print_receiver_stats(self):
        """打印接收端统计"""
        if not self.start_time or not self.last_message_time:
            print("❌ 没有接收到任何消息")
            return
        
        # 计算从第一条消息到最后一条消息的时长
        duration = self.last_message_time - self.start_time
        throughput = self.received_count / duration if duration > 0 else 0
        lost_count = self.expected_count - self.received_count
        loss_rate = (lost_count / self.expected_count * 100) if self.expected_count > 0 else 0
        
        print("\n" + "="*50)
        print("📊 接收端统计")
        print("="*50)
        print(f"接收时长: {duration:.2f} 秒 (从第一条到最后一条消息)")
        print(f"期望接收: {self.expected_count} 条")
        print(f"实际接收: {self.received_count} 条")
        print(f"丢失消息: {lost_count} 条")
        print(f"丢包率: {loss_rate:.2f}%")
        print(f"吞吐量: {throughput:.2f} 消息/秒")
        
        if self.latencies:
            avg_latency = statistics.mean(self.latencies)
            min_latency = min(self.latencies)
            max_latency = max(self.latencies)
            median_latency = statistics.median(self.latencies)
            
            print(f"\n接收间隔统计 (毫秒):")
            print(f"  间隔样本数: {len(self.latencies)}")
            print(f"  平均间隔: {avg_latency:.2f} ms")
            print(f"  最小间隔: {min_latency:.2f} ms")
            print(f"  最大间隔: {max_latency:.2f} ms")
            print(f"  中位间隔: {median_latency:.2f} ms")
            
            # 计算P95和P99延迟
            if len(self.latencies) >= 20:
                sorted_latencies = sorted(self.latencies)
                p95_index = int(len(sorted_latencies) * 0.95)
                p99_index = int(len(sorted_latencies) * 0.99)
                p95_latency = sorted_latencies[p95_index]
                p99_latency = sorted_latencies[p99_index]
                print(f"  P95间隔:  {p95_latency:.2f} ms")
                print(f"  P99间隔:  {p99_latency:.2f} ms")
            
            # 延迟分布统计
            if len(self.latencies) >= 10:
                latency_ranges = [
                    (0, 1, "0-1ms"),
                    (1, 2, "1-2ms"), 
                    (2, 5, "2-5ms"),
                    (5, 10, "5-10ms"),
                    (10, 1000, ">10ms")
                ]
                
                print(f"\n接收间隔分布:")
                for min_val, max_val, label in latency_ranges:
                    count = sum(1 for l in self.latencies if min_val <= l < max_val)
                    percentage = count / len(self.latencies) * 100
                    print(f"  {label}: {count}条 ({percentage:.1f}%)")
        
        print("="*50)
    
    def cleanup(self):
        """清理DDS资源"""
        print("🧹 清理接收端资源...")
        
        try:
            if self.participant:
                ret = self.participant.delete_contained_entities()
                if ret != basic.RETCODE_OK:
                    print(f"⚠️ 删除包含实体失败: {ret}")
                
                factory = domain.TheParticipantFactory
                ret = factory.delete_participant(self.participant)
                if ret != basic.RETCODE_OK:
                    print(f"⚠️ 删除域参与者失败: {ret}")
            
            print("✅ 接收端资源清理完成")
            
        except Exception as e:
            print(f"⚠️ 清理资源时出错: {e}")

def main():
    """主函数"""
    print("="*50)
    print("🚀 DDS 性能测试 - 接收端")
    print("="*50)
    
    # 获取用户输入
    domain_id = int(input("输入DDS域ID (默认80): ") or "80")
    topic_name = input("输入主题名称 (默认PERF_TEST): ") or "PERF_TEST"
    expected_count = int(input("输入期望接收消息数量 (默认100): ") or "100")
    timeout = int(input("输入接收超时时间秒数 (默认60): ") or "60")
    
    receiver = DDSReceiver(domain_id, topic_name)
    
    try:
        # 初始化DDS
        topic_obj = receiver.initialize_dds()
        
        # 设置接收端
        receiver.setup_receiver(topic_obj)
        
        print("等待DDS发现完成...")
        time.sleep(3)
        
        # 接收消息
        receiver.receive_messages(expected_count, timeout)
        
    except KeyboardInterrupt:
        print("\n⏹️ 接收被中断")
    except Exception as e:
        print(f"❌ 接收失败: {e}")
        import traceback
        traceback.print_exc()
    finally:
        receiver.cleanup()

if __name__ == "__main__":
    main()
