# 严格按照图片样式的聊天界面 - 优化消息气泡显示
import os, sys, time
from PySide6.QtWidgets import (QApplication, QWidget, QVBoxLayout, QHBoxLayout, 
                               QTextBrowser, QLineEdit, QPushButton, QListWidget, 
                               QListWidgetItem, QLabel, QFrame, QScrollArea, QSpacerItem, QSizePolicy)
from PySide6.QtCore import Qt, Signal, QObject, QTimer, QSize
from PySide6.QtGui import QTextCursor, QFont, QPalette, QColor, QPixmap, QPainter, QFontMetrics

# ========== ZRDDS 模块加载 ==========
current_dir = os.path.dirname(os.path.abspath(__file__))
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, build_release_dir)

import _zrdds_basic as basic
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
import _zrdds_listener as listener
import _zrdds_subscribe as subscribe
import _zrdds_shapetype as shapetype

def safe_str(s):
    if s is None: return "<None>"
    if isinstance(s, str): return s
    if isinstance(s, bytes):
        try: return s.rstrip(b"\x00").decode("utf-8")
        except: return s.rstrip(b"\x00").decode("latin-1", errors="ignore")
    return str(s)

class SignalProxy(QObject):
    newMessage = Signal(str, str, str)  # topic, sender_name, msg

class ChatListener(listener.DataReaderListener):
    def __init__(self, self_id, proxy: SignalProxy, topic_name):
        super().__init__()
        self.self_id = self_id
        self.proxy = proxy
        self.topic_name = topic_name

    def on_data_available(self, reader):
        try:
            print(f"[调试] 收到数据，主题: {self.topic_name}")
            while True:
                data = shapetype.ShapeType()
                sample_info = shapetype.SampleInfo()
                ret = reader.read_next_sample(data, sample_info)
                if ret == basic.RETCODE_OK and sample_info.valid_data:
                    sender_id = data.x
                    msg_content = safe_str(data.z)
                    print(f"[调试] 收到消息: 发送者ID={sender_id}, 自己ID={self.self_id}, 内容={msg_content}")
                    if sender_id != self.self_id:
                        # 解析用户名和消息内容
                        if "|" in msg_content:
                            parts = msg_content.split("|", 1)
                            sender_name = parts[0]
                            actual_message = parts[1]
                        else:
                            # 兼容旧格式，如果没有分隔符则使用用户ID
                            sender_name = f"用户{sender_id}"
                            actual_message = msg_content
                        
                        print(f"[调试] 转发消息到UI: {self.topic_name} - {sender_name} - {actual_message}")
                        self.proxy.newMessage.emit(self.topic_name, sender_name, actual_message)
                    else:
                        print(f"[调试] 忽略自己的消息")
                else:
                    break
        except Exception as e:
            print(f"[错误] 接收消息出错: {e}")
            import traceback
            traceback.print_exc()

class TopicItem(QWidget):
    """主题列表项 - 严格按照图片样式"""
    topicSelected = Signal(str)
    
    def __init__(self, topic_name, is_selected=False):
        super().__init__()
        self.topic_name = topic_name
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
        if event.button() == Qt.LeftButton:
            self.topicSelected.emit(self.topic_name)

