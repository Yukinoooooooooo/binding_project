# -*- coding: utf-8 -*-
# 独立画板窗口
import sys
import time
import re
import json

from PySide6.QtCore import Qt, QTimer, QPropertyAnimation, QEasingCurve
from PySide6.QtGui import QMouseEvent, QColor, QPen, QFont, QIcon, QPainter, QBrush, QLinearGradient, QPalette
from PySide6.QtWidgets import (
    QApplication, QGraphicsScene, QGraphicsView, QGraphicsLineItem, QWidget,
    QVBoxLayout, QHBoxLayout, QPushButton, QSlider, QLabel, QColorDialog, QFrame,
    QMainWindow, QMessageBox, QSizePolicy, QSpacerItem
)
from queue import Queue


def safe_str(s):
    """
    将数据安全转换为字符串，处理DDS字符串字段
    支持UTF-8和系统编码（GBK）的回退机制
    """
    if s is None:
        return "<None>"
    if isinstance(s, str):
        return s
    if isinstance(s, bytes):
        # 去掉末尾的 \x00 填充
        raw = s.rstrip(b"\x00")
        
        # 首先尝试UTF-8解码
        try:
            return raw.decode("utf-8")
        except UnicodeDecodeError:
            # 回退到系统编码（Windows下通常是GBK/CP936）
            try:
                return raw.decode("gbk", errors="ignore")
            except Exception:
                # 最后的回退：使用latin-1（不会失败）
                return raw.decode("latin-1", errors="ignore")
    
    return str(s)


class ModernButton(QPushButton):
    """现代化按钮样式"""
    def __init__(self, text, icon_text=None, button_type="primary", is_dark_theme=False):
        super().__init__(text)
        self.button_type = button_type
        self.icon_text = icon_text
        # 固定使用白色主题
        self.is_dark_theme = False
        self.setup_style()
        
    def setup_style(self):
        """设置按钮样式"""
        # 设置字体
        font = QFont()
        font.setFamily("Microsoft YaHei")
        font.setPointSize(10)
        font.setBold(True)
        self.setFont(font)
        
        # 设置按钮大小
        self.setMinimumHeight(40)
        self.setMinimumWidth(100)
        
        # 固定白色主题按钮样式
        if self.button_type == "primary":
            self.setStyleSheet("""
                QPushButton {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #007BFF, stop:1 #0056B3);
                    border: 2px solid #0056B3;
                    border-radius: 8px;
                    color: white;
                    padding: 8px 16px;
                    font-weight: bold;
                }
                QPushButton:hover {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #0056B3, stop:1 #004085);
                    border: 2px solid #004085;
                }
                QPushButton:pressed {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #004085, stop:1 #002752);
                    border: 2px solid #002752;
                }
                QPushButton:checked {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #DC3545, stop:1 #C82333);
                    border: 2px solid #C82333;
                }
            """)
        elif self.button_type == "secondary":
            self.setStyleSheet("""
                QPushButton {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #6C757D, stop:1 #5A6268);
                    border: 2px solid #5A6268;
                    border-radius: 8px;
                    color: white;
                    padding: 8px 16px;
                    font-weight: bold;
                }
                QPushButton:hover {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #5A6268, stop:1 #495057);
                    border: 2px solid #495057;
                }
                QPushButton:pressed {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #495057, stop:1 #343A40);
                    border: 2px solid #343A40;
                }
                QPushButton:checked {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #DC3545, stop:1 #C82333);
                    border: 2px solid #C82333;
                }
            """)
        elif self.button_type == "success":
            self.setStyleSheet("""
                QPushButton {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #27AE60, stop:1 #229954);
                    border: 2px solid #229954;
                    border-radius: 8px;
                    color: white;
                    padding: 8px 16px;
                    font-weight: bold;
                }
                QPushButton:hover {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #37BE70, stop:1 #32A964);
                    border: 2px solid #32A964;
                }
                QPushButton:pressed {
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                        stop:0 #229954, stop:1 #1D8044);
                    border: 2px solid #1D8044;
                }
            """)


