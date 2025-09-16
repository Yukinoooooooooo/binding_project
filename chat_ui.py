# -*- coding: utf-8 -*-
# 聊天界面UI模块
import time
from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, 
                               QLineEdit, QPushButton, QLabel, QFrame, 
                               QScrollArea, QSizePolicy, QListWidgetItem)
from PySide6.QtCore import Qt, Signal, QTimer
from PySide6.QtGui import QFont, QFontMetrics

class TopicItem(QWidget):
    """主题列表项"""
    topicSelected = Signal(str)
    
    def __init__(self, topic_name, parent=None, is_selected=False):
        super().__init__()
        self.topic_name = topic_name
        self.parent = parent
        self.is_selected = is_selected
        self.init_ui()
        
    def init_ui(self):
        self.setFixedHeight(50)
        layout = QHBoxLayout(self)
        layout.setContentsMargins(15, 8, 15, 8)
        layout.setSpacing(12)
        
        # 主题图标 - 圆形头像
        self.icon_label = QLabel()
        self.icon_label.setFixedSize(32, 32)
        self.icon_label.setStyleSheet("""
            QLabel {
                background-color: #4a5568;
                border-radius: 16px;
                color: white;
                font-size: 14px;
                font-weight: bold;
            }
        """)

        self.icon_label.setAlignment(Qt.AlignCenter)
        self.icon_label.setText(self.topic_name[:2].upper())
        
        # 主题名称
        self.name_label = QLabel(self.topic_name)
        self.name_label.setFont(QFont("Microsoft YaHei", 11))
        self.name_label.setStyleSheet("border: none; background: transparent;")
        
        # 在线状态指示器（绿色小圆点）
        self.status_dot = QLabel("●")
        self.status_dot.setFixedSize(12, 12)
        self.status_dot.setStyleSheet("color: #48bb78; font-size: 8px; border: none; background: transparent;")
        self.status_dot.setAlignment(Qt.AlignCenter)
        
        layout.addWidget(self.icon_label)
        layout.addWidget(self.name_label)
        layout.addStretch()
        layout.addWidget(self.status_dot)
        
        self.update_style()
        
    def update_style(self):
        if self.is_selected:
            self.setStyleSheet("""
                TopicItem {
                    background-color: #2d3748;
                    border: none;
                }
            """)
            self.name_label.setStyleSheet("color: #ffffff; font-weight: bold; border: none; background: transparent;")
        else:
            self.setStyleSheet("""
                TopicItem {
                    background-color: transparent;
                    border: none;
                }
                TopicItem:hover {
                    background-color: #1a202c;
                }
            """)
            self.name_label.setStyleSheet("color: #a0aec0; border: none; background: transparent;")
    
    def set_selected(self, selected):
        self.is_selected = selected
        self.update_style()
    
    def update_unread(self, count):
        """更新未读消息数"""
        pass  # 暂时不显示未读消息数
    
    def mousePressEvent(self, event):
        """鼠标点击事件"""
        if event.button() == Qt.LeftButton:
            print(f"[调试] 点击主题: {self.topic_name}")
            self.topicSelected.emit(self.topic_name)
        super().mousePressEvent(event)

class ChatUI(QWidget):
    sendMessage = Signal(str, str)  # topic, message
    showMessage = Signal(str, str, str)  # topic, sender_name, msg
    userJoined = Signal(str, str)  # topic, username
    userLeft = Signal(str, str)  # topic, username
    newTopicCreated = Signal(str)  # topic_name
    topicDeleted = Signal(str)  # topic_name

    def __init__(self, username="我", user_id=0, dds_manager=None):
        super().__init__()
        self.username = username
        self.user_id = user_id
        self.dds_manager = dds_manager
        self.current_topic = "多功能聊天室"
        self.topic_messages = {}  # 存储每个主题的消息历史
        self.topic_items = {}  # 存储主题项
        self.topic_unread = {}  # 存储未读消息数
        self.joined_users = {}  # 存储每个主题已显示加入提示的用户
        self.online_users = {}  # 存储每个主题的在线用户列表
        self.init_ui()
        
        # 将自己添加到所有主题的在线用户列表中
        self.add_self_to_all_topics()
        self.showMessage.connect(self.append_message)
        self.userJoined.connect(self.handle_user_join)
        self.userLeft.connect(self.handle_user_leave)
        self.newTopicCreated.connect(self.handle_new_topic_created)
        self.topicDeleted.connect(self.handle_topic_deleted)
        
        # 连接DDS管理器的信号
        if self.dds_manager and self.dds_manager.proxy:
            self.dds_manager.proxy.userJoined.connect(self.handle_user_join)
            self.dds_manager.proxy.userLeft.connect(self.handle_user_leave)
            self.dds_manager.proxy.newTopicCreated.connect(self.handle_new_topic_created)
            self.dds_manager.proxy.topicDeleted.connect(self.handle_topic_deleted)
            print(f"[调试] DDS管理器信号连接完成")
        self.setup_exact_theme()

    def setup_exact_theme(self):
        """严格按照图片设置主题"""
        self.setStyleSheet("""
            QWidget {
                background-color: #1a202c;
                color: #ffffff;
                border: none;
            }
            QFrame {
                background-color: #1a202c;
                border: none;
            }
            QLineEdit {
                background-color: #2d3748;
                border: 1px solid #4a5568;
                border-radius: 8px;
                padding: 12px;
                color: #ffffff;
                font-size: 14px;
                font-family: 'Microsoft YaHei';
                outline: none;
            }
            QLineEdit:focus {
                border: 1px solid #4299e1;
                outline: none;
            }
            QLineEdit:focus-visible {
                outline: none;
            }
            QPushButton {
                background-color: #4299e1;
                border: none;
                border-radius: 8px;
                padding: 12px 20px;
                color: white;
                font-weight: bold;
                font-size: 14px;
                font-family: 'Microsoft YaHei';
            }
            QPushButton:hover {
                background-color: #3182ce;
            }
            QPushButton:pressed {
                background-color: #2c5282;
            }
            QTextBrowser {
                background-color: #1a202c;
                border: none;
                padding: 15px;
                color: #ffffff;
                font-size: 14px;
                font-family: 'Microsoft YaHei';
                line-height: 1.5;
            }
            QScrollBar:vertical {
                background-color: #2d3748;
                width: 8px;
                border-radius: 4px;
            }
            QScrollBar::handle:vertical {
                background-color: #4a5568;
                border-radius: 4px;
                min-height: 20px;
            }
            QScrollBar::handle:vertical:hover {
                background-color: #718096;
            }
        """)

    def init_ui(self):
        # 当作为嵌入组件时，不设置窗口标志和大小
        # self.setWindowTitle("多功能聊天室")
        # self.setWindowFlags(Qt.Window | Qt.WindowCloseButtonHint | Qt.WindowMaximizeButtonHint)
        # self.resize(1200, 800)
        
        # 主布局
        main_layout = QHBoxLayout(self)
        main_layout.setContentsMargins(0, 0, 0, 0)
        main_layout.setSpacing(0)
        
        # 设置主布局的大小策略
        self.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
        
        # 左侧主题列表
        self.create_topic_sidebar(main_layout)
        
        # 右侧聊天区域
        self.create_chat_area(main_layout)
        
        # 初始化主题
        self.init_topics()

    def create_topic_sidebar(self, parent_layout):
        """创建左侧主题栏 - 严格按照图片样式"""
        sidebar_frame = QFrame()
        sidebar_frame.setFixedWidth(280)
        sidebar_frame.setSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sidebar_frame.setStyleSheet("background-color: #1a202c; border-right: 1px solid #2d3748;")
        sidebar_layout = QVBoxLayout(sidebar_frame)
        sidebar_layout.setContentsMargins(0, 0, 0, 0)
        sidebar_layout.setSpacing(0)
        
        # 顶部标题区域 - 作为主题名字
        header_frame = QFrame()
        header_frame.setFixedHeight(80)
        header_frame.setStyleSheet("background-color: #1a202c; border-bottom: 1px solid #2d3748;")
        header_layout = QHBoxLayout(header_frame)
        header_layout.setContentsMargins(20, 15, 20, 15)
        header_layout.setSpacing(15)
        
        # 圆形图标
        icon_label = QLabel("BP")
        icon_label.setFixedSize(50, 50)
        icon_label.setStyleSheet("""
            QLabel {
                background-color: #4299e1;
                border-radius: 25px;
                color: white;
                font-size: 16px;
                font-weight: bold;
                font-family: 'Microsoft YaHei';
            }
        """)
        icon_label.setAlignment(Qt.AlignCenter)
        
        # 标题文字 - 作为主题名字
        title_layout = QVBoxLayout()
        title_layout.setSpacing(2)
        
        club_label = QLabel("CHATTING TOPIC")
        club_label.setFont(QFont("Microsoft YaHei", 8))
        club_label.setStyleSheet("color: #a0aec0; border: none; background: transparent;")
        
        main_title = QLabel("主题栏")
        main_title.setFont(QFont("Microsoft YaHei", 14, QFont.Bold))
        main_title.setStyleSheet("color: #ffffff; border: none; background: transparent;")
        
        title_layout.addWidget(club_label)
        title_layout.addWidget(main_title)
        
        header_layout.addWidget(icon_label)
        header_layout.addLayout(title_layout)
        header_layout.addStretch()
        
        sidebar_layout.addWidget(header_frame)
        
        # 新建主题按钮区域 - 独立区域
        button_frame = QFrame()
        button_frame.setFixedHeight(60)
        button_frame.setStyleSheet("background-color: #1a202c; border-bottom: 1px solid #2d3748;")
        button_layout = QHBoxLayout(button_frame)
        button_layout.setContentsMargins(15, 10, 15, 10)
        button_layout.setSpacing(8)
        
        self.create_topic_button = self.create_new_topic_button()
        self.discover_topics_button = self.create_discover_topics_button()
        
        button_layout.addWidget(self.create_topic_button)
        button_layout.addWidget(self.discover_topics_button)
        
        sidebar_layout.addWidget(button_frame)
        
        # 主题列表滚动区域
        self.topic_scroll_area = QScrollArea()
        self.topic_scroll_area.setWidgetResizable(True)
        self.topic_scroll_area.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAsNeeded)
        self.topic_scroll_area.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.topic_scroll_area.setStyleSheet("""
            QScrollArea {
                background-color: #1a202c;
                border: none;
            }
            QScrollBar:vertical {
                background-color: #2d3748;
                width: 8px;
                border-radius: 4px;
            }
            QScrollBar::handle:vertical {
                background-color: #4a5568;
                border-radius: 4px;
                min-height: 20px;
            }
            QScrollBar::handle:vertical:hover {
                background-color: #718096;
            }
        """)
        
        # 创建主题列表容器
        self.topic_container = QWidget()
        self.topic_list = QVBoxLayout(self.topic_container)
        self.topic_list.setSpacing(0)
        self.topic_list.setContentsMargins(0, 0, 0, 0)
        self.topic_scroll_area.setWidget(self.topic_container)
        
        sidebar_layout.addWidget(self.topic_scroll_area)
        
        # 在线用户列表区域
        self.create_online_users_section(sidebar_layout)
        
        sidebar_layout.addStretch()  
        parent_layout.addWidget(sidebar_frame)

    def create_online_users_section(self, parent_layout):
        """创建在线用户列表区域"""
        # 在线用户标题
        online_title_frame = QFrame()
        online_title_frame.setFixedHeight(40)
        online_title_frame.setStyleSheet("background-color: #1a202c; border-top: 1px solid #2d3748;")
        online_title_layout = QHBoxLayout(online_title_frame)
        online_title_layout.setContentsMargins(15, 8, 15, 8)
        
        online_title_label = QLabel("在线用户")
        online_title_label.setFont(QFont("Microsoft YaHei", 10, QFont.Bold))
        online_title_label.setStyleSheet("color: #a0aec0; border: none; background: transparent;")
        online_title_layout.addWidget(online_title_label)
        
        # 在线人数标签
        self.online_count_label = QLabel("(0)")
        self.online_count_label.setFont(QFont("Microsoft YaHei", 9))
        self.online_count_label.setStyleSheet("color: #718096; border: none; background: transparent;")
        online_title_layout.addWidget(self.online_count_label)
        online_title_layout.addStretch()
        
        parent_layout.addWidget(online_title_frame)
        
        # 在线用户列表容器
        self.online_users_container = QFrame()
        self.online_users_container.setStyleSheet("background-color: #1a202c;")
        self.online_users_layout = QVBoxLayout(self.online_users_container)
        self.online_users_layout.setContentsMargins(15, 5, 15, 5)
        self.online_users_layout.setSpacing(3)
        
        parent_layout.addWidget(self.online_users_container)

    def create_new_topic_button(self):
        """创建新主题按钮"""
        button = QPushButton("+ 新建主题")
        button.setFixedHeight(40)
        button.setMinimumWidth(120)
        
        # 设置字体
        font = QFont("Microsoft YaHei", 12, QFont.Bold)
        button.setFont(font)
        
        button.setStyleSheet("""
            QPushButton {
                background-color: #2d3748;
                color: #a0aec0;
                border: 1px solid #4a5568;
                border-radius: 6px;
                font-size: 12px;
                font-weight: bold;
                padding: 8px 12px;
                text-align: left;
            }
            QPushButton:hover {
                background-color: #4a5568;
                color: #e2e8f0;
            }
            QPushButton:pressed {
                background-color: #1a202c;
            }
        """)
        button.clicked.connect(self.show_create_topic_dialog)
        return button

    def create_discover_topics_button(self):
        """创建发现主题按钮"""
        button = QPushButton("🔍 发现主题")
        button.setFixedHeight(40)
        button.setMinimumWidth(120)
        
        # 设置字体
        font = QFont("Microsoft YaHei", 12, QFont.Bold)
        button.setFont(font)
        
        button.setStyleSheet("""
            QPushButton {
                background-color: #4299e1;
                color: #ffffff;
                border: 1px solid #3182ce;
                border-radius: 6px;
                font-size: 12px;
                font-weight: bold;
                padding: 8px 12px;
                text-align: left;
            }
            QPushButton:hover {
                background-color: #3182ce;
                color: #ffffff;
            }
            QPushButton:pressed {
                background-color: #2c5282;
            }
        """)
        button.clicked.connect(self.show_discover_topics_dialog)
        return button

    def show_create_topic_dialog(self):
        """显示创建新主题对话框"""
        from PySide6.QtWidgets import QInputDialog
        
        topic_name, ok = QInputDialog.getText(
            self, 
            "创建新主题", 
            "请输入新主题名称:",
            text=""
        )
        
        if ok and topic_name.strip():
            topic_name = topic_name.strip()
            # 检查主题名是否已存在
            if topic_name in self.topic_items:
                # 使用控制台输出而不是弹窗，避免重叠
                print(f"[警告] 主题 '{topic_name}' 已存在！")
                return
            
            # 创建新主题
            self.create_new_topic(topic_name)

    def show_discover_topics_dialog(self):
        """显示发现主题对话框"""
        from PySide6.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, 
                                     QLabel, QPushButton, QListWidget, 
                                     QMessageBox)
        
        dialog = QDialog(self)
        dialog.setWindowTitle("发现主题")
        dialog.setFixedSize(400, 300)
        dialog.setStyleSheet("""
            QDialog {
                background-color: #1a202c;
                color: #ffffff;
            }
            QLabel {
                color: #ffffff;
                font-family: 'Microsoft YaHei';
            }
            QPushButton {
                background-color: #4299e1;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 8px 16px;
                font-weight: bold;
                font-family: 'Microsoft YaHei';
            }
            QPushButton:hover {
                background-color: #3182ce;
            }
            QPushButton:pressed {
                background-color: #2c5282;
            }
            QListWidget {
                background-color: #2d3748;
                border: 1px solid #4a5568;
                border-radius: 6px;
                color: #ffffff;
                font-family: 'Microsoft YaHei';
            }
            QListWidget::item {
                padding: 8px;
                border-bottom: 1px solid #4a5568;
            }
            QListWidget::item:selected {
                background-color: #4299e1;
            }
            QListWidget::item:hover {
                background-color: #4a5568;
            }
        """)
        
        layout = QVBoxLayout(dialog)
        layout.setSpacing(15)
        layout.setContentsMargins(20, 20, 20, 20)
        
        # 标题
        title_label = QLabel("发现可用的主题")
        title_label.setFont(QFont("Microsoft YaHei", 14, QFont.Bold))
        title_label.setStyleSheet("color: #ffffff; margin-bottom: 10px;")
        layout.addWidget(title_label)
        
        # 说明文字
        desc_label = QLabel("选择主题后点击订阅按钮，或双击主题名称直接订阅")
        desc_label.setFont(QFont("Microsoft YaHei", 10))
        desc_label.setStyleSheet("color: #a0aec0; margin-bottom: 10px;")
        layout.addWidget(desc_label)
        
        # 主题列表
        self.discovered_topics_list = QListWidget()
        self.discovered_topics_list.setStyleSheet("""
            QListWidget {
                background-color: #2d3748;
                border: 1px solid #4a5568;
                border-radius: 6px;
                color: #ffffff;
                font-family: 'Microsoft YaHei';
            }
            QListWidget::item {
                padding: 12px;
                border-bottom: 1px solid #4a5568;
                font-size: 12px;
            }
            QListWidget::item:selected {
                background-color: #4299e1;
            }
            QListWidget::item:hover {
                background-color: #4a5568;
            }
        """)
        layout.addWidget(self.discovered_topics_list)
        
        # 按钮区域
        button_layout = QHBoxLayout()
        button_layout.setSpacing(10)
        
        refresh_button = QPushButton("🔄 刷新")
        refresh_button.clicked.connect(lambda: self.refresh_discovered_topics())
        button_layout.addWidget(refresh_button)
        
        # 订阅按钮
        subscribe_button = QPushButton("📋 订阅选中主题")
        subscribe_button.clicked.connect(lambda: self.subscribe_selected_topic(dialog))
        button_layout.addWidget(subscribe_button)
        
        
        button_layout.addStretch()
        
        close_button = QPushButton("关闭")
        close_button.clicked.connect(dialog.accept)
        button_layout.addWidget(close_button)
        
        layout.addLayout(button_layout)
        
        # 连接双击事件
        self.discovered_topics_list.itemDoubleClicked.connect(
            lambda item: self.subscribe_to_topic(item.text(), dialog)
        )
        
        # 初始加载主题
        self.refresh_discovered_topics()
        
        dialog.exec()

    def subscribe_selected_topic(self, dialog):
        """订阅选中的主题"""
        current_item = self.discovered_topics_list.currentItem()
        if current_item:
            topic_name = current_item.text()
            self.subscribe_to_topic(topic_name, dialog)
        else:
            print("[提示] 请先选择一个主题！")

    def refresh_discovered_topics(self):
        """刷新发现的主题列表"""
        try:
            # 清空当前列表
            self.discovered_topics_list.clear()
            
            # 请求发现主题
            if self.dds_manager:
                self.dds_manager.request_topic_discovery()
                
                # 获取已发现的主题
                discovered_topics = self.dds_manager.get_discovered_topics()
                print(f"[调试] 从DDS获取到 {len(discovered_topics)} 个发现的主题")
                
                for topic in discovered_topics:
                    # 只显示未订阅的主题
                    if topic not in self.topic_items:
                        item = QListWidgetItem(f"📋 {topic}")
                        item.setText(topic)  # 存储实际的主题名
                        self.discovered_topics_list.addItem(item)
                        print(f"[调试] 添加发现主题到列表: {topic}")
            
            # 如果没有发现任何主题，不显示任何内容
            # 让列表保持空白状态
            
            print(f"[调试] 刷新发现主题列表，找到 {self.discovered_topics_list.count()} 个主题")
            
        except Exception as e:
            print(f"[错误] 刷新发现主题失败: {e}")
            import traceback
            traceback.print_exc()

    def handle_topic_discovered(self, topic_name):
        """处理发现的主题"""
        try:
            print(f"[调试] 处理发现的主题: {topic_name}")
            
            # 检查是否已经订阅
            if topic_name in self.topic_items:
                print(f"[调试] 主题 '{topic_name}' 已订阅，跳过")
                return
            
            # 添加到发现列表（如果对话框打开的话）
            if hasattr(self, 'discovered_topics_list') and self.discovered_topics_list:
                # 检查是否已经存在
                for i in range(self.discovered_topics_list.count()):
                    item = self.discovered_topics_list.item(i)
                    if item and item.text() == topic_name:
                        print(f"[调试] 主题 '{topic_name}' 已在发现列表中")
                        return
                
                # 现在不需要移除空项目，因为不会添加空项目
                
                item = QListWidgetItem(f"📋 {topic_name}")
                item.setText(topic_name)
                self.discovered_topics_list.addItem(item)
                print(f"[调试] 主题 '{topic_name}' 已添加到发现列表")
            
        except Exception as e:
            print(f"[错误] 处理发现主题失败: {e}")
            import traceback
            traceback.print_exc()

    def subscribe_to_topic(self, topic_name, dialog):
        """订阅主题"""
        try:
            print(f"[调试] 尝试订阅主题: {topic_name}")
            
            # 检查主题名称是否有效
            if not topic_name or not topic_name.strip() or topic_name == "__NO_TOPIC__":
                from PySide6.QtWidgets import QMessageBox
                QMessageBox.warning(dialog, "错误", "无效的主题名称！")
                return
            
            # 检查是否已经订阅
            if topic_name in self.topic_items:
                # 使用控制台输出而不是弹窗，避免重叠
                print(f"[提示] 您已经订阅了主题 '{topic_name}'！")
                return
            
            # 创建主题项
            topic_item = TopicItem(topic_name, self)
            self.topic_items[topic_name] = topic_item
            self.topic_list.addWidget(topic_item)
            
            # 连接点击信号
            topic_item.topicSelected.connect(self.select_topic)
            
            # 初始化主题相关数据
            self.topic_messages[topic_name] = []
            self.topic_unread[topic_name] = 0
            self.joined_users[topic_name] = set()
            self.online_users[topic_name] = set()
            
            # 将自己添加到新主题的在线用户列表
            self.online_users[topic_name].add(self.username)
            if self.dds_manager and topic_name in self.dds_manager.online_users:
                self.dds_manager.online_users[topic_name].add(self.username)
            
            # 通知DDS管理器订阅新主题
            if self.dds_manager:
                self.dds_manager.subscribe_to_topic(topic_name)
            
            # 立即更新在线用户显示
            self.update_online_users_display(topic_name)
            
            # 自动切换到新订阅的主题
            self.select_topic(topic_name)
            
            # 从发现列表中移除已订阅的主题
            if hasattr(self, 'discovered_topics_list') and self.discovered_topics_list:
                for i in range(self.discovered_topics_list.count()):
                    item = self.discovered_topics_list.item(i)
                    if item and item.text() == topic_name:
                        self.discovered_topics_list.takeItem(i)
                        break
            
            # 关闭对话框
            dialog.accept()
            
            # 使用状态栏或简单的提示，避免弹窗重叠
            print(f"[成功] 已成功订阅主题 '{topic_name}'！")
            
            print(f"[调试] 主题 '{topic_name}' 订阅成功")
            
        except Exception as e:
            print(f"[错误] 订阅主题失败: {e}")
            import traceback
            traceback.print_exc()
    

    def create_new_topic(self, topic_name):
        """创建新主题"""
        try:
            print(f"[调试] 创建新主题: {topic_name}")
            
            # 创建主题项
            topic_item = TopicItem(topic_name, self)
            self.topic_items[topic_name] = topic_item
            self.topic_list.addWidget(topic_item)
            
            # 连接点击信号
            topic_item.topicSelected.connect(self.select_topic)
            
            # 初始化主题相关数据
            self.topic_messages[topic_name] = []
            self.topic_unread[topic_name] = 0
            self.joined_users[topic_name] = set()
            self.online_users[topic_name] = set()
            
            # 将自己添加到新主题的在线用户列表
            self.online_users[topic_name].add(self.username)
            if self.dds_manager and topic_name in self.dds_manager.online_users:
                self.dds_manager.online_users[topic_name].add(self.username)
            
            # 通知DDS管理器创建新主题
            if self.dds_manager:
                self.dds_manager.create_new_topic(topic_name)
            
            # 立即更新在线用户显示（确保UI先更新）
            self.update_online_users_display(topic_name)
            
            # 自动切换到新创建的主题
            self.select_topic(topic_name)
            
            print(f"[调试] 新主题 '{topic_name}' 创建成功")
            
        except Exception as e:
            print(f"[错误] 创建新主题失败: {e}")
            import traceback
            traceback.print_exc()


    def create_chat_area(self, parent_layout):
        """创建右侧聊天区域 - 严格按照图片样式"""
        chat_frame = QFrame()
        chat_frame.setStyleSheet("background-color: #1a202c;")
        chat_layout = QVBoxLayout(chat_frame)
        chat_layout.setContentsMargins(0, 0, 0, 0)
        chat_layout.setSpacing(0)
        
        # 设置聊天框架的大小策略，使其能够响应窗口大小变化
        chat_frame.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
        
        # 聊天标题栏
        title_frame = QFrame()
        title_frame.setFixedHeight(80)
        title_frame.setStyleSheet("background-color: #1a202c; border-bottom: 1px solid #2d3748;")
        title_layout = QHBoxLayout(title_frame)
        title_layout.setContentsMargins(20, 15, 20, 15)
        title_layout.setSpacing(12)
        
        self.chat_title = QLabel("俱乐部")
        self.chat_title.setFont(QFont("Microsoft YaHei", 14, QFont.Bold))
        self.chat_title.setStyleSheet("color: #ffffff; border: none; background: transparent;")
        title_layout.addWidget(self.chat_title)
              
        chat_layout.addWidget(title_frame)
        
        # 消息显示区 - 使用滚动区域和动态气泡
        self.scroll_area = QScrollArea()
        self.scroll_area.setWidgetResizable(True)
        self.scroll_area.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        # 设置滚动区域的大小策略，使其能够扩展
        self.scroll_area.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
        self.scroll_area.setStyleSheet("""
            QScrollArea {
                background-color: #1a202c;
                border: none;
            }
            QScrollBar:vertical {
                background-color: #2d3748;
                width: 8px;
                border-radius: 4px;
            }
            QScrollBar::handle:vertical {
                background-color: #4a5568;
                border-radius: 4px;
                min-height: 20px;
            }
            QScrollBar::handle:vertical:hover {
                background-color: #718096;
            }
        """)
        
        # 创建聊天内容容器
        self.chat_container = QWidget()
        self.chat_layout = QVBoxLayout()
        self.chat_container.setLayout(self.chat_layout)
        self.scroll_area.setWidget(self.chat_container)
        
        chat_layout.addWidget(self.scroll_area)
        
        # 输入区域 - 保持深色风格
        input_frame = QFrame()
        input_frame.setFixedHeight(80)
        input_frame.setStyleSheet("background-color: #1a202c;")
        input_frame.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        input_layout = QHBoxLayout(input_frame)
        input_layout.setContentsMargins(20, 15, 20, 15)
        input_layout.setSpacing(12)
        
        # 左侧头像
        self.user_avatar = QLabel("我")
        self.user_avatar.setFixedSize(40, 40)
        self.user_avatar.setStyleSheet("""
            QLabel {
                background-color: #4299e1;
                border-radius: 20px;
                color: white;
                font-size: 14px;
                font-weight: bold;
                font-family: 'Microsoft YaHei';
            }
        """)
        self.user_avatar.setAlignment(Qt.AlignCenter)
        input_layout.addWidget(self.user_avatar)
        
        # 输入框 - 深色背景
        self.input_box = QLineEdit()
        self.input_box.setPlaceholderText("输入消息...")
        self.input_box.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        self.input_box.setStyleSheet("""
            QLineEdit {
                background-color: #2d3748;
                border: 1px solid #4a5568;
                border-radius: 8px;
                padding: 12px;
                color: #ffffff;
                font-size: 14px;
                font-family: 'Microsoft YaHei';
                outline: none;
            }
            QLineEdit:focus {
                border: 1px solid #4299e1;
                outline: none;
            }
            QLineEdit:focus-visible {
                outline: none;
            }
        """)
        self.input_box.returnPressed.connect(self.handle_send)
        input_layout.addWidget(self.input_box)
        
        # 发送按钮 - 蓝色按钮
        self.send_btn = QPushButton("发送")
        self.send_btn.setFixedSize(80, 40)
        self.send_btn.setStyleSheet("""
            QPushButton {
                background-color: #4299e1;
                border: none;
                border-radius: 8px;
                color: white;
                font-size: 14px;
                font-weight: bold;
                font-family: 'Microsoft YaHei';
            }
            QPushButton:hover {
                background-color: #3182ce;
            }
            QPushButton:pressed {
                background-color: #2c5282;
            }
        """)
        self.send_btn.clicked.connect(self.handle_send)
        input_layout.addWidget(self.send_btn)
        
        chat_layout.addWidget(input_frame)
        parent_layout.addWidget(chat_frame)

    def init_topics(self):
        """初始化主题列表"""
        topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
        for topic_name in topics:
            self.add_topic(topic_name)
            self.topic_unread[topic_name] = 0
        
        # 默认选择第一个主题
        if topics:
            self.select_topic(topics[0])

    def add_topic(self, topic_name):
        """添加主题到列表"""
        topic_item = TopicItem(topic_name, self)
        topic_item.topicSelected.connect(self.select_topic)
        self.topic_items[topic_name] = topic_item
        self.topic_list.addWidget(topic_item)

    def select_topic(self, topic_name):
        """选择主题"""
        print(f"[调试] 切换到主题: {topic_name}")
        
        # 更新选中状态
        for name, item in self.topic_items.items():
            item.set_selected(name == topic_name)
        
        # 更新当前主题
        self.current_topic = topic_name
        self.chat_title.setText(f"{topic_name}")
        
        # 清除未读计数
        self.topic_unread[topic_name] = 0
        if topic_name in self.topic_items:
            self.topic_items[topic_name].update_unread(0)
        
        # 刷新消息显示
        self.refresh_messages()
        
        # 更新在线用户列表显示
        self.update_online_users_display(topic_name)
        
        # 延迟刷新机制：确保主题切换后用户状态完全同步
        from PySide6.QtCore import QTimer
        QTimer.singleShot(300, lambda: self.update_online_users_display(topic_name))

    def refresh_messages(self):
        """刷新当前主题的消息显示"""
        print(f"[调试] 刷新消息显示，当前主题: {self.current_topic}")
        
        # 清空当前聊天布局
        while self.chat_layout.count():
            child = self.chat_layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()
            elif child.layout():
                # 处理布局项
                self._clear_layout(child.layout())
                child.layout().deleteLater()
        
        # 重新显示该主题的消息历史
        if self.current_topic in self.topic_messages:
            print(f"[调试] 显示 {len(self.topic_messages[self.current_topic])} 条历史消息")
            for message_data in self.topic_messages[self.current_topic]:
                # 检查是否是系统消息
                if message_data.get('is_system', False):
                    print(f"[调试] 显示系统消息: {message_data['message']}")
                    self.add_system_message(message_data['message'])
                else:
                    # 普通消息使用气泡显示
                    self.add_message_bubble(
                        message_data['message'], 
                        message_data['is_sender'], 
                        message_data['sender'], 
                        message_data['time']
                    )
        else:
            print(f"[调试] 主题 {self.current_topic} 没有历史消息")
        
        # 添加伸缩组件，确保消息从顶部开始显示
        self.chat_layout.addStretch()
    
    def _clear_layout(self, layout):
        """递归清空布局中的所有组件"""
        while layout.count():
            child = layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()
            elif child.layout():
                self._clear_layout(child.layout())
                child.layout().deleteLater()

    def handle_send(self):
        text = self.input_box.text().strip()
        if text and self.current_topic:
            self.sendMessage.emit(self.current_topic, text)
            self.input_box.clear()

    def format_time(self):
        """格式化当前时间"""
        return time.strftime("%H:%M", time.localtime())
    
    def wrap_text(self, message, font, max_width):
        """文本自动换行功能"""
        font_metrics = QFontMetrics(font)
        lines = []
        current_line = ""

        for char in message:
            test_line = current_line + char
            text_line_width = font_metrics.horizontalAdvance(test_line)
            if text_line_width > max_width:
                lines.append(current_line.strip())
                current_line = char
            else:
                current_line = test_line

        if current_line:
            lines.append(current_line.strip())

        wrapped_text = "\n".join(lines)
        return wrapped_text
    
    def scroll_to_bottom(self):
        """将滚动条滚动到底部"""
        scroll_bar = self.scroll_area.verticalScrollBar()
        QTimer.singleShot(100, lambda: scroll_bar.setValue(scroll_bar.maximum()))

    def append_message(self, topic, sender, message):
        try:
            print(f"[调试] 尝试显示消息: {topic} - {sender}: {message}")
            print(f"[调试] 当前用户名: {self.username}, 发送者: {sender}")
            
            # 判断是否为自己发送的消息
            is_own_message = (sender == self.username)
            print(f"[调试] 是否为自己的消息: {is_own_message}")
            
            # 获取当前时间
            current_time = self.format_time()
            
            # 将消息存储到对应主题的历史记录中
            if topic not in self.topic_messages:
                self.topic_messages[topic] = []
            
            # 存储消息数据为字典格式
            message_data = {
                'message': message,
                'is_sender': is_own_message,
                'sender': sender,
                'time': current_time
            }
            self.topic_messages[topic].append(message_data)
            
            # 如果当前显示的是这个消息的主题，则立即显示
            if topic == self.current_topic:
                self.add_message_bubble(message, is_own_message, sender, current_time)
            else:
                # 更新未读计数
                if not is_own_message:
                    self.topic_unread[topic] = self.topic_unread.get(topic, 0) + 1
                    if topic in self.topic_items:
                        self.topic_items[topic].update_unread(self.topic_unread[topic])
            
            print(f"[调试] 消息显示完成")
        except Exception as e:
            print(f"[错误] 显示消息出错: {e}")
            import traceback
            traceback.print_exc()
    
    def add_message_bubble(self, message, is_sender=True, sender_name="", current_time=""):
        """添加消息气泡到聊天界面"""
        # 检查当前布局中的组件数量，移除原来的伸缩组件
        if self.chat_layout.count() > 0:
            # 移除最后一个伸缩组件
            last_item = self.chat_layout.takeAt(self.chat_layout.count() - 1)
            if last_item and last_item.widget():
                last_item.widget().deleteLater()
        
        # 创建消息标签
        message_label = QLabel(message)
        message_label.setWordWrap(False)  # 关闭自动换行，使用自定义换行
        font = QFont("Microsoft YaHei", 12)
        message_label.setFont(font)
        message_label.setTextInteractionFlags(Qt.TextInteractionFlag.TextSelectableByMouse)
        
        # 设置最大宽度
        text_max_width = 300
        message_label_max_width = text_max_width + 50
        message_label.setMaximumWidth(message_label_max_width)
        
        # 应用文本换行
        wrapped_text = self.wrap_text(message, font, text_max_width)
        message_label.setText(wrapped_text)
        
        # 设置大小策略
        message_label.setSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Minimum)
        
        # 创建时间标签
        time_label = QLabel(current_time)
        time_label.setFont(QFont("Microsoft YaHei", 9))
        time_label.setStyleSheet("color: #a0aec0;")
        
        # 创建消息容器
        message_container = QWidget()
        message_container_layout = QVBoxLayout(message_container)
        message_container_layout.setContentsMargins(0, 0, 0, 0)
        message_container_layout.setSpacing(2)
        
        # 添加发送者名字标签（所有消息都显示发送者）
        if sender_name:
            sender_label = QLabel(sender_name)
            sender_label.setFont(QFont("Microsoft YaHei", 9))
            sender_label.setStyleSheet("color: #a0aec0;")
            # 根据消息类型设置对齐方式
            if is_sender:
                sender_label.setAlignment(Qt.AlignRight)
            else:
                sender_label.setAlignment(Qt.AlignLeft)
            message_container_layout.addWidget(sender_label)
        

        message_container_layout.addWidget(message_label)
        message_container_layout.addWidget(time_label)
        
        # 创建水平布局来管理消息的对齐方式
        message_layout = QHBoxLayout()
        message_layout.setContentsMargins(15, 5, 15, 5)
        
        if is_sender:
            # 发送的消息 - 右侧显示，绿色气泡
            message_label.setStyleSheet("""
                QLabel {
                    background-color: #dcf8c6;
                    color: #333;
                    padding: 10px 15px;
                    border-radius: 18px;
                    border-bottom-right-radius: 4px;
                    font-size: 12px;
                    line-height: 1.4;
                }
            """)
            time_label.setStyleSheet("color: #a0aec0;")
            time_label.setAlignment(Qt.AlignRight)
            message_layout.addStretch()
            message_layout.addWidget(message_container)
        else:
            # 接收的消息 - 左侧显示，白色气泡
            message_label.setStyleSheet("""
                QLabel {
                    background-color: #f1f1f1;
                    color: #333;
                    padding: 10px 15px;
                    border-radius: 18px;
                    border-bottom-left-radius: 4px;
                    font-size: 12px;
                    line-height: 1.4;
                }
            """)
            time_label.setStyleSheet("color: #a0aec0;")
            time_label.setAlignment(Qt.AlignLeft)
            message_layout.addWidget(message_container)
            message_layout.addStretch()
        
        # 将水平布局添加到聊天布局中
        self.chat_layout.addLayout(message_layout)
        self.chat_layout.addStretch()
        
        # 滚动到底部
        self.scroll_to_bottom()
    
    def update_online_users_display(self, topic):
        """更新在线用户列表显示"""
        try:
            # 清空当前显示
            while self.online_users_layout.count():
                child = self.online_users_layout.takeAt(0)
                if child.widget():
                    child.widget().deleteLater()
            
            # 从DDS管理器同步在线用户数据
            if self.dds_manager:
                dds_users = self.dds_manager.get_online_users(topic)
                # 同步到本地存储
                self.online_users[topic] = dds_users.copy()
            
            # 确保自己始终在在线用户列表中
            if topic not in self.online_users:
                self.online_users[topic] = set()
            self.online_users[topic].add(self.username)
            
            # 获取当前主题的在线用户
            if topic in self.online_users:
                users = self.online_users[topic]
                self.online_count_label.setText(f"({len(users)})")
                
                # 添加每个在线用户
                for username in sorted(users):
                    user_item = self.create_online_user_item(username)
                    self.online_users_layout.addWidget(user_item)
            else:
                self.online_count_label.setText("(0)")
            
            # 延迟重试机制：如果用户数量较少，延迟后再次刷新
            if self.dds_manager and topic in self.dds_manager.online_users:
                dds_user_count = len(self.dds_manager.online_users[topic])
                current_user_count = len(self.online_users.get(topic, set()))
                
                # 如果DDS中的用户数比当前显示的多，延迟后再次刷新
                if dds_user_count > current_user_count:
                    print(f"[调试] 检测到用户数不匹配，DDS: {dds_user_count}, UI: {current_user_count}，延迟刷新")
                    from PySide6.QtCore import QTimer
                    QTimer.singleShot(1000, lambda: self.update_online_users_display(topic))
                
        except Exception as e:
            print(f"[错误] 更新在线用户显示失败: {e}")
    
    def create_online_user_item(self, username):
        """创建在线用户项"""
        user_frame = QFrame()
        user_frame.setFixedHeight(30)
        
        # 判断是否是当前用户
        is_self = (username == self.username)
        
        # 简化样式，移除背景色
        user_frame.setStyleSheet("""
            QFrame {
                background-color: transparent;
                border: none;
            }
            QFrame:hover {
                background-color: #2d3748;
                border-radius: 4px;
            }
        """)
        
        user_layout = QHBoxLayout(user_frame)
        user_layout.setContentsMargins(8, 5, 8, 5)
        user_layout.setSpacing(8)
        
        # 在线状态指示器
        status_dot = QLabel("●")
        status_dot.setFixedSize(8, 8)
        if is_self:
            status_dot.setStyleSheet("color: #63b3ed; font-size: 8px; border: none; background: transparent;")
        else:
            status_dot.setStyleSheet("color: #48bb78; font-size: 8px; border: none; background: transparent;")
        status_dot.setAlignment(Qt.AlignCenter)
        
        # 用户名
        username_label = QLabel(username)
        username_label.setFont(QFont("Microsoft YaHei", 9))
        if is_self:
            username_label.setStyleSheet("color: #63b3ed; font-weight: bold; border: none; background: transparent;")
        else:
            username_label.setStyleSheet("color: #a0aec0; border: none; background: transparent;")
        
        user_layout.addWidget(status_dot)
        user_layout.addWidget(username_label)
        user_layout.addStretch()
        
        return user_frame
    
    def add_self_to_all_topics(self):
        """将自己添加到所有主题的在线用户列表中"""
        try:
            # 获取所有主题（包括预定义的和已创建的）
            predefined_topics = ["多功能聊天室", "CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
            all_topics = predefined_topics + list(self.topic_items.keys())
            
            for topic in all_topics:
                if topic not in self.online_users:
                    self.online_users[topic] = set()
                self.online_users[topic].add(self.username)
                
                # 同步到DDS管理器
                if self.dds_manager and topic in self.dds_manager.online_users:
                    self.dds_manager.online_users[topic].add(self.username)
            
            # 更新当前主题的在线用户显示
            self.update_online_users_display(self.current_topic)
            
        except Exception as e:
            print(f"[错误] 添加自己到在线用户列表失败: {e}")
    
    def handle_user_join(self, topic, username):
        """处理用户加入事件"""
        try:
            print(f"[调试] 开始处理用户加入: {username} 到 {topic}")
            
            # 初始化主题的已加入用户列表
            if topic not in self.joined_users:
                self.joined_users[topic] = set()
            
            # 初始化主题的在线用户列表
            if topic not in self.online_users:
                self.online_users[topic] = set()
            
            # 检查是否已经处理过该用户的加入
            if username in self.joined_users[topic]:
                # 确保用户在线状态正确，但不重复显示消息
                if username not in self.online_users[topic]:
                    self.online_users[topic].add(username)
                    print(f"[调试] 用户重新加入: {username} 加入 {topic}")
                print(f"[调试] 用户 {username} 已经处理过加入 {topic}，跳过")
                return  # 已经显示过加入消息，不再显示
            
            print(f"[调试] 用户加入: {username} 加入 {topic}")
            
            # 标记该用户已显示加入提示
            self.joined_users[topic].add(username)
            
            # 添加到在线用户列表
            self.online_users[topic].add(username)
            
            # 创建系统消息
            system_message = f"🎉 {username} 加入了聊天室"
            
            # 将系统消息存储到对应主题的历史记录中
            if topic not in self.topic_messages:
                self.topic_messages[topic] = []
            
            # 存储系统消息数据
            message_data = {
                'message': system_message,
                'is_sender': False,
                'sender': '系统',
                'time': self.format_time(),
                'is_system': True
            }
            self.topic_messages[topic].append(message_data)
            
            # 如果当前显示的是这个消息的主题，则立即显示
            if topic == self.current_topic:
                self.add_system_message(system_message)
            
            # 总是更新当前显示主题的在线用户列表，确保一致性
            self.update_online_users_display(self.current_topic)
            
        except Exception as e:
            print(f"[错误] 处理用户加入出错: {e}")
            import traceback
            traceback.print_exc()
    
    def handle_user_leave(self, topic, username):
        """处理用户离开事件"""
        try:
            print(f"[调试] 用户离开: {username} 离开 {topic}")
            
            # 从在线用户列表中移除（只移除离开的用户，不影响当前用户）
            if topic in self.online_users and username in self.online_users[topic]:
                self.online_users[topic].remove(username)
                print(f"[调试] 已从在线用户列表移除: {username}")
            
            # 确保自己始终在在线用户列表中
            if topic in self.online_users:
                self.online_users[topic].add(self.username)
            
            # 创建系统消息
            system_message = f"👋 {username} 离开了聊天室"
            
            # 将系统消息存储到对应主题的历史记录中
            if topic not in self.topic_messages:
                self.topic_messages[topic] = []
            
            # 存储系统消息数据
            message_data = {
                'message': system_message,
                'is_sender': False,
                'sender': '系统',
                'time': self.format_time(),
                'is_system': True
            }
            self.topic_messages[topic].append(message_data)
            
            # 如果当前显示的是这个消息的主题，则立即显示
            if topic == self.current_topic:
                self.add_system_message(system_message)
            
            # 总是更新当前显示主题的在线用户列表，确保一致性
            self.update_online_users_display(self.current_topic)
            
            # 延迟刷新机制：确保用户状态完全同步
            from PySide6.QtCore import QTimer
            QTimer.singleShot(500, lambda: self.update_online_users_display(self.current_topic))
            
            # 不检查域清理，只在程序退出时检查
            print(f"[调试] 用户 {username} 已离开，不检查域状态")
            
        except Exception as e:
            print(f"[错误] 处理用户离开出错: {e}")
            import traceback
            traceback.print_exc()
    
    def check_domain_cleanup(self):
        """检查是否需要清理域（删除所有创建的主题）"""
        try:
            if not self.dds_manager:
                return
                
            # 检查所有主题是否只有自己在线
            all_topics_empty = True
            for topic, users in self.online_users.items():
                # 如果主题还有除了自己以外的用户，则域不为空
                other_users = users - {self.username}
                if other_users:
                    all_topics_empty = False
                    break
            
            if all_topics_empty:
                print(f"[调试] 检测到域已空，通知DDS管理器清理所有创建的主题")
                self.dds_manager.delete_all_created_topics()
                
        except Exception as e:
            print(f"[错误] 检查域清理失败: {e}")
            import traceback
            traceback.print_exc()
    
    def handle_topic_deleted(self, topic_name):
        """处理主题删除事件"""
        try:
            print(f"[调试] 收到主题删除通知: {topic_name}")
            
            # 从主题列表中移除
            if topic_name in self.topic_items:
                topic_item = self.topic_items[topic_name]
                self.topic_list.layout().removeWidget(topic_item)
                topic_item.deleteLater()
                del self.topic_items[topic_name]
                print(f"[调试] 主题 '{topic_name}' 已从列表中移除")
            
            # 从发现的主题列表中移除
            if hasattr(self, 'discovered_topics') and topic_name in self.discovered_topics:
                self.discovered_topics.remove(topic_name)
                print(f"[调试] 主题 '{topic_name}' 已从发现列表中移除")
            
            # 如果当前显示的是被删除的主题，切换到默认主题
            if self.current_topic == topic_name:
                if "CHAT_TOPIC 1" in self.topic_items:
                    self.select_topic("CHAT_TOPIC 1")
                elif self.topic_items:
                    # 选择第一个可用的主题
                    first_topic = list(self.topic_items.keys())[0]
                    self.select_topic(first_topic)
            
            # 清理相关数据
            if topic_name in self.topic_messages:
                del self.topic_messages[topic_name]
            if topic_name in self.online_users:
                del self.online_users[topic_name]
            
            print(f"[调试] 主题 '{topic_name}' 删除处理完成")
            
        except Exception as e:
            print(f"[错误] 处理主题删除出错: {e}")
            import traceback
            traceback.print_exc()
    
    def handle_new_topic_created(self, topic_name):
        """处理新主题创建事件"""
        try:
            print(f"[调试] 收到新主题创建通知: {topic_name}")
            
            # 检查主题是否已存在
            if topic_name in self.topic_items:
                print(f"[调试] 主题 '{topic_name}' 已存在，跳过创建")
                return
            
            # 创建主题项
            topic_item = TopicItem(topic_name, self)
            self.topic_items[topic_name] = topic_item
            self.topic_list.addWidget(topic_item)
            
            # 连接点击信号
            topic_item.topicSelected.connect(self.select_topic)
            
            # 初始化主题相关数据
            self.topic_messages[topic_name] = []
            self.topic_unread[topic_name] = 0
            self.joined_users[topic_name] = set()
            self.online_users[topic_name] = set()
            
            # 将自己添加到新主题的在线用户列表
            self.online_users[topic_name].add(self.username)
            if self.dds_manager and topic_name in self.dds_manager.online_users:
                self.dds_manager.online_users[topic_name].add(self.username)
            
            # 通知DDS管理器创建新主题的发布者和订阅者
            if self.dds_manager:
                self.dds_manager.create_new_topic(topic_name)
            
            # 立即更新在线用户显示（确保UI及时更新）
            self.update_online_users_display(topic_name)
            
            # 同时更新当前显示主题的在线用户显示，确保一致性
            self.update_online_users_display(self.current_topic)
            
            # 向新主题发送自己的在线状态，确保其他用户能看到我们
            if self.dds_manager:
                self.dds_manager.send_online_message(topic_name)
            
            print(f"[调试] 新主题 '{topic_name}' 添加成功")
            
        except Exception as e:
            print(f"[错误] 处理新主题创建失败: {e}")
            import traceback
            traceback.print_exc()
    
    def add_system_message(self, message):
        """添加系统消息到聊天界面"""
        # 检查当前布局中的组件数量，移除原来的伸缩组件
        if self.chat_layout.count() > 0:
            # 移除最后一个伸缩组件
            last_item = self.chat_layout.takeAt(self.chat_layout.count() - 1)
            if last_item and last_item.widget():
                last_item.widget().deleteLater()
        
        # 创建系统消息标签
        message_label = QLabel(message)
        message_label.setWordWrap(True)
        font = QFont("Microsoft YaHei", 11)
        message_label.setFont(font)
        message_label.setStyleSheet("""
            QLabel {
                background-color: #2d3748;
                color: #a0aec0;
                padding: 8px 15px;
                border-radius: 12px;
                font-size: 11px;
                font-style: italic;
            }
        """)
        message_label.setAlignment(Qt.AlignCenter)
        
        # 创建时间标签
        time_label = QLabel(self.format_time())
        time_label.setFont(QFont("Microsoft YaHei", 9))
        time_label.setStyleSheet("color: #718096;")
        time_label.setAlignment(Qt.AlignCenter)
        
        # 创建消息容器
        message_container = QWidget()
        message_container_layout = QVBoxLayout(message_container)
        message_container_layout.setContentsMargins(0, 0, 0, 0)
        message_container_layout.setSpacing(2)
        
        message_container_layout.addWidget(message_label)
        message_container_layout.addWidget(time_label)
        
        # 创建水平布局来管理消息的对齐方式
        message_layout = QHBoxLayout()
        message_layout.setContentsMargins(15, 5, 15, 5)
        message_layout.addStretch()
        message_layout.addWidget(message_container)
        message_layout.addStretch()
        
        # 将水平布局添加到聊天布局中
        self.chat_layout.addLayout(message_layout)
        self.chat_layout.addStretch()
        
        # 滚动到底部
        self.scroll_to_bottom()