class ChatUI(QWidget):
    sendMessage = Signal(str, str)  # topic, message
    showMessage = Signal(str, str, str)  # topic, sender_name, msg

    def __init__(self, username="我", user_id=0):
        super().__init__()
        self.username = username
        self.user_id = user_id
        self.current_topic = "多功能聊天室"
        self.topic_messages = {}  # 存储每个主题的消息历史
        self.topic_items = {}  # 存储主题项
        self.topic_unread = {}  # 存储未读消息数
        self.init_ui()
        self.showMessage.connect(self.append_message)
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
            }
            QLineEdit:focus {
                border: 1px solid #4299e1;
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
        self.setWindowTitle("多功能聊天室")
        self.setWindowFlags(Qt.Window | Qt.WindowCloseButtonHint | Qt.WindowMaximizeButtonHint)
        self.resize(1200, 800)
        
        # 主布局
        main_layout = QHBoxLayout(self)
        main_layout.setContentsMargins(0, 0, 0, 0)
        main_layout.setSpacing(0)
        
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
        
        # 主题列表
        self.topic_list = QVBoxLayout()
        self.topic_list.setSpacing(0)
        self.topic_list.setContentsMargins(0, 0, 0, 0)
        sidebar_layout.addLayout(self.topic_list)
        sidebar_layout.addStretch()  
        parent_layout.addWidget(sidebar_frame)

    def create_chat_area(self, parent_layout):
        """创建右侧聊天区域 - 严格按照图片样式"""
        chat_frame = QFrame()
        chat_frame.setStyleSheet("background-color: #1a202c;")
        chat_layout = QVBoxLayout(chat_frame)
        chat_layout.setContentsMargins(0, 0, 0, 0)
        chat_layout.setSpacing(0)
        
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
        self.input_box.setStyleSheet("""
            QLineEdit {
                background-color: #2d3748;
                border: 1px solid #4a5568;
                border-radius: 8px;
                padding: 12px;
                color: #ffffff;
                font-size: 14px;
                font-family: 'Microsoft YaHei';
            }
            QLineEdit:focus {
                border: 1px solid #4299e1;
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
        topic_item = TopicItem(topic_name)
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

    def refresh_messages(self):
        """刷新当前主题的消息显示"""
        # 清空当前聊天布局
        while self.chat_layout.count():
            child = self.chat_layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()
        
        # 重新显示该主题的消息历史
        if self.current_topic in self.topic_messages:
            for message_data in self.topic_messages[self.current_topic]:
                # message_data 现在是一个字典，包含消息信息
                self.add_message_bubble(
                    message_data['message'], 
                    message_data['is_sender'], 
                    message_data['sender'], 
                    message_data['time']
                )

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

def main():
    app = QApplication(sys.argv)
    self_name = input("请输入你的名字: ").strip() or "匿名用户"
    self_id = hash(self_name) % 10000

    ui = ChatUI(self_name, self_id)
    proxy = SignalProxy()

    try:
        factory = domain.TheParticipantFactory
        qos = domain.DomainParticipantQos()
        factory.get_default_participant_qos(qos)
        participant = factory.create_participant(80, qos, None, 0)

        shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
        shapetype_support.register_type(participant, None)

        # 每个主题分别创建 publisher & subscriber
        writers = {}
        listeners = {}
        topics = ["CHAT_TOPIC 1", "CHAT_TOPIC 2", "CHAT_TOPIC 3"]
        for topic_name in topics:
            topic_qos = domain.TopicQos()
            participant.get_default_topic_qos(topic_qos)
            topic_obj = participant.create_topic(topic_name, shapetype_support.get_type_name(), topic_qos, None, 0)

            pub_qos = domain.PublisherQos()
            participant.get_default_publisher_qos(pub_qos)
            publisher = participant.create_publisher(pub_qos, None, 0)

            ret, dw_qos = publisher.get_default_datawriter_qos()
            writer = publisher.create_datawriter(topic_obj, dw_qos, None, 0)
            writers[topic_name] = writer

            sub_qos = domain.SubscriberQos()
            participant.get_default_subscriber_qos(sub_qos)
            subscriber = participant.create_subscriber(sub_qos, None, 0)

            listener_obj = ChatListener(self_id, proxy, topic_name)
            ret, dr_qos = subscriber.get_default_datareader_qos()
            datareader = subscriber.create_datareader(topic_obj, dr_qos, listener_obj, 1024)
            print(f"[调试] 创建数据读取器成功，主题: {topic_name}")
            listeners[topic_name] = listener_obj

    except Exception as e:
        print(f"DDS 初始化失败: {e}")
        raise

    # 发送消息安全封装
    def send_msg(topic, text):
        try:
            if len(text) > 512: text = text[:512]
            send_data = shapetype.ShapeType()
            send_data.x = self_id
            send_data.y = int(time.time() * 1000) % 1000
            # 将用户名和消息内容组合发送
            combined_message = f"{self_name}|{text}"
            send_data.z = combined_message
            writer = writers.get(topic)
            if writer:
                ret = writer.write(send_data, domain.HANDLE_NIL_NATIVE)
                if ret == basic.RETCODE_OK:
                    ui.showMessage.emit(topic, self_name, text)
                else:
                    print(f"消息发送失败: {ret}")
            else:
                print(f"找不到主题 {topic} 的写入器")
        except Exception as e:
            print(f"DDS 写入异常: {e}")
            import traceback
            traceback.print_exc()

    ui.sendMessage.connect(send_msg)
    proxy.newMessage.connect(lambda t, s, m: ui.showMessage.emit(t, s, m))

    ui.show()
    print(f"[调试] 信号连接完成，用户名: {self_name}, 用户ID: {self_id}")
    
    # 添加窗口关闭事件处理
    def on_window_close():
        print("👋 窗口关闭，程序退出")
        app.quit()
    
    ui.closeEvent = lambda event: on_window_close()
    
    try:
        print("[调试] 开始运行事件循环...")
        app.exec()
        print("[调试] 事件循环结束")
    except Exception as e:
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()