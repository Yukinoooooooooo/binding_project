#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
用户名输入对话框
用于替代终端输入，方便打包成exe文件
"""

from PySide6.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QLabel, 
                               QLineEdit, QPushButton, QMessageBox, QApplication)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QFont, QPalette


class UsernameDialog(QDialog):
    """用户名输入对话框"""
    
    # 定义信号，当用户确认输入时发射
    username_confirmed = Signal(str, int)  # 用户名, 用户ID
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("用户登录")
        self.setFixedSize(400, 260)
        self.setWindowFlags(Qt.Window | Qt.WindowCloseButtonHint | Qt.WindowMinimizeButtonHint)
        
        # 检测系统主题
        self.is_dark_theme = self.detect_dark_theme()
        
        # 设置窗口居中
        self.center_window()
        
        # 初始化UI
        self.init_ui()
        
        # 设置默认焦点到输入框
        self.username_input.setFocus()
    
    def detect_dark_theme(self):
        """检测系统是否使用深色主题"""
        try:
            palette = QApplication.palette()
            # 检查窗口背景色是否较暗
            window_color = palette.color(QPalette.Window)
            # 如果背景色的亮度较低，认为是深色主题
            return window_color.lightness() < 128
        except:
            return False
        
    def center_window(self):
        """将窗口居中显示"""
        if self.parent():
            # 如果有父窗口，相对于父窗口居中
            parent_geometry = self.parent().geometry()
            x = parent_geometry.x() + (parent_geometry.width() - self.width()) // 2
            y = parent_geometry.y() + (parent_geometry.height() - self.height()) // 2
            self.move(x, y)
        else:
            # 如果没有父窗口，相对于屏幕居中
            screen = QApplication.primaryScreen().geometry()
            x = (screen.width() - self.width()) // 2
            y = (screen.height() - self.height()) // 2
            self.move(x, y)
    
    def init_ui(self):
        """初始化用户界面"""
        layout = QVBoxLayout()
        layout.setSpacing(25)
        layout.setContentsMargins(30, 30, 30, 30)
        
        # 标题
        title_label = QLabel("欢迎使用多功能聊天室")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title_label.setFont(title_font)
        title_label.setAlignment(Qt.AlignCenter)
        
        # 根据主题设置标题颜色
        if self.is_dark_theme:
            title_label.setStyleSheet("color: #E2E8F0; margin-bottom: 10px;")
        else:
            title_label.setStyleSheet("color: #2D3748; margin-bottom: 10px;")
        layout.addWidget(title_label)
        
        # 用户名输入框
        self.username_input = QLineEdit()
        self.username_input.setPlaceholderText("请输入用户名")
        
        # 根据主题设置输入框样式
        if self.is_dark_theme:
            self.username_input.setStyleSheet("""
                QLineEdit {
                    padding: 15px;
                    border: 2px solid #4A5568;
                    border-radius: 8px;
                    font-size: 14px;
                    background-color: #2D3748;
                    color: #E2E8F0;
                    min-height: 20px;
                }
                QLineEdit:focus {
                    border-color: #3182CE;
                    outline: none;
                }
                QLineEdit::placeholder {
                    color: #A0AEC0;
                    font-style: italic;
                }
            """)
        else:
            self.username_input.setStyleSheet("""
                QLineEdit {
                    padding: 15px;
                    border: 2px solid #E2E8F0;
                    border-radius: 8px;
                    font-size: 14px;
                    background-color: white;
                    color: #2D3748;
                    min-height: 20px;
                }
                QLineEdit:focus {
                    border-color: #3182CE;
                    outline: none;
                }
                QLineEdit::placeholder {
                    color: #718096;
                    font-style: italic;
                }
            """)
        layout.addWidget(self.username_input)
        
        # 按钮布局
        button_layout = QHBoxLayout()
        button_layout.setSpacing(15)
        
        # 确认按钮
        self.confirm_button = QPushButton("确认")
        if self.is_dark_theme:
            self.confirm_button.setStyleSheet("""
                QPushButton {
                    background-color: #3182CE;
                    color: white;
                    border: none;
                    padding: 15px 24px;
                    border-radius: 8px;
                    font-size: 14px;
                    font-weight: bold;
                    min-height: 20px;
                }
                QPushButton:hover {
                    background-color: #2C5AA0;
                }
                QPushButton:pressed {
                    background-color: #1E3A8A;
                }
            """)
        else:
            self.confirm_button.setStyleSheet("""
                QPushButton {
                    background-color: #3182CE;
                    color: white;
                    border: none;
                    padding: 15px 24px;
                    border-radius: 8px;
                    font-size: 14px;
                    font-weight: bold;
                    min-height: 20px;
                }
                QPushButton:hover {
                    background-color: #2C5AA0;
                }
                QPushButton:pressed {
                    background-color: #1E3A8A;
                }
            """)
        self.confirm_button.clicked.connect(self.confirm_input)
        
        # 取消按钮
        self.cancel_button = QPushButton("取消")
        if self.is_dark_theme:
            self.cancel_button.setStyleSheet("""
                QPushButton {
                    background-color: #4A5568;
                    color: #E2E8F0;
                    border: 1px solid #718096;
                    padding: 15px 24px;
                    border-radius: 8px;
                    font-size: 14px;
                    min-height: 20px;
                }
                QPushButton:hover {
                    background-color: #718096;
                }
                QPushButton:pressed {
                    background-color: #A0AEC0;
                }
            """)
        else:
            self.cancel_button.setStyleSheet("""
                QPushButton {
                    background-color: #E2E8F0;
                    color: #4A5568;
                    border: 1px solid #CBD5E0;
                    padding: 15px 24px;
                    border-radius: 8px;
                    font-size: 14px;
                    min-height: 20px;
                }
                QPushButton:hover {
                    background-color: #CBD5E0;
                }
                QPushButton:pressed {
                    background-color: #A0AEC0;
                }
            """)
        self.cancel_button.clicked.connect(self.reject)
        
        button_layout.addWidget(self.confirm_button)
        button_layout.addWidget(self.cancel_button)
        layout.addLayout(button_layout)
        
        # 设置主布局
        self.setLayout(layout)
        
        # 连接回车键事件
        self.username_input.returnPressed.connect(self.confirm_input)
        
    def confirm_input(self):
        """确认输入"""
        username = self.username_input.text().strip()
        
        # 如果用户名为空，使用默认值
        if not username:
            username = "匿名用户"
        
        # 验证用户名长度
        if len(username) > 20:
            QMessageBox.warning(self, "输入错误", "用户名不能超过20个字符！")
            return
        
        # 验证用户名是否包含非法字符
        invalid_chars = ['|', '\\', '/', ':', '*', '?', '"', '<', '>']
        for char in invalid_chars:
            if char in username:
                QMessageBox.warning(self, "输入错误", f"用户名不能包含字符：{char}")
                return
        
        # 生成用户ID（基于用户名的哈希值）
        user_id = hash(username) % 10000
        
        # 发射信号
        self.username_confirmed.emit(username, user_id)
        
        # 关闭对话框
        self.accept()
    
    def keyPressEvent(self, event):
        """处理键盘事件"""
        if event.key() == Qt.Key_Escape:
            self.reject()
        else:
            super().keyPressEvent(event)


def get_username_from_dialog():
    """
    通过弹窗获取用户名，并生成用户ID。
    如果用户取消，返回 (None, None)。
    """
    app = QApplication.instance()
    if app is None:
        app = QApplication([])
    
    dialog = UsernameDialog()
    
    # 存储结果的变量
    result_username = None
    result_user_id = None
    
    def on_username_confirmed(username, user_id):
        nonlocal result_username, result_user_id
        result_username = username
        result_user_id = user_id
        print(f"[调试] 用户名: {username}, 用户ID: {user_id}")
    
    # 连接信号
    dialog.username_confirmed.connect(on_username_confirmed)
    
    # 显示对话框
    if dialog.exec() == QDialog.Accepted:
        return result_username, result_user_id
    else:
        print("[调试] 用户取消了输入")
        return None, None


if __name__ == '__main__':
    # 仅用于测试对话框功能
    import sys
    app = QApplication(sys.argv)
    name, uid = get_username_from_dialog()
    if name:
        print(f"获取到的用户名: {name}, ID: {uid}")
    else:
        print("未输入用户名")
    sys.exit(app.exec())