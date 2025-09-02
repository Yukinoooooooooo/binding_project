#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
使用ZRDDS Unified模块实现的聊天程序
基于原C++代码的功能，使用Python和unified模块API
"""

import sys
import os
import time
import threading
from datetime import datetime

# 添加zrpy目录到Python路径
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'zrpy'))

class ChatApp:
    def __init__(self):
        self.dds = None
        self.running = False
        self.self_name = ""
        
    def get_current_time(self):
        """获取当前时间字符串"""
        return datetime.now().strftime("%H:%M:%S")
    
    def print_with_wrap(self, prefix, msg, wrap_len=80):
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
    
    def init_dds(self):
        """初始化DDS模块"""
        try:
            import _zrdds_unified as dds
            self.dds = dds
            
            # 初始化
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
            
            print("DDS初始化成功")
            return True
            
        except Exception as e:
            print(f"DDS初始化失败: {e}")
            return False
    
    def start_receiving(self):
        """启动接收消息的线程"""
        def receive_loop():
            while self.running:
                try:
                    # 读取数据
                    data = self.dds.read_data()
                    if data:
                        self.handle_received_message(data)
                    time.sleep(0.1)  # 避免CPU占用过高
                except Exception as e:
                    if self.running:  # 只有在运行状态下才打印错误
                        print(f"接收消息错误: {e}")
                    break
        
        receive_thread = threading.Thread(target=receive_loop, daemon=True)
        receive_thread.start()
        return receive_thread
    
    def handle_received_message(self, data):
        """处理接收到的消息"""
        try:
            # 消息格式: "用户名:消息内容"
            if ':' in data:
                name, msg = data.split(':', 1)
                if name != self.self_name:  # 不打印自己的消息
                    timestr = self.get_current_time()
                    prefix = f"[{timestr}][对方 {name}] "
                    self.print_with_wrap(prefix, msg)
            else:
                print(f"[收到] {data}")
        except Exception as e:
            print(f"处理消息错误: {e}")
    
    def send_message(self, message):
        """发送消息"""
        try:
            # 构造消息格式: "用户名:消息内容"
            full_message = f"{self.self_name}:{message}"
            
            # 发送数据
            if self.dds.write_data(full_message):
                # 显示自己发送的消息
                timestr = self.get_current_time()
                prefix = f"[{timestr}][我] "
                self.print_with_wrap(prefix, message)
                return True
            else:
                print("发送消息失败")
                return False
        except Exception as e:
            print(f"发送消息错误: {e}")
            return False
    
    def run(self):
        """运行聊天程序"""
        print("=" * 60)
        print("ZRDDS 聊天程序")
        print("=" * 60)
        
        # 获取用户名
        self.self_name = input("请输入你的用户名: ").strip()
        if not self.self_name:
            self.self_name = "匿名用户"
        
        # 初始化DDS
        if not self.init_dds():
            return False
        
        # 启动接收线程
        self.running = True
        receive_thread = self.start_receiving()
        
        print(f"\n欢迎 {self.self_name}！开始聊天吧！")
        print("输入 'exit' 退出程序")
        print("-" * 60)
        
        try:
            # 主循环：发送消息
            while True:
                try:
                    message = input("[我] 请输入消息 (输入 exit 退出): ").strip()
                    
                    if message.lower() == "exit":
                        break
                    
                    if message:  # 只发送非空消息
                        self.send_message(message)
                    
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
            self.running = False
            if self.dds:
                self.dds.cleanup()
            print("聊天程序已退出")
        
        return True

def main():
    """主函数"""
    chat_app = ChatApp()
    success = chat_app.run()
    
    if not success:
        print("程序运行失败")
        sys.exit(1)
    else:
        print("程序正常退出")

if __name__ == "__main__":
    main()
