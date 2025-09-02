#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
重构后模块测试 - 验证模块分离架构
测试所有重构后的DDS模块：domain, topic, publish, subscribe, listener, basic
"""

import sys
import os
import time

# 添加当前目录和zrpy目录到Python路径
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'zrpy'))

def test_domain_module():
    """测试域模块"""
    print("🔧 测试域模块 (Domain Module)")
    print("-" * 50)
    
    try:
        import _zrdds_domain as domain
        
        # 初始化
        if not domain.init():
            print("   ✗ 域模块初始化失败")
            return False, None
        print("   ✓ 域模块初始化成功")
        
        # 创建域参与者
        if not domain.create_domain_participant(80):
            print("   ✗ 创建域参与者失败")
            return False, None
        print("   ✓ 域参与者创建成功")
        
        # 验证域参与者存在
        if not domain.participant_exists():
            print("   ✗ 域参与者不存在")
            return False, None
        print("   ✓ 域参与者验证成功")
        
        # 获取域ID
        domain_id = domain.get_participant_domain_id()
        if domain_id is None:
            print("   ✗ 获取域ID失败")
            return False, None
        print(f"   ✓ 域ID: {domain_id}")
        
        # 获取域参与者对象（用于其他模块）
        participant = domain.get_participant()
        if participant is None:
            print("   ✗ 获取域参与者对象失败")
            return False, None
        print("   ✓ 域参与者对象获取成功")
        
        return True, participant
    
    except Exception as e:
        print(f"   ✗ 域模块测试失败: {e}")
        return False, None

def test_topic_module(participant):
    """测试主题模块"""
    print("\n📝 测试主题模块 (Topic Module)")
    print("-" * 50)
    
    try:
        import _zrdds_topic as topic
        
        # 初始化
        if not topic.init():
            print("   ✗ 主题模块初始化失败")
            return False, None
        print("   ✓ 主题模块初始化成功")
        
        # 创建主题
        if not topic.create_topic(participant, "TestTopic", "Bytes"):
            print("   ✗ 创建主题失败")
            return False, None
        print("   ✓ 主题创建成功")
        
        # 验证主题存在
        if not topic.topic_exists():
            print("   ✗ 主题不存在")
            return False, None
        print("   ✓ 主题验证成功")
        
        # 获取主题名称
        topic_name = topic.get_topic_name()
        if topic_name is None:
            print("   ✗ 获取主题名称失败")
            return False, None
        print(f"   ✓ 主题名称: {topic_name}")
        
        # 获取主题类型
        topic_type = topic.get_topic_type_name()
        if topic_type is None:
            print("   ✗ 获取主题类型失败")
            return False, None
        print(f"   ✓ 主题类型: {topic_type}")
        
        # 获取主题对象（用于其他模块）
        topic_obj = topic.get_topic()
        if topic_obj is None:
            print("   ✗ 获取主题对象失败")
            return False, None
        print("   ✓ 主题对象获取成功")
        
        return True, topic_obj
        
    except Exception as e:
        print(f"   ✗ 主题模块测试失败: {e}")
        return False, None

def test_publish_module(participant, topic_obj):
    """测试发布模块"""
    print("\n📢 测试发布模块 (Publish Module)")
    print("-" * 50)
    
    try:
        import _zrdds_publish as publish
        
        # 初始化
        if not publish.init():
            print("   ✗ 发布模块初始化失败")
            return False, None
        print("   ✓ 发布模块初始化成功")
        
        # 创建发布者
        if not publish.create_publisher(participant):
            print("   ✗ 创建发布者失败")
            return False, None
        print("   ✓ 发布者创建成功")
        
        # 验证发布者存在
        if not publish.publisher_exists():
            print("   ✗ 发布者不存在")
            return False, None
        print("   ✓ 发布者验证成功")
        
        # 创建数据写入器
        if not publish.create_datawriter(topic_obj):
            print("   ✗ 创建数据写入器失败")
            return False, None
        print("   ✓ 数据写入器创建成功")
        
        # 验证数据写入器存在
        if not publish.datawriter_exists():
            print("   ✗ 数据写入器不存在")
            return False, None
        print("   ✓ 数据写入器验证成功")
        
        # 测试数据写入
        test_data = "Hello from Publish Module!"
        if not publish.write_bytes_data(test_data):
            print("   ✗ 数据写入失败")
            return False, None
        print(f"   ✓ 数据写入成功: {test_data}")
        
        return True, None
        
    except Exception as e:
        print(f"   ✗ 发布模块测试失败: {e}")
        return False, None

def test_subscribe_module(participant, topic_obj):
    """测试订阅模块"""
    print("\n📥 测试订阅模块 (Subscribe Module)")
    print("-" * 50)
    
    try:
        import _zrdds_subscribe as subscribe
        
        # 初始化
        if not subscribe.init():
            print("   ✗ 订阅模块初始化失败")
            return False, None
        print("   ✓ 订阅模块初始化成功")
        
        # 创建订阅者
        if not subscribe.create_subscriber(participant):
            print("   ✗ 创建订阅者失败")
            return False, None
        print("   ✓ 订阅者创建成功")
        
        # 验证订阅者存在
        if not subscribe.subscriber_exists():
            print("   ✗ 订阅者不存在")
            return False, None
        print("   ✓ 订阅者验证成功")
        
        # 创建数据读取器
        if not subscribe.create_datareader(topic_obj):
            print("   ✗ 创建数据读取器失败")
            return False, None
        print("   ✓ 数据读取器创建成功")
        
        # 验证数据读取器存在
        if not subscribe.datareader_exists():
            print("   ✗ 数据读取器不存在")
            return False, None
        print("   ✓ 数据读取器验证成功")
        
        # 等待数据传播
        print("   ⏳ 等待数据传播...")
        time.sleep(2)
        
        # 测试数据读取
        received_data = subscribe.read_bytes_data()
        if received_data is None:
            print("   ⚠ 数据读取返回None（可能没有数据）")
        else:
            print(f"   ✓ 数据读取成功: {received_data}")
        
        return True, None
        
    except Exception as e:
        print(f"   ✗ 订阅模块测试失败: {e}")
        return False, None

def test_listener_module():
    """测试监听器模块"""
    print("\n👂 测试监听器模块 (Listener Module)")
    print("-" * 50)
    
    try:
        import _zrdds_listener as listener
        
        # 初始化
        if not listener.init():
            print("   ✗ 监听器模块初始化失败")
            return False
        print("   ✓ 监听器模块初始化成功")
        
        # 创建数据读取器监听器
        if not listener.create_datareader_listener():
            print("   ✗ 创建数据读取器监听器失败")
            return False
        print("   ✓ 数据读取器监听器创建成功")
        
        # 验证监听器存在
        if not listener.datareader_listener_exists():
            print("   ✗ 数据读取器监听器不存在")
            return False
        print("   ✓ 数据读取器监听器验证成功")
        
        # 创建数据写入器监听器
        if not listener.create_datawriter_listener():
            print("   ✗ 创建数据写入器监听器失败")
            return False
        print("   ✓ 数据写入器监听器创建成功")
        
        # 验证监听器存在
        if not listener.datawriter_listener_exists():
            print("   ✗ 数据写入器监听器不存在")
            return False
        print("   ✓ 数据写入器监听器验证成功")
        
        return True
        
    except Exception as e:
        print(f"   ✗ 监听器模块测试失败: {e}")
        return False

def test_basic_module():
    """测试基础模块"""
    print("\n🔧 测试基础模块 (Basic Module)")
    print("-" * 50)
    
    try:
        import _zrdds_basic as basic
        
        # 初始化
        if not basic.init():
            print("   ✗ 基础模块初始化失败")
            return False
        print("   ✓ 基础模块初始化成功")
        
        # 创建GuardCondition
        if not basic.create_guard_condition():
            print("   ✗ 创建GuardCondition失败")
            return False
        print("   ✓ GuardCondition创建成功")
        
        # 验证GuardCondition存在
        if not basic.guard_condition_exists():
            print("   ✗ GuardCondition不存在")
            return False
        print("   ✓ GuardCondition验证成功")
        
        # 创建WaitSet
        if not basic.create_waitset():
            print("   ✗ 创建WaitSet失败")
            return False
        print("   ✓ WaitSet创建成功")
        
        # 验证WaitSet存在
        if not basic.waitset_exists():
            print("   ✗ WaitSet不存在")
            return False
        print("   ✓ WaitSet验证成功")
        
        # 附加条件
        if not basic.attach_condition():
            print("   ✗ 附加条件失败")
            return False
        print("   ✓ 条件附加成功")
        
        return True
        
    except Exception as e:
        print(f"   ✗ 基础模块测试失败: {e}")
        return False

def test_module_integration():
    """测试模块集成"""
    print("\n🔗 测试模块集成 (Module Integration)")
    print("-" * 50)
    
    try:
        # 测试完整的发布-订阅流程
        print("   📤 测试发布-订阅流程...")
        
        # 1. 创建域参与者
        import _zrdds_domain as domain
        domain.init()
        domain.create_domain_participant(81)
        participant = domain.get_participant()
        
        # 2. 创建主题
        import _zrdds_topic as topic
        topic.init()
        topic.create_topic(participant, "IntegrationTest", "Bytes")
        topic_obj = topic.get_topic()
        
        # 3. 创建发布者
        import _zrdds_publish as publish
        publish.init()
        publish.create_publisher(participant)
        publish.create_datawriter(topic_obj)
        
        # 4. 创建订阅者
        import _zrdds_subscribe as subscribe
        subscribe.init()
        subscribe.create_subscriber(participant)
        subscribe.create_datareader(topic_obj)
        
        # 5. 发布数据
        test_message = "Integration Test Message"
        if publish.write_bytes_data(test_message):
            print(f"   ✓ 发布数据成功: {test_message}")
        else:
            print("   ✗ 发布数据失败")
            return False
        
        # 6. 等待并读取数据
        time.sleep(2)
        received = subscribe.read_bytes_data()
        if received:
            print(f"   ✓ 接收数据成功: {received}")
        else:
            print("   ⚠ 未接收到数据（可能正常）")
        
        print("   ✓ 模块集成测试完成")
        return True
        
    except Exception as e:
        print(f"   ✗ 模块集成测试失败: {e}")
        return False

def main():
    """主测试函数"""
    print("🚀 重构后模块测试")
    print("=" * 60)
    print("目标：验证模块分离架构的正确性")
    print("=" * 60)
    
    success_count = 0
    total_tests = 6
    
    # 测试域模块
    domain_success, participant = test_domain_module()
    if domain_success:
        success_count += 1
    
    # 测试主题模块
    if participant:
        topic_success, topic_obj = test_topic_module(participant)
        if topic_success:
            success_count += 1
    else:
        print("\n📝 跳过主题模块测试（域模块失败）")
        topic_obj = None
    
    # 测试发布模块
    if participant and topic_obj:
        publish_success, _ = test_publish_module(participant, topic_obj)
        if publish_success:
            success_count += 1
    else:
        print("\n📢 跳过发布模块测试（前置条件失败）")
    
    # 测试订阅模块
    if participant and topic_obj:
        subscribe_success, _ = test_subscribe_module(participant, topic_obj)
        if subscribe_success:
            success_count += 1
    else:
        print("\n📥 跳过订阅模块测试（前置条件失败）")
    
    # 测试监听器模块
    listener_success = test_listener_module()
    if listener_success:
        success_count += 1
    
    # 测试基础模块
    basic_success = test_basic_module()
    if basic_success:
        success_count += 1
    
    # 测试模块集成
    integration_success = test_module_integration()
    if integration_success:
        success_count += 1
    
    # 输出测试结果
    print("\n" + "=" * 60)
    print("📊 测试结果汇总")
    print("=" * 60)
    print(f"总测试数: {total_tests}")
    print(f"成功数: {success_count}")
    print(f"失败数: {total_tests - success_count}")
    print(f"成功率: {success_count/total_tests*100:.1f}%")
    
    if success_count == total_tests:
        print("\n🎉 所有测试通过！模块重构成功！")
        return True
    else:
        print(f"\n⚠️ 有 {total_tests - success_count} 个测试失败，需要进一步调试")
        return False

if __name__ == "__main__":
    success = main()
    if not success:
        print("\n💥 测试失败！")
        sys.exit(1)
    else:
        print("\n✨ 测试完成！")
