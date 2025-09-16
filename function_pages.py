# 功能页面模块
from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QLabel, 
                               QListWidget, QListWidgetItem, QPushButton, 
                               QLineEdit, QTextEdit, QFrame, QScrollArea)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QFont

class ChatPage(QWidget):
    """聊天页面 - 复用现有的聊天功能"""
    
    def __init__(self, chat_ui):
        super().__init__()
        self.chat_ui = chat_ui
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # 将聊天UI嵌入到页面中
        layout.addWidget(self.chat_ui)

class CanvasPage(QWidget):
    """共享画布页面"""
    
    def __init__(self, username="匿名用户", dds_manager=None):
        super().__init__()
        self.username = username
        self.dds_manager = dds_manager
        self.canvas_window = None
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(20, 20, 20, 20)
        
        # 标题
        title_label = QLabel("🎨 共享画布")
        title_label.setFont(QFont("Microsoft YaHei", 18, QFont.Bold))
        title_label.setAlignment(Qt.AlignCenter)
        title_label.setStyleSheet("color: #4299e1; margin-bottom: 20px;")
        
        # 描述
        desc_label = QLabel("点击下方按钮打开共享画板，与其他人一起创作！")
        desc_label.setFont(QFont("Microsoft YaHei", 12))
        desc_label.setAlignment(Qt.AlignCenter)
        desc_label.setStyleSheet("color: #a0aec0; margin-bottom: 30px;")
        
        # 启动画板按钮
        self.start_canvas_btn = QPushButton("🚀 启动共享画板")
        self.start_canvas_btn.setFont(QFont("Microsoft YaHei", 14, QFont.Bold))
        self.start_canvas_btn.setFixedHeight(60)
        self.start_canvas_btn.setStyleSheet("""
            QPushButton {
                background-color: #4299e1;
                color: white;
                border: none;
                border-radius: 8px;
                padding: 10px;
            }
            QPushButton:hover {
                background-color: #3182ce;
            }
            QPushButton:pressed {
                background-color: #2c5282;
            }
        """)
        self.start_canvas_btn.clicked.connect(self.open_canvas)
        
        # 功能说明
        features_label = QLabel("""
        <h3>功能特点：</h3>
        <ul>
        <li>🎨 实时共享绘画</li>
        <li>👥 多用户协作</li>
        <li>🎯 颜色和粗细调节</li>
        <li>🧹 橡皮擦功能</li>
        <li>🏷️ 用户标签显示</li>
        </ul>
        """)
        features_label.setFont(QFont("Microsoft YaHei", 10))
        features_label.setStyleSheet("color: #e2e8f0; margin-top: 30px;")
        
        # 添加到布局
        layout.addStretch()
        layout.addWidget(title_label)
        layout.addWidget(desc_label)
        layout.addWidget(self.start_canvas_btn)
        layout.addWidget(features_label)
        layout.addStretch()
        
    def open_canvas(self):
        """打开画板窗口"""
        try:
            from canvas_window import open_canvas_window
            if self.canvas_window is None or not self.canvas_window.isVisible():
                self.canvas_window = open_canvas_window(self.username, self.dds_manager)
                if self.canvas_window:
                    print(f"✅ 画板窗口已打开，用户: {self.username}")
                else:
                    print("❌ 画板窗口打开失败")
            else:
                # 如果窗口已经打开，将其提到前台
                self.canvas_window.raise_()
                self.canvas_window.activateWindow()
        except Exception as e:
            print(f"[错误] 打开画板窗口失败: {e}")
            from PySide6.QtWidgets import QMessageBox
            QMessageBox.critical(self, "错误", f"打开画板窗口失败: {e}")
    
    def set_username(self, username):
        """设置用户名"""
        self.username = username
        
class SnakePage(QWidget):
    """贪吃蛇页面"""
    
    def __init__(self, username: str, user_id: int):
        super().__init__()
        self.username = username
        self.user_id = user_id
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        from snake import Snake
        self.widget = Snake(self.username, self.user_id)
        layout.addWidget(self.widget)