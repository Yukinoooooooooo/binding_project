# -*- coding: utf-8 -*-
# 主UI界面 - 整合功能栏和聊天功能
from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QFrame, 
                               QLabel, QPushButton, QHBoxLayout, QSizePolicy)
from PySide6.QtCore import Qt, Signal, QPoint
from PySide6.QtGui import QFont

from chat_ui import ChatUI
from function_manager import FunctionManager
from function_pages import (ChatPage, CanvasPage, SnakePage)

class CustomTitleBar(QWidget):
    """自定义标题栏"""
    
    def __init__(self, parent):
        super().__init__()
        self.parent = parent
        self.init_ui()
        
    def init_ui(self):
        self.setFixedHeight(40)
        self.setStyleSheet("""
            QWidget {
                background-color: #1a202c;
                border: none;
            }
        """)
        
        layout = QHBoxLayout(self)
        layout.setContentsMargins(15, 8, 8, 8)
        layout.setSpacing(10)
        
        # 应用图标和标题
        icon_label = QLabel("💬")
        icon_label.setFont(QFont("Microsoft YaHei", 14))
        icon_label.setStyleSheet("color: #4299e1;")
        
        title_label = QLabel("多功能聊天室")
        title_label.setFont(QFont("Microsoft YaHei", 12, QFont.Bold))
        title_label.setStyleSheet("color: #ffffff;")
        
        layout.addWidget(icon_label)
        layout.addWidget(title_label)
        layout.addStretch()
        
        # 窗口控制按钮
        self.minimize_btn = QPushButton("−")
        self.maximize_btn = QPushButton("□")
        self.close_btn = QPushButton("×")
        
        for btn in [self.minimize_btn, self.maximize_btn, self.close_btn]:
            btn.setFixedSize(30, 24)
            btn.setFont(QFont("Microsoft YaHei", 12, QFont.Bold))
            btn.setStyleSheet("""
                QPushButton {
                    background-color: transparent;
                    border: none;
                    color: #a0aec0;
                    border-radius: 4px;
                }
                QPushButton:hover {
                    background-color: #4a5568;
                    color: #ffffff;
                }
            """)
            layout.addWidget(btn)
        
        # 连接按钮事件
        self.minimize_btn.clicked.connect(self.parent.showMinimized)
        self.maximize_btn.clicked.connect(self.toggle_maximize)
        self.close_btn.clicked.connect(self.parent.close)
        
        # 设置关闭按钮特殊样式
        self.close_btn.setStyleSheet("""
            QPushButton {
                background-color: transparent;
                border: none;
                color: #a0aec0;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #e53e3e;
                color: #ffffff;
            }
        """)
        
    def toggle_maximize(self):
        """切换最大化状态"""
        if self.parent.isMaximized():
            self.parent.showNormal()
            self.maximize_btn.setText("□")
        else:
            self.parent.showMaximized()
            self.maximize_btn.setText("❐")
    
    def mousePressEvent(self, event):
        """鼠标按下事件 - 用于拖拽窗口"""
        if event.button() == Qt.LeftButton:
            self.drag_position = event.globalPosition().toPoint() - self.parent.frameGeometry().topLeft()
            event.accept()
        else:
            # 将其他事件传递给父窗口
            super().mousePressEvent(event)
    
    def mouseMoveEvent(self, event):
        """鼠标移动事件 - 拖拽窗口"""
        if event.buttons() == Qt.LeftButton and hasattr(self, 'drag_position'):
            self.parent.move(event.globalPosition().toPoint() - self.drag_position)
            event.accept()
        else:
            # 将其他事件传递给父窗口
            super().mouseMoveEvent(event)
    
    def mouseReleaseEvent(self, event):
        """鼠标释放事件"""
        if hasattr(self, 'drag_position'):
            delattr(self, 'drag_position')
        # 将事件传递给父窗口
        super().mouseReleaseEvent(event)

class MainUI(QWidget):
    """主UI界面 - 包含功能栏和内容区域"""
    
    def __init__(self, username="我", user_id=0, dds_manager=None):
        super().__init__()
        self.username = username
        self.user_id = user_id
        self.dds_manager = dds_manager
        self.init_ui()
        
    def init_ui(self):
        self.setWindowTitle("多功能聊天室")
        # 使用无边框窗口
        self.setWindowFlags(Qt.Window | Qt.FramelessWindowHint)
        self.resize(1200, 800)  # 增加宽度和高度以容纳功能栏和聊天界面
        
        # 设置最小窗口尺寸，确保小窗口时也能看到输入框
        self.setMinimumSize(800, 600)
        

        # 主布局
        main_layout = QVBoxLayout(self)
        main_layout.setContentsMargins(0, 0, 0, 0)
        main_layout.setSpacing(0)
        
        # 添加自定义标题栏
        self.title_bar = CustomTitleBar(self)
        main_layout.addWidget(self.title_bar)
        
        # 内容区域布局
        content_layout = QHBoxLayout()
        content_layout.setContentsMargins(0, 0, 0, 0)
        content_layout.setSpacing(0)
        
        # 创建功能管理器
        self.function_manager = FunctionManager()
        
        # 添加功能栏到左侧
        content_layout.addWidget(self.function_manager.get_sidebar())
        
        # 创建内容区域
        self.create_content_area(content_layout)
        
        # 将内容布局添加到主布局
        main_layout.addLayout(content_layout)
        
        # 设置主题样式
        self.setup_theme()
        
        
    def create_content_area(self, parent_layout):
        """创建内容区域"""
        # 内容区域容器
        content_frame = QFrame()
        content_frame.setStyleSheet("background-color: #1a202c;")
        content_layout = QVBoxLayout(content_frame)
        content_layout.setContentsMargins(0, 0, 0, 0)
        content_layout.setSpacing(0)
        
        # 添加功能页面容器
        self.pages_container = self.function_manager.get_pages()
        content_layout.addWidget(self.pages_container)
        
        # 创建聊天UI（作为聊天页面）
        self.chat_ui = ChatUI(self.username, self.user_id)
        chat_page = ChatPage(self.chat_ui)
        
        # 创建其他功能页面
        Canvas_page = CanvasPage(self.username, self.dds_manager)
        snake_page = SnakePage(self.username, self.user_id)
 
        # 添加所有页面到功能管理器
        self.function_manager.add_function_page("聊天", chat_page)
        self.function_manager.add_function_page("共享画布", Canvas_page)
        self.function_manager.add_function_page("贪吃蛇", snake_page)
        # 默认显示聊天页面
        self.function_manager.pages.switch_to_page("聊天")
        
        parent_layout.addWidget(content_frame)
        
    def setup_theme(self):
        """设置主题样式"""
        self.setStyleSheet("""
            QWidget {
                background-color: #1a202c;
                color: #ffffff;
                border: none;
            }
        """)
        
    def get_chat_ui(self):
        """获取聊天UI对象"""
        return self.chat_ui
        
    def get_function_manager(self):
        """获取功能管理器"""
        return self.function_manager
