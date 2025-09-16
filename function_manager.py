# 功能管理模块
from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QLabel, 
                               QPushButton, QFrame, QStackedWidget, QScrollArea)
from PySide6.QtCore import Qt, Signal, QObject
from PySide6.QtGui import QFont, QIcon

class FunctionButton(QPushButton):
    """功能按钮组件"""
    functionSelected = Signal(str)  # 功能名称
    
    def __init__(self, function_name, icon_text, is_selected=False):
        super().__init__()
        self.function_name = function_name
        self.is_selected = is_selected
        self.init_ui(icon_text)
        
    def init_ui(self, icon_text):
        self.setFixedHeight(60)
        self.setFixedWidth(80)
        
        # 创建垂直布局
        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 8, 8, 8)
        layout.setSpacing(4)
        
        # 图标标签
        self.icon_label = QLabel(icon_text)
        self.icon_label.setFont(QFont("Microsoft YaHei", 16))
        self.icon_label.setAlignment(Qt.AlignCenter)
        self.icon_label.setStyleSheet("color: #a0aec0;")
        
        # 功能名称标签
        self.name_label = QLabel(self.function_name)
        self.name_label.setFont(QFont("Microsoft YaHei", 9))
        self.name_label.setAlignment(Qt.AlignCenter)
        self.name_label.setStyleSheet("color: #a0aec0;")
        
        layout.addWidget(self.icon_label)
        layout.addWidget(self.name_label)
        
        self.update_style()
        
    def update_style(self):
        if self.is_selected:
            self.setStyleSheet("""
                QPushButton {
                    background-color: transparent;
                    border: none;
                    border-radius: 8px;
                    border-left: 3px solid #4299e1;
                }
                QPushButton:hover {
                    background-color: #2d3748;
                }
            """)
            self.icon_label.setStyleSheet("color: #4299e1;")
            self.name_label.setStyleSheet("color: #4299e1;")
        else:
            self.setStyleSheet("""
                QPushButton {
                    background-color: transparent;
                    border: none;
                    border-radius: 8px;
                }
                QPushButton:hover {
                    background-color: #2d3748;
                }
            """)
            self.icon_label.setStyleSheet("color: #a0aec0;")
            self.name_label.setStyleSheet("color: #a0aec0;")
    
    def set_selected(self, selected):
        self.is_selected = selected
        self.update_style()
    
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.functionSelected.emit(self.function_name)

class FunctionSidebar(QWidget):
    """功能侧边栏"""
    functionChanged = Signal(str)  # 功能切换信号
    
    def __init__(self):
        super().__init__()
        self.function_buttons = {}
        self.current_function = "聊天"
        self.init_ui()
        
    def init_ui(self):
        self.setFixedWidth(80)
        self.setStyleSheet("background-color: #1a202c; border-right: 1px solid #2d3748;")
        
        layout = QVBoxLayout(self)
        layout.setContentsMargins(8, 20, 8, 20)
        layout.setSpacing(8)
        
        # 添加功能按钮
        functions = [
            ("聊天", "💬"),
            ("共享画布", "🎨"),
            ("贪吃蛇", "🐍"),
        ]
        
        for func_name, icon in functions:
            btn = FunctionButton(func_name, icon, func_name == self.current_function)
            btn.functionSelected.connect(self.select_function)
            self.function_buttons[func_name] = btn
            layout.addWidget(btn)
        
        layout.addStretch()
        
    def select_function(self, function_name):
        """选择功能"""
        if function_name == self.current_function:
            return
            
        # 更新按钮状态
        for name, btn in self.function_buttons.items():
            btn.set_selected(name == function_name)
        
        self.current_function = function_name
        self.functionChanged.emit(function_name)

class FunctionPages(QWidget):
    """功能页面容器"""
    
    def __init__(self):
        super().__init__()
        self.pages = {}
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        
        # 创建堆叠窗口
        self.stacked_widget = QStackedWidget()
        layout.addWidget(self.stacked_widget)
        
    def add_page(self, page_name, page_widget):
        """添加页面"""
        self.pages[page_name] = page_widget
        self.stacked_widget.addWidget(page_widget)
        
    def switch_to_page(self, page_name):
        """切换到指定页面"""
        if page_name in self.pages:
            self.stacked_widget.setCurrentWidget(self.pages[page_name])
            return True
        return False

class FunctionManager(QObject):
    """功能管理器"""
    functionChanged = Signal(str)  # 功能切换信号
    
    def __init__(self):
        super().__init__()
        self.sidebar = FunctionSidebar()
        self.pages = FunctionPages()
        self.current_function = "聊天"
        
        # 连接信号
        self.sidebar.functionChanged.connect(self.handle_function_change)
        
    def handle_function_change(self, function_name):
        """处理功能切换"""
        self.current_function = function_name
        self.pages.switch_to_page(function_name)
        self.functionChanged.emit(function_name)
        
    def get_sidebar(self):
        """获取侧边栏"""
        return self.sidebar
        
    def get_pages(self):
        """获取页面容器"""
        return self.pages
        
    def add_function_page(self, page_name, page_widget):
        """添加功能页面"""
        self.pages.add_page(page_name, page_widget)
