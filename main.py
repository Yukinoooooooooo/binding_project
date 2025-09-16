# -*- coding: utf-8 -*-
# 主程序入口
import sys
from PySide6.QtWidgets import QApplication, QMessageBox
from PySide6.QtCore import Qt

from main_ui import MainUI
from dds_chat import DDSChatManager
from username_dialog import get_username_from_dialog

def main():
    """主函数"""
    # 创建Qt应用程序
    app = QApplication(sys.argv)
    
    # 获取用户输入（使用对话框）
    self_name, self_id = get_username_from_dialog()
    
    # 如果用户取消了输入，退出程序
    if self_name is None:
        print("用户取消了登录，程序退出")
        return

    # 创建DDS聊天管理器
    dds_manager = DDSChatManager(self_name, self_id)
    
    # 创建主UI界面（包含功能栏和聊天功能）
    main_ui = MainUI(self_name, self_id, dds_manager)
    
    try:
        # 获取聊天UI和信号代理（在DDS初始化之前）
        chat_ui = main_ui.get_chat_ui()
        # 将DDS管理器传递给聊天UI
        chat_ui.dds_manager = dds_manager
        proxy = dds_manager.get_signal_proxy()
        
        # 连接信号（在DDS初始化之前连接）
        chat_ui.sendMessage.connect(dds_manager.send_message)
        proxy.newMessage.connect(lambda t, s, m: chat_ui.showMessage.emit(t, s, m))
        proxy.userJoined.connect(lambda t, u: chat_ui.userJoined.emit(t, u))
        proxy.userLeft.connect(lambda t, u: chat_ui.userLeft.emit(t, u))
        proxy.newTopicCreated.connect(lambda t: chat_ui.newTopicCreated.emit(t))
        proxy.topicDiscovered.connect(lambda t: chat_ui.handle_topic_discovered(t))
        proxy.topicDeleted.connect(lambda t: chat_ui.topicDeleted.emit(t))
        
        print(f"[调试] 信号连接完成，用户名: {self_name}, 用户ID: {self_id}")
        
        # 初始化DDS系统（在信号连接之后）
        if not dds_manager.initialize_dds():
            print("DDS初始化失败，程序退出")
            return
        
        # 显示UI
        main_ui.show()
        
        # 添加窗口关闭事件处理
        def on_window_close():
            print("👋 窗口关闭，程序退出")
            dds_manager.cleanup()
            app.quit()
        
        main_ui.closeEvent = lambda event: on_window_close()
        
        # 运行应用程序
        try:
            print("[调试] 开始运行事件循环...")
            app.exec()
            print("[调试] 事件循环结束")
        except Exception as e:
            import traceback
            traceback.print_exc()
            
    except Exception as e:
        print(f"程序启动失败: {e}")
        import traceback
        traceback.print_exc()
    finally:
        # 清理资源
        dds_manager.cleanup()

if __name__ == "__main__":
    main()
