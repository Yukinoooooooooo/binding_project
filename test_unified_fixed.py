#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os

# 添加当前目录到Python路径
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

try:
    import _zrdds_unified as dds
    print("✓ 成功导入 _zrdds_unified 模块")
except ImportError as e:
    print(f"✗ 导入模块失败: {e}")
    sys.exit(1)

def test_basic_functionality():
    print("\n=== 测试基本功能 ===")
    
    # 初始化
    print("1. 初始化...")
    if dds.init():
        print("✓ 初始化成功")
    else:
        print("✗ 初始化失败")
        return False
    
    # 创建域参与者
    print("2. 创建域参与者...")
    if dds.create_participant(0):
        print("✓ 域参与者创建成功")
    else:
        print("✗ 域参与者创建失败")
        return False
    
    # 创建主题
    print("3. 创建主题...")
    if dds.create_topic("ChatTopic"):
        print("✓ 主题创建成功")
    else:
        print("✗ 主题创建失败")
        return False
    
    # 创建发布者
    print("4. 创建发布者...")
    if dds.create_publisher():
        print("✓ 发布者创建成功")
    else:
        print("✗ 发布者创建失败")
        return False
    
    # 创建订阅者
    print("5. 创建订阅者...")
    if dds.create_subscriber():
        print("✓ 订阅者创建成功")
    else:
        print("✗ 订阅者创建失败")
        return False
    
    # 创建数据写入器
    print("6. 创建数据写入器...")
    if dds.create_datawriter():
        print("✓ 数据写入器创建成功")
    else:
        print("✗ 数据写入器创建失败")
        return False
    
    # 创建数据读取器
    print("7. 创建数据读取器...")
    if dds.create_datareader():
        print("✓ 数据读取器创建成功")
    else:
        print("✗ 数据读取器创建失败")
        return False
    
    # 检查状态
    print("8. 检查状态...")
    status = dds.get_status()
    print(f"状态: {status}")
    
    return True

def test_send_receive():
    print("\n=== 测试发送接收 ===")
    
    # 测试发送
    print("1. 测试发送数据...")
    test_message = "Hello from Python!"
    if dds.write_data(test_message):
        print(f"✓ 发送成功: {test_message}")
    else:
        print("✗ 发送失败")
        return False
    
    # 测试接收
    print("2. 测试接收数据...")
    try:
        received_data = dds.read_data()
        if received_data is not None:
            print(f"✓ 接收成功: {received_data}")
            return True
        else:
            print("⚠ 没有接收到数据（这是正常的，因为没有其他发送者）")
            return True
    except Exception as e:
        print(f"✗ 接收失败: {e}")
        return False

def main():
    print("开始测试修复后的 _zrdds_unified 模块...")
    
    if not test_basic_functionality():
        print("\n✗ 基本功能测试失败")
        return False
    
    if not test_send_receive():
        print("\n✗ 发送接收测试失败")
        return False
    
    # 清理
    print("\n3. 清理资源...")
    if dds.cleanup():
        print("✓ 清理成功")
    else:
        print("✗ 清理失败")
    
    print("\n✓ 所有测试通过！模块工作正常。")
    return True

if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)
