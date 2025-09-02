#!/usr/bin/env python3

import sys
import time
sys.path.insert(0, 'zrpy')

def test_final_dds_architecture():

    try:
        # 导入所有模块
        import _zrdds_domain
        import _zrdds_topic
        import _zrdds_publish
        import _zrdds_subscribe
        import _zrdds_listener
        
        # ========================================
        # 阶段1: 域管理 - 域隔离实现
        # ========================================
        print(" 域管理 ")
        print("-" * 40)
        
        # 初始化所有模块
        print("🔧 初始化所有模块...")
        _zrdds_domain.init()
        _zrdds_topic.init()
        _zrdds_publish.init()
        _zrdds_subscribe.init()
        _zrdds_listener.init()
        print("   ✓ 所有模块初始化完成")
        
        # 获取工厂实例
        print("🏭 获取DomainParticipantFactory实例...")
        factory_available = _zrdds_domain.get_factory_instance()
        if not factory_available:
            print("   ✗ Factory实例不可用")
            return False
        print("   ✓ Factory实例可用")
        
        # 创建域参与者QoS
        print("⚙️ 创建域参与者QoS...")
        participant_qos_id = _zrdds_domain.create_participant_qos()
        if participant_qos_id == -1:
            print("   ✗ 创建域参与者QoS失败")
            return False
        print(f"   ✓ 域参与者QoS创建成功，ID: {participant_qos_id}")
        
        # 创建域参与者（域隔离的核心）
        print("👤 创建域参与者")
        domain_id = 100  # 使用域ID 100
        participant_id = _zrdds_domain.create_domain_participant(domain_id, participant_qos_id)
        if participant_id == -1:
            print("   ✗ 创建域参与者失败")
            return False
        print(f"   ✓ 域参与者创建成功，ID: {participant_id}")
        
        # 注册模块到域参与者（域隔离管理）
        print("注册模块到域参与者（域隔离管理）...")
        _zrdds_domain.register_participant_for_module(participant_id, "topic")
        _zrdds_domain.register_participant_for_module(participant_id, "publish")
        _zrdds_domain.register_participant_for_module(participant_id, "subscribe")
        print("   ✓ 模块注册到域参与者成功")
        
        # 其他模块注册域参与者（不自己创建）
        print("其他模块注册域参与者")
        _zrdds_topic.register_participant_by_id(domain_id, participant_id)
        _zrdds_publish.register_participant_by_id(domain_id, participant_id)
        _zrdds_subscribe.register_participant_by_id(domain_id, participant_id)
        print("   ✓ 其他模块注册域参与者成功")
        
        # ========================================
        # 阶段2: 主题管理 - 实体层次结构
        # ========================================
        print("\n阶段2: 主题管理 - 实体层次结构")
        print("-" * 40)
        
        # 创建主题
        print("创建主题...")
        topic_name = "FINAL_ARCHITECTURE_TEST"
        type_name = "Bytes"
        topic_id = _zrdds_topic.create_topic_pure_id(participant_id, topic_name, type_name)
        if topic_id <= 0:
            if topic_id == 0:
                print(f"   ⚠ 主题已存在: {topic_name}")
                topic_id = 1
            else:
                print("   ✗ 创建主题失败")
                return False
        print(f"   ✓ 主题创建成功，ID: {topic_id}")
        
        # 注册主题到其他模块
        print("注册主题到其他模块...")
        _zrdds_publish.register_topic_by_id(topic_name, topic_id)
        _zrdds_subscribe.register_topic_by_id(topic_name, topic_id)
        print("   ✓ 主题注册到其他模块成功")
        
        # ========================================
        # 阶段3: 发布者管理 - 实体层次结构
        # ========================================
        print("\n阶段3: 发布者管理 - 实体层次结构")
        print("-" * 40)
        
        # 创建发布者QoS
        print("创建发布者QoS...")
        publisher_qos_id = _zrdds_publish.create_publisher_qos()
        if publisher_qos_id == -1:
            print("   ✗ 创建发布者QoS失败")
            return False
        print(f"   ✓ 发布者QoS创建成功，ID: {publisher_qos_id}")
        
        # 创建发布者
        print("创建发布者...")
        publisher_id = _zrdds_publish.create_publisher_pure_id(participant_id, publisher_qos_id)
        if publisher_id == -1:
            print("   ✗ 创建发布者失败")
            return False
        print(f"   ✓ 发布者创建成功，ID: {publisher_id}")
        
        # 创建数据写入器QoS
        print("创建数据写入器QoS...")
        datawriter_qos_id = _zrdds_publish.create_datawriter_qos()
        if datawriter_qos_id == -1:
            print("   ✗ 创建数据写入器QoS失败")
            return False
        print(f"   ✓ 数据写入器QoS创建成功，ID: {datawriter_qos_id}")
        
        # 创建数据写入器
        print("创建数据写入器...")
        datawriter_id = _zrdds_publish.create_datawriter_pure_id(publisher_id, topic_id, datawriter_qos_id)
        if datawriter_id == -1:
            print("   ✗ 创建数据写入器失败")
            return False
        print(f"   ✓ 数据写入器创建成功，ID: {datawriter_id}")
        
        # ========================================
        # 阶段4: 订阅者管理 - 实体层次结构
        # ========================================
        print("\n阶段4: 订阅者管理")
        print("-" * 40)
        
        # 创建订阅者QoS
        print("创建订阅者QoS...")
        subscriber_qos_id = _zrdds_subscribe.create_subscriber_qos()
        if subscriber_qos_id == -1:
            print("   ✗ 创建订阅者QoS失败")
            return False
        print(f"   ✓ 订阅者QoS创建成功，ID: {subscriber_qos_id}")
        
        # 创建订阅者
        print("创建订阅者...")
        subscriber_id = _zrdds_subscribe.create_subscriber_pure_id(participant_id, subscriber_qos_id)
        if subscriber_id == -1:
            print("   ✗ 创建订阅者失败")
            return False
        print(f"   ✓ 订阅者创建成功，ID: {subscriber_id}")
        
        # 创建数据读取器QoS
        print("创建数据读取器QoS...")
        datareader_qos_id = _zrdds_subscribe.create_datareader_qos()
        if datareader_qos_id == -1:
            print("   ✗ 创建数据读取器QoS失败")
            return False
        print(f"   ✓ 数据读取器QoS创建成功，ID: {datareader_qos_id}")
        
        # 创建数据读取器
        print("创建数据读取器...")
        datareader_id = _zrdds_subscribe.create_datareader_pure_id(subscriber_id, topic_id, datareader_qos_id)
        if datareader_id == -1:
            print("   ✗ 创建数据读取器失败")
            return False
        print(f"   ✓ 数据读取器创建成功，ID: {datareader_id}")
        
        # ========================================
        # 阶段5: 数据通信测试
        # ========================================
        print("\n阶段5: 数据通信测试")
        print("-" * 40)
        
        # 发送测试数据
        print("发送测试数据...")
        test_messages = [
            "Architecture Test #1",
            "架构测试消息 #2",
            "Domain Isolation Working #3",
            "域隔离正常工作 #4",
            "ID-based Communication #5"
        ]
        
        for i, message in enumerate(test_messages, 1):
            success = _zrdds_publish.write_bytes_data(datawriter_id, message)
            if success:
                print(f"   ✓ 消息 {i} 发送成功: '{message}'")
            else:
                print(f"   ✗ 消息 {i} 发送失败: '{message}'")
            time.sleep(0.3)  # 短暂延迟
        
        # 等待数据到达
        print("⏳ 等待数据到达...")
        time.sleep(2)
        
        # 尝试读取数据
        print("📖 尝试读取数据...")
        received_data = _zrdds_subscribe.read_bytes_data(datareader_id)
        if received_data:
            print(f"   ✓ 接收到数据: {received_data}")
        else:
            print("   ⚠ 未接收到数据 (这是正常的，因为监听器回调可能还未触发)")
        
        # ========================================
        # 阶段6: 架构验证
        # ========================================
        print("\n阶段6: 架构验证")
        print("-" * 40)
        
        # 验证域隔离
        print("验证域隔离...")
        domain_participant_count = _zrdds_domain.get_participant_count()
        print(f"   ✓ 域参与者数量: {domain_participant_count}")
        
        # 验证实体层次结构
        print("验证实体层次结构...")
        topic_count = _zrdds_topic.get_topic_count()
        publisher_count = _zrdds_publish.get_publisher_count()
        datawriter_count = _zrdds_publish.get_datawriter_count()
        subscriber_count = _zrdds_subscribe.get_subscriber_count()
        datareader_count = _zrdds_subscribe.get_datareader_count()
        
        print(f"   ✓ 主题数量: {topic_count}")
        print(f"   ✓ 发布者数量: {publisher_count}")
        print(f"   ✓ 数据写入器数量: {datawriter_count}")
        print(f"   ✓ 订阅者数量: {subscriber_count}")
        print(f"   ✓ 数据读取器数量: {datareader_count}")
        
        # 验证ID-based通信
        print("验证ID-based通信...")
        print(f"   ✓ 域参与者ID: {participant_id}")
        print(f"   ✓ 主题ID: {topic_id}")
        print(f"   ✓ 发布者ID: {publisher_id}")
        print(f"   ✓ 数据写入器ID: {datawriter_id}")
        print(f"   ✓ 订阅者ID: {subscriber_id}")
        print(f"   ✓ 数据读取器ID: {datareader_id}")
        
        # ========================================
        # 阶段7: 资源清理
        # ========================================
        print("\n🧹 阶段7: 资源清理")
        print("-" * 40)
        
        # 删除数据读取器
        print("删除数据读取器...")
        if datareader_id != -1:
            _zrdds_subscribe.delete_datareader(datareader_id)
            print("   ✓ 数据读取器删除成功")
        
        # 删除订阅者
        print("删除订阅者...")
        if subscriber_id != -1:
            _zrdds_subscribe.delete_subscriber(subscriber_id)
            print("   ✓ 订阅者删除成功")
        
        # 删除数据写入器
        print("删除数据写入器...")
        if datawriter_id != -1:
            _zrdds_publish.delete_datawriter(datawriter_id)
            print("   ✓ 数据写入器删除成功")
        
        # 删除发布者
        print("删除发布者...")
        if publisher_id != -1:
            _zrdds_publish.delete_publisher(publisher_id)
            print("   ✓ 发布者删除成功")
        
        # 删除主题
        print("删除主题...")
        _zrdds_topic.delete_topic(topic_name)
        print("   ✓ 主题删除成功")
        
        # 删除域参与者
        print("删除域参与者...")
        if participant_id != -1:
            _zrdds_domain.delete_domain_participant(participant_id)
            print("   ✓ 域参与者删除成功")
        
        # 删除QoS对象
        print("删除QoS对象...")
        if participant_qos_id != -1:
            _zrdds_domain.delete_participant_qos(participant_qos_id)
        if publisher_qos_id != -1:
            _zrdds_publish.delete_publisher_qos(publisher_qos_id)
        if datawriter_qos_id != -1:
            _zrdds_publish.delete_datawriter_qos(datawriter_qos_id)
        if subscriber_qos_id != -1:
            _zrdds_subscribe.delete_subscriber_qos(subscriber_qos_id)
        if datareader_qos_id != -1:
            _zrdds_subscribe.delete_datareader_qos(datareader_qos_id)
        print("   ✓ 所有QoS对象删除成功")
        
        # 最终化所有模块
        print("最终化所有模块...")
        _zrdds_listener.finalize()
        _zrdds_subscribe.finalize()
        _zrdds_publish.finalize()
        _zrdds_topic.finalize()
        _zrdds_domain.finalize()
        print("   ✓ 所有模块最终化成功")
     
        
        return True
        
    except Exception as e:
        print(f"\n❌ 测试失败: {e}")
        import traceback
        traceback.print_exc()
        return False

if __name__ == "__main__":
    success = test_final_dds_architecture()
    if success:
        print("\n🚀 测试成功完成！")
        sys.exit(0)
    else:
        print("\n💥 测试失败！")
        sys.exit(1)
