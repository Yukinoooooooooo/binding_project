#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
简化版聊天程序 - 使用ZRDDS Unified模块
直接对应原C++代码的功能
"""

import sys
import os
import time
import threading
from datetime import datetime

# 添加zrpy目录到Python路径
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'zrpy'))

def get_current_time():
    """获取当前时间字符串"""
    return datetime.now().strftime("%H:%M:%S")

def print_with_wrap(prefix, msg, wrap_len=80):
    """打印带换行的消息"""
    lines = []
    start = 0
    while start < len(msg):
        lines.append(msg[start:start + wrap_len])
        start += wrap_len
    
    for i, line in enumerate(lines):
        if i == 0:
            print(f"{prefix}{line}")
        else:
            print(f"       {line}")
    sys.stdout.flush()

def main():
    """主函数"""
    print("=" * 60)
    print("ZRDDS 聊天程序 (简化版)")
    print("=" * 60)
    
    try:
        import _zrdds_unified as dds
    except ImportError:
        print("错误: 无法导入 _zrdds_unified 模块")
        print("请确保模块已正确编译并放在 zrpy 目录中")
        return False
    
    # 获取用户名
    self_name = input("请输入你的用户名: ").strip()
    if not self_name:
        self_name = "匿名用户"
    
    # 初始化DDS
    print("正在初始化DDS...")
    if not dds.init():
        print("DDS初始化失败")
        return False
    
    # 创建域参与者
    if not dds.create_participant(80):
        print("创建域参与者失败")
        return False
    
    # 创建主题
    if not dds.create_topic("CHAT_TOPIC"):
        print("创建主题失败")
        return False
    
    # 创建发布者
    if not dds.create_publisher():
        print("创建发布者失败")
        return False
    
    # 创建订阅者
    if not dds.create_subscriber():
        print("创建订阅者失败")
        return False
    
    # 创建数据写入器
    if not dds.create_datawriter():
        print("创建数据写入器失败")
        return False
    
    # 创建数据读取器
    if not dds.create_datareader():
        print("创建数据读取器失败")
        return False
    
    print("DDS初始化成功！")
    print(f"欢迎 {self_name}！开始聊天吧！")
    print("输入 'exit' 退出程序")
    print("-" * 60)
    
    # 接收消息的线程
    running = True
    
    def receive_messages():
        """接收消息的线程函数"""
        while running:
            try:
                data = dds.read_data()
                if data:
                    # 处理接收到的消息
                    if ':' in data:
                        name, msg = data.split(':', 1)
                        if name != self_name:  # 不打印自己的消息
                            timestr = get_current_time()
                            prefix = f"[{timestr}][对方 {name}] "
                            print_with_wrap(prefix, msg)
                    else:
                        print(f"[收到] {data}")
                time.sleep(0.1)
            except Exception as e:
                if running:
                    print(f"接收消息错误: {e}")
                break
    
    # 启动接收线程
    receive_thread = threading.Thread(target=receive_messages, daemon=True)
    receive_thread.start()
    
    try:
        # 主循环：发送消息
        while True:
            try:
                message = input("[我] 请输入消息 (输入 exit 退出): ").strip()
                
                if message.lower() == "exit":
                    break
                
                if message:  # 只发送非空消息
                    # 构造消息格式: "用户名:消息内容"
                    full_message = f"{self_name}:{message}"
                    
                    # 发送数据
                    if dds.write_data(full_message):
                        # 显示自己发送的消息
                        timestr = get_current_time()
                        prefix = f"[{timestr}][我] "
                        print_with_wrap(prefix, message)
                    else:
                        print("发送消息失败")
                
            except KeyboardInterrupt:
                print("\n收到中断信号，正在退出...")
                break
            except EOFError:
                print("\n输入结束，正在退出...")
                break
            except Exception as e:
                print(f"输入错误: {e}")
                continue
    
    finally:
        # 清理资源
        running = False
        dds.cleanup()
        print("聊天程序已退出")
    
    return True

if __name__ == "__main__":
    success = main()
    if not success:
        print("程序运行失败")
        sys.exit(1)
    else:
        print("程序正常退出")