class ColorButton(QPushButton):
    """颜色选择按钮"""
    def __init__(self, color=QColor(Qt.black)):
        super().__init__()
        self.current_color = color
        self.setup_style()
        
    def setup_style(self):
        """设置颜色按钮样式"""
        self.setMinimumSize(50, 40)
        self.setMaximumSize(50, 40)
        self.setStyleSheet(f"""
            QPushButton {{
                background-color: {self.current_color.name()};
                border: 3px solid #2C3E50;
                border-radius: 20px;
            }}
            QPushButton:hover {{
                border: 3px solid #3498DB;
                transform: scale(1.1);
            }}
            QPushButton:pressed {{
                border: 3px solid #E74C3C;
            }}
        """)
        
    def set_color(self, color):
        """设置颜色"""
        self.current_color = color
        self.setStyleSheet(f"""
            QPushButton {{
                background-color: {color.name()};
                border: 3px solid #2C3E50;
                border-radius: 20px;
            }}
            QPushButton:hover {{
                border: 3px solid #3498DB;
            }}
            QPushButton:pressed {{
                border: 3px solid #E74C3C;
            }}
        """)


class ModernSlider(QSlider):
    """现代化滑块"""
    def __init__(self, orientation=Qt.Horizontal):
        super().__init__(orientation)
        self.setup_style()
        
    def setup_style(self):
        """设置滑块样式"""
        self.setStyleSheet("""
            QSlider::groove:horizontal {
                border: 1px solid #999999;
                height: 8px;
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);
                margin: 2px 0;
                border-radius: 4px;
            }
            QSlider::handle:horizontal {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #4A90E2, stop:1 #357ABD);
                border: 1px solid #357ABD;
                width: 18px;
                margin: -2px 0;
                border-radius: 9px;
            }
            QSlider::handle:horizontal:hover {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #5BA0F2, stop:1 #468ACD);
                border: 1px solid #468ACD;
            }
            QSlider::handle:horizontal:pressed {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #357ABD, stop:1 #2A6A9D);
                border: 1px solid #2A6A9D;
            }
            QSlider::sub-page:horizontal {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4A90E2, stop:1 #357ABD);
                border: 1px solid #357ABD;
                height: 8px;
                border-radius: 4px;
            }
        """)


