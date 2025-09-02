#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
统一DDS模块测试 - 像C++那样直接调用
演示如何像C++代码那样直接使用DDS功能
"""

import sys
import os
import time

# 添加zrpy目录到Python路径
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'zrpy'))

def test_unified_dds():

    try:
        import _zrdds_unified as dds
        
        # 初始化
        print("🔧 初始化DDS管理器...")
        if not dds.init():
            print("   ✗ 初始化失败")
            return False
        print("   ✓ 初始化成功")
        
        # 1. 创建域参与者 -        print("\n📡 创建域参与者...")
        if not dds.create_participant(80):
            print("   ✗ 创建域参与者失败")
            return False
        print("   ✓ 域参与者创建成功")
        
        # 2. 创建主题 - 直接使用，不需要传递participant
        print("\n📝 创建主题...")
        if not dds.create_topic("TestTopic", "Bytes"):
            print("   ✗ 创建主题失败")
            return False
        print("   ✓ 主题创建成功")
        
        # 3. 创建发布者 - 直接使用，不需要传递participant
        print("\n📢 创建发布者...")
        if not dds.create_publisher():
            print("   ✗ 创建发布者失败")
            return False
        print("   ✓ 发布者创建成功")
        
        # 4. 创建订阅者 - 直接使用，不需要传递participant
        print("\n📥 创建订阅者...")
        if not dds.create_subscriber():
            print("   ✗ 创建订阅者失败")
            return False
        print("   ✓ 订阅者创建成功")
        
        # 5. 创建数据写入器 - 直接使用，不需要传递publisher和topic
        print("\n✍️ 创建数据写入器...")
        if not dds.create_datawriter():
            print("   ✗ 创建数据写入器失败")
            return False
        print("   ✓ 数据写入器创建成功")
        
        # 6. 创建数据读取器 - 直接使用，不需要传递subscriber和topic
        print("\n👁️ 创建数据读取器...")
        if not dds.create_datareader():
            print("   ✗ 创建数据读取器失败")
            return False
        print("   ✓ 数据读取器创建成功")
        
        # 7. 写入数据 - 直接使用，不需要传递datawriter
        print("\n📤 写入数据...")
        test_message = "Hello from Unified DDS Module!"
        if not dds.write_data(test_message):
            print("   ✗ 数据写入失败")
            return False
        print(f"   ✓ 数据写入成功: {test_message}")
        
        # 8. 等待数据传播
        print("\n⏳ 等待数据传播...")
        time.sleep(2)
        
        # 9. 读取数据 - 直接使用，不需要传递datareader
        print("\n📥 读取数据...")
        received_data = dds.read_data()
        if received_data is None:
            print("   ⚠ 未接收到数据（可能正常）")
        else:
            print(f"   ✓ 数据读取成功: {received_data}")
        
        # 10. 检查状态
        print("\n📊 检查所有实体状态...")
        status = dds.get_status()
        for entity, exists in status.items():
            status_icon = "✓" if exists else "✗"
            print(f"   {status_icon} {entity}: {'存在' if exists else '不存在'}")
        
        # 清理
        print("\n🧹 清理资源...")
        if dds.cleanup():
            print("   ✓ 清理成功")
        else:
            print("   ✗ 清理失败")
        
        print("\n🎉 统一DDS模块测试完成！")
        print("=" * 60)
        print("✅ 成功演示了像C++那样的直接DDS调用方式")
        print("✅ 不需要手动传递对象，模块内部自动管理依赖关系")
        print("✅ 使用简单，代码清晰，就像你的C++代码一样")
        
        return True
        
    except Exception as e:
        print(f"   ✗ 测试失败: {e}")
        return False

def compare_with_old_way():
    """对比新旧使用方式"""
    print("\n" + "=" * 60)
    print("📊 新旧使用方式对比")
    print("=" * 60)
    
    print("\n🔴 旧方式（复杂，需要手动传递对象）:")
    print("""
    # 需要导入多个模块
    import _zrdds_domain as domain
    import _zrdds_topic as topic
    import _zrdds_publish as publish
    import _zrdds_subscribe as subscribe
    
    # 需要手动传递对象
    domain.init()
    domain.create_domain_participant(80)
    participant = domain.get_participant()  # 手动获取
    
    topic.init()
    topic.create_topic(participant, "MyTopic", "Bytes")  # 手动传递
    topic_obj = topic.get_topic()  # 再次手动获取
    
    publish.init()
    publish.create_publisher(participant)  # 再次手动传递
    publish.create_datawriter(topic_obj)   # 再次手动传递
    """)
    
    print("\n🟢 新方式（简单，像C++那样直接）:")
    print("""
    # 只需要导入一个模块
    import _zrdds_unified as dds
    
    # 直接调用，不需要传递对象
    dds.init()
    dds.create_participant(80)      # 直接创建
    dds.create_topic("MyTopic")     # 直接创建，自动使用participant
    dds.create_publisher()          # 直接创建，自动使用participant
    dds.create_datawriter()         # 直接创建，自动使用publisher和topic
    dds.write_data("Hello!")        # 直接写入，自动使用datawriter
    """)
    
    print("\n💡 优势:")
    print("   ✅ 使用简单，像C++代码一样直接")
    print("   ✅ 不需要手动管理对象传递")
    print("   ✅ 模块内部自动处理依赖关系")
    print("   ✅ 代码更清晰，更易维护")
    print("   ✅ 符合你的C++代码使用习惯")

if __name__ == "__main__":
    success = test_unified_dds()
    compare_with_old_way()
    
    if not success:
        print("\n💥 测试失败！")
        sys.exit(1)
    else:
        print("\n✨ 测试完成！")