class DoodleBoard(QWidget):
    def __init__(self, dds_manager, self_name, is_dark_theme=False):
        super().__init__()
        self.dds_manager = dds_manager
        self.self_name = self_name
        # 固定使用白色主题
        self.is_dark_theme = False

        # 画板参数
        self.current_color = QColor(Qt.black)
        self.current_width = 2
        self.current_tool = "pen"  # pen/eraser
        self.zoom_factor = 1.0  # 缩放因子

        # 画布
        self.scene = QGraphicsScene()
        self.view = QGraphicsView(self.scene)
        self.view.setBackgroundBrush(Qt.white)
        self.view.setMouseTracking(False)  # 禁用鼠标跟踪，避免意外触发
        self.view.setDragMode(QGraphicsView.RubberBandDrag)  # 设置拖拽模式

        # 画图标记
        self.drawing = False
        self.last_pos = None
        self.has_drawn = False  # 标记是否已经绘制过

        # 用户绘制内容跟踪
        self.user_drawings = {}  # {username: [line_items]}
        self.user_labels = {}    # {username: label_item}

        # 队列和定时器
        self.draw_queue = Queue()
        self.timer = QTimer()
        self.timer.timeout.connect(self.process_draw_queue)
        self.timer.start(30)

        # UI控件区 - 使用美化组件
        self.color_btn = ColorButton(self.current_color)
        self.color_btn.clicked.connect(self.choose_color)
        self.color_btn.setToolTip("点击选择颜色")
        
        self.width_slider = ModernSlider(Qt.Horizontal)
        self.width_slider.setMinimum(1)
        self.width_slider.setMaximum(20)
        self.width_slider.setValue(self.current_width)
        self.width_slider.valueChanged.connect(self.change_width)
        self.width_slider.setToolTip("调整画笔粗细")
        
        # 美化标签
        self.width_label = QLabel(f"粗细: {self.current_width}")
        font = QFont()
        font.setFamily("Microsoft YaHei")
        font.setPointSize(10)
        font.setBold(True)
        self.width_label.setFont(font)
        
        # 固定白色主题标签颜色
        self.width_label.setStyleSheet("color: #2C3E50; background: transparent; font-weight: bold;")
        
        self.eraser_btn = ModernButton("🧽 橡皮", button_type="secondary")
        self.eraser_btn.setCheckable(True)
        self.eraser_btn.toggled.connect(self.toggle_eraser)
        self.eraser_btn.setToolTip("切换橡皮擦模式")

        # 添加清空按钮
        self.clear_self_btn = ModernButton("🧹 清空我的", button_type="secondary")
        self.clear_self_btn.clicked.connect(self.clear_self_canvas)
        self.clear_self_btn.setToolTip("清空自己绘制的内容")

        # 缩放控制按钮
        self.zoom_in_btn = ModernButton("放大", button_type="secondary")
        self.zoom_in_btn.clicked.connect(self.zoom_in)
        self.zoom_in_btn.setToolTip("放大 (Ctrl+滚轮)")
        self.zoom_in_btn.setMinimumWidth(60)
        self.zoom_in_btn.setMaximumWidth(60)
        
        self.zoom_out_btn = ModernButton("缩小", button_type="secondary")
        self.zoom_out_btn.clicked.connect(self.zoom_out)
        self.zoom_out_btn.setToolTip("缩小 (Ctrl+滚轮)")
        self.zoom_out_btn.setMinimumWidth(60)
        self.zoom_out_btn.setMaximumWidth(60)
        
        self.reset_zoom_btn = ModernButton("重置", button_type="secondary")
        self.reset_zoom_btn.clicked.connect(self.reset_zoom)
        self.reset_zoom_btn.setToolTip("重置缩放")
        self.reset_zoom_btn.setMinimumWidth(60)
        self.reset_zoom_btn.setMaximumWidth(60)

        # 缩放滑块
        self.zoom_slider = ModernSlider(Qt.Horizontal)
        self.zoom_slider.setMinimum(25)  # 25%
        self.zoom_slider.setMaximum(400)  # 400%
        self.zoom_slider.setValue(100)  # 100%
        self.zoom_slider.valueChanged.connect(self.change_zoom)
        self.zoom_slider.setToolTip("调整画布缩放 (25%-400%)")
        self.zoom_slider.setMinimumWidth(100)
        self.zoom_slider.setMaximumWidth(150)
        
        # 缩放标签
        self.zoom_label = QLabel("100%")
        font = QFont()
        font.setFamily("Microsoft YaHei")
        font.setPointSize(10)
        font.setBold(True)
        self.zoom_label.setFont(font)
        
        # 固定白色主题缩放标签样式
        self.zoom_label.setStyleSheet("""
            QLabel {
                color: #2C3E50; 
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #FFFFFF, stop:1 #F8F9FA);
                border: 1px solid #6C757D;
                border-radius: 4px;
                min-width: 50px;
                padding: 4px 8px;
                font-weight: bold;
            }
        """)
        self.zoom_label.setAlignment(Qt.AlignCenter)

        # 美化布局
        tool_layout = QHBoxLayout()
        tool_layout.setSpacing(15)
        tool_layout.setContentsMargins(20, 15, 20, 15)
        
        # 添加工具组
        tool_layout.addWidget(self.color_btn)
        tool_layout.addWidget(self.width_label)
        tool_layout.addWidget(self.width_slider)
        tool_layout.addItem(QSpacerItem(20, 0, QSizePolicy.Expanding, QSizePolicy.Minimum))
        
        # 缩放控制组
        zoom_group_layout = QHBoxLayout()
        zoom_group_layout.setSpacing(6)
        zoom_group_layout.setContentsMargins(8, 4, 8, 4)
        
        # 添加缩放控制组件
        zoom_group_layout.addWidget(self.zoom_out_btn)
        zoom_group_layout.addWidget(self.zoom_slider)
        zoom_group_layout.addWidget(self.zoom_label)
        zoom_group_layout.addWidget(self.zoom_in_btn)
        zoom_group_layout.addWidget(self.reset_zoom_btn)
        
        # 为缩放控制组添加背景框架
        zoom_frame = QFrame()
        zoom_frame.setLayout(zoom_group_layout)
        
        # 固定白色主题缩放控制组背景样式
        zoom_frame.setStyleSheet("""
            QFrame {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #FFFFFF, stop:1 #F8F9FA);
                border: 1px solid #DEE2E6;
                border-radius: 8px;
                margin: 2px;
            }
        """)
        
        tool_layout.addWidget(zoom_frame)
        tool_layout.addItem(QSpacerItem(20, 0, QSizePolicy.Expanding, QSizePolicy.Minimum))
        tool_layout.addWidget(self.clear_self_btn)
        tool_layout.addWidget(self.eraser_btn)

        main_layout = QVBoxLayout(self)
        main_layout.addWidget(self.view)
        main_layout.addLayout(tool_layout)

        self.setLayout(main_layout)

        # 事件绑定
        self.view.mousePressEvent = self.mousePressEvent
        self.view.mouseMoveEvent = self.mouseMoveEvent
        self.view.mouseReleaseEvent = self.mouseReleaseEvent
        self.view.wheelEvent = self.wheelEvent

    def get_color_dialog(self, initial_color):
        """创建固定白色主题的颜色选择器对话框"""
        # 使用简单的颜色选择器，不设置复杂样式
        dialog = QColorDialog(initial_color, self)
        dialog.setWindowTitle("选择颜色")
        
        # 设置对话框为模态
        dialog.setModal(True)
        
        # 简单的白色主题样式，只针对关键元素
        dialog.setStyleSheet("""
            QColorDialog {
                background-color: white;
                color: black;
            }
            QColorDialog QLabel {
                color: black;
                background-color: transparent;
            }
            QColorDialog QLineEdit {
                background-color: white;
                color: black;
                border: 1px solid gray;
            }
            QColorDialog QSpinBox {
                background-color: white;
                color: black;
                border: 1px solid gray;
            }
            QColorDialog QPushButton {
                background-color: #007BFF;
                color: white;
                border: 1px solid #0056B3;
                padding: 4px 8px;
            }
        """)
        
        return dialog

    def choose_color(self):
        """选择颜色"""
        dialog = self.get_color_dialog(self.current_color)
        if dialog.exec() == QColorDialog.Accepted:
            color = dialog.selectedColor()
        if color.isValid():
            self.current_color = color
            self.color_btn.set_color(color)
            self.eraser_btn.setChecked(False)

    def change_width(self, value):
        self.current_width = value
        self.width_label.setText(f"粗细: {value}")

    def toggle_eraser(self, checked):
        self.current_tool = "eraser" if checked else "pen"
        if checked:
            self.current_color = QColor(Qt.white)
            self.color_btn.set_color(self.current_color)
        else:
            if self.current_color == QColor(Qt.white):
                # 使用相同的白色主题颜色选择器
                dialog = self.get_color_dialog(QColor(Qt.black))
                if dialog.exec() == QColorDialog.Accepted:
                    color = dialog.selectedColor()
                if color.isValid():
                    self.current_color = color
                    self.color_btn.set_color(color)
    
    def zoom_in(self):
        """放大画布"""
        current_value = self.zoom_slider.value()
        new_value = min(current_value + 25, self.zoom_slider.maximum())
        self.zoom_slider.setValue(new_value)
    
    def zoom_out(self):
        """缩小画布"""
        current_value = self.zoom_slider.value()
        new_value = max(current_value - 25, self.zoom_slider.minimum())
        self.zoom_slider.setValue(new_value)
    
    def reset_zoom(self):
        """重置缩放"""
        self.zoom_slider.setValue(100)
    
    def change_zoom(self, value):
        """改变画布缩放"""
        self.zoom_factor = value / 100.0
        self.zoom_label.setText(f"{value}%")
        
        # 重置变换矩阵并应用新的缩放
        self.view.resetTransform()
        self.view.scale(self.zoom_factor, self.zoom_factor)
        
        print(f"[调试] 缩放设置为: {value}%")
    
    def clear_self_canvas(self):
        """只清空自己绘制的内容"""
        if self.self_name not in self.user_drawings or not self.user_drawings[self.self_name]:
            QMessageBox.information(self, "提示", "您还没有绘制任何内容")
            return
            
        reply = QMessageBox.question(self, "确认清空", f"确定要清空您绘制的所有内容吗？", 
                                   QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            # 只删除自己绘制的线条
            for line_item in self.user_drawings[self.self_name]:
                self.scene.removeItem(line_item)
            
            # 清空自己的绘制记录
            self.user_drawings[self.self_name] = []
            
            # 删除自己的用户名标签
            if hasattr(self, '_username_label_item') and self._username_label_item:
                self.scene.removeItem(self._username_label_item)
                self._username_label_item = None
            
            # 发送清空消息给其他用户
            self.send_clear_message()
            
            print(f"[调试] 已清空用户 {self.self_name} 的绘制内容")
    
    def send_clear_message(self):
        """发送清空消息给其他用户"""
        clear_data = {
            'action': 'clear_user',
            'username': self.self_name
        }
        
        message = json.dumps(clear_data)
        topic_name = "SHARED_CANVAS_TOPIC"
        
        # 使用DDS管理器的发送方法
        if self.dds_manager and hasattr(self.dds_manager, 'send_message'):
            success = self.dds_manager.send_message(topic_name, message)
            if success:
                print(f"[调试] 清空消息发送成功: {message}")
            else:
                print(f"[错误] 清空消息发送失败")
        else:
            print(f"[错误] DDS管理器不可用")
    
    def clear_user_drawings(self, username):
        """清空指定用户的绘制内容（用于处理远程清空请求）"""
        if username not in self.user_drawings or not self.user_drawings[username]:
            print(f"[调试] 用户 {username} 没有绘制内容需要清空")
            return
        
        # 删除该用户的所有绘制线条
        for line_item in self.user_drawings[username]:
            self.scene.removeItem(line_item)
        
        # 清空该用户的绘制记录
        self.user_drawings[username] = []
        
        # 删除该用户的标签
        if username in self.user_labels:
            label_item = self.user_labels[username]
            self.scene.removeItem(label_item)
            del self.user_labels[username]
        
        # 如果是自己的标签，也要清理
        if username == self.self_name and hasattr(self, '_username_label_item') and self._username_label_item:
            self.scene.removeItem(self._username_label_item)
            self._username_label_item = None
        
        print(f"[调试] 已清空用户 {username} 的绘制内容")

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drawing = True
            self.has_drawn = False  # 重置绘制标记
            self.last_pos = self.view.mapToScene(event.pos())

    def mouseMoveEvent(self, event: QMouseEvent):
        if self.drawing and self.last_pos:
            scene_pos = self.view.mapToScene(event.pos())
            # 计算移动距离
            distance = ((scene_pos.x() - self.last_pos.x()) ** 2 + (scene_pos.y() - self.last_pos.y()) ** 2) ** 0.5
            # 只有当鼠标移动距离超过20像素时才绘制
            if distance > 20:
                # 如果还没有绘制过，先更新位置但不绘制
                if not self.has_drawn:
                    self.has_drawn = True
                    self.last_pos = scene_pos
                    return
                
                pen = QPen(self.current_color, self.current_width)
                line = QGraphicsLineItem(self.last_pos.x(), self.last_pos.y(), scene_pos.x(), scene_pos.y())
                line.setPen(pen)
                self.scene.addItem(line)
                
                # 跟踪用户绘制的内容
                if self.self_name not in self.user_drawings:
                    self.user_drawings[self.self_name] = []
                self.user_drawings[self.self_name].append(line)
                
                # 传入起点用于判断方向
                self.add_or_update_username_label(scene_pos, self.self_name, self.current_color, self.last_pos)
                self.send_drawing_data(self.last_pos, scene_pos, self.current_color, self.current_width, self.current_tool, self.self_name)
                self.last_pos = scene_pos
                self.view.viewport().update()

    def mouseReleaseEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drawing = False
            self.has_drawn = False
            self.last_pos = None
    
    def wheelEvent(self, event):
        """鼠标滚轮缩放"""
        from PySide6.QtCore import QPoint
        from PySide6.QtGui import QWheelEvent
        
        # 检查是否按住了Ctrl键
        if event.modifiers() == Qt.ControlModifier:
            # 获取滚轮增量
            delta = event.angleDelta().y()
            
            # 计算缩放因子
            if delta > 0:
                # 向上滚动，放大
                current_value = self.zoom_slider.value()
                new_value = min(current_value + 10, self.zoom_slider.maximum())
            else:
                # 向下滚动，缩小
                current_value = self.zoom_slider.value()
                new_value = max(current_value - 10, self.zoom_slider.minimum())
            
            self.zoom_slider.setValue(new_value)
            event.accept()
        else:
            # 如果没有按Ctrl键，使用默认的滚动行为
            super().wheelEvent(event)

    def add_or_update_username_label(self, pos, username, color, start_pos=None):
        from PySide6.QtWidgets import QGraphicsTextItem
        if not hasattr(self, '_username_label_item') or self._username_label_item is None:
            self._username_label_item = QGraphicsTextItem(username)
            self._username_label_item.setDefaultTextColor(color)
            self.scene.addItem(self._username_label_item)
            # 跟踪用户标签
            self.user_labels[username] = self._username_label_item
        self._username_label_item.setPlainText(username)
        self._username_label_item.setDefaultTextColor(color)
        offset = 10
        label_width = self._username_label_item.boundingRect().width()
        # 判断方向，左移则标签在左侧
        if start_pos is not None and pos.x() < start_pos.x():
            self._username_label_item.setPos(pos.x() - offset - label_width, pos.y() - 10)
        else:
            self._username_label_item.setPos(pos.x() + offset, pos.y() - 10)

    def mouseReleaseEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drawing = False

    def send_drawing_data(self, start_pos, end_pos, color, width, tool, username):
        # 使用DDS管理器发送数据，避免直接使用shapetype
        line_data = {
            'start': {'x': start_pos.x(), 'y': start_pos.y()},
            'end': {'x': end_pos.x(), 'y': end_pos.y()},
            'color': color.name(),
            'width': width,
            'tool': tool,
            'username': username
        }
        
        # 将绘制数据作为消息发送到画板主题
        message = json.dumps(line_data)
        topic_name = "SHARED_CANVAS_TOPIC"
        
        # 使用DDS管理器的发送方法
        if self.dds_manager and hasattr(self.dds_manager, 'send_message'):
            success = self.dds_manager.send_message(topic_name, message)
            if success:
                print(f"[调试] 画板数据发送成功: {message}")
            else:
                print(f"[错误] 画板数据发送失败")
        else:
            print(f"[错误] DDS管理器不可用")

    def draw_line(self, start_pos, end_pos, color, width, tool, username):
        self.draw_queue.put((start_pos, end_pos, color, width, tool, username))

    def process_draw_queue(self):
        from PySide6.QtWidgets import QGraphicsTextItem
        if not hasattr(self, '_remote_labels'):
            self._remote_labels = {}
        offset = 10
        while not self.draw_queue.empty():
            start_pos, end_pos, color, width, tool, username = self.draw_queue.get()
            pen = QPen(QColor(color), width)
            line = QGraphicsLineItem(start_pos[0], start_pos[1], end_pos[0], end_pos[1])
            line.setPen(pen)
            self.scene.addItem(line)
            
            # 跟踪远程用户绘制的内容
            if username not in self.user_drawings:
                self.user_drawings[username] = []
            self.user_drawings[username].append(line)
            
            # 只保留一个远程用户标签，移动时更新位置
            if username not in self._remote_labels or self._remote_labels[username] is None:
                label_item = QGraphicsTextItem(username)
                label_item.setDefaultTextColor(QColor(color))
                self.scene.addItem(label_item)
                self._remote_labels[username] = label_item
                # 跟踪用户标签
                self.user_labels[username] = label_item
            label_item = self._remote_labels[username]
            label_item.setPlainText(username)
            label_item.setDefaultTextColor(QColor(color))
            label_width = label_item.boundingRect().width()
            if end_pos[0] < start_pos[0]:
                label_item.setPos(end_pos[0] - offset - label_width, end_pos[1] - 10)
            else:
                label_item.setPos(end_pos[0] + offset, end_pos[1] - 10)
        self.view.viewport().update()


class CanvasWindow(QMainWindow):
    """独立的画板窗口"""
    
    def __init__(self, username, dds_manager=None):
        super().__init__()
        self.username = username
        self.dds_manager = dds_manager
        self.dds_components = {}
        
        # 固定使用白色主题
        self.is_dark_theme = False
        
        self.init_ui()
        # 不在这里初始化DDS，而是在open_canvas_window中初始化
        
    def init_ui(self):
        """初始化UI"""
        self.setWindowTitle(f"🎨 共享画板 - {self.username}")
        self.setGeometry(100, 100, 900, 600)
        
        # 固定白色主题样式
        self.setStyleSheet("""
            QMainWindow {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #F8F9FA, stop:1 #E9ECEF);
                border: 1px solid #DEE2E6;
            }
            QGraphicsView {
                background-color: white;
                border: 2px solid #6C757D;
                border-radius: 10px;
                margin: 10px;
            }
            QFrame {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #FFFFFF, stop:1 #F8F9FA);
                border: 1px solid #DEE2E6;
                border-radius: 8px;
                margin: 5px;
            }
        """)
        
        # 设置窗口图标（如果有的话）
        try:
            self.setWindowIcon(self.style().standardIcon(self.style().SP_DesktopIcon))
        except:
            # 如果设置图标失败，忽略错误
            pass
        
    def init_dds(self):
        """初始化DDS系统 - 直接使用现有DDS管理器"""
        try:
            print("🚀 启动共享画板系统...")
            
            # 使用现有的DDS管理器
            if self.dds_manager is None:
                QMessageBox.critical(self, "错误", "DDS管理器未提供")
                return False
                
            print("✅ 使用现有DDS管理器")
            
            # 创建画板 - 直接使用DDS管理器，不创建新的DDS组件
            self.doodle_board = DoodleBoard(self.dds_manager, self.username)
            
            # 连接画板主题的消息接收信号
            proxy = self.dds_manager.get_signal_proxy()
            proxy.newMessage.connect(self.handle_canvas_message)
            
            # 设置中央窗口
            self.setCentralWidget(self.doodle_board)
            
            print("✅ 画板系统初始化成功")
            return True
            
        except Exception as e:
            QMessageBox.critical(self, "错误", f"画板初始化失败: {e}")
            print(f"[错误] 画板初始化失败: {e}")
            import traceback
            traceback.print_exc()
            return False
    
    def handle_canvas_message(self, topic, sender, message):
        """处理画板主题的消息"""
        if topic == "SHARED_CANVAS_TOPIC" and sender != self.username:
            try:
                # 解析消息数据
                data = json.loads(message)
                
                # 检查是否是清空消息
                if data.get('action') == 'clear_user':
                    username = data.get('username', '未知用户')
                    self.doodle_board.clear_user_drawings(username)
                    print(f"[调试] 收到清空消息: {sender} - 清空用户 {username}")
                    return
                
                # 处理绘制数据
                start_pos = (data['start']['x'], data['start']['y'])
                end_pos = (data['end']['x'], data['end']['y'])
                color = data.get('color', '#000000')
                width = data.get('width', 2)
                tool = data.get('tool', 'pen')
                username = data.get('username', '未知用户')
                
                # 将绘制数据添加到队列
                self.doodle_board.draw_line(start_pos, end_pos, color, width, tool, username)
                print(f"[调试] 收到画板数据: {sender} - {message}")
                
            except json.JSONDecodeError as e:
                print(f"[错误] 解析画板数据失败: {e}")
            except Exception as e:
                print(f"[错误] 处理画板数据失败: {e}")
    
    def closeEvent(self, event):
        """窗口关闭事件"""
        print("👋 画板窗口关闭，清理资源...")
        self.cleanup()
        event.accept()
    
    def cleanup(self):
        """清理DDS资源"""
        try:
            if 'participant' in self.dds_components:
                participant = self.dds_components['participant']
                print("✅ DDS资源清理完成")
        except Exception as e:
            print(f"[错误] 清理资源时出错: {e}")


def open_canvas_window(username, dds_manager=None):
    """打开画板窗口的函数"""
    try:
        canvas_window = CanvasWindow(username, dds_manager)
        if canvas_window.init_dds():
            canvas_window.show()
            return canvas_window
        else:
            canvas_window.close()
            return None
    except Exception as e:
        print(f"[错误] 打开画板窗口失败: {e}")
        return None
