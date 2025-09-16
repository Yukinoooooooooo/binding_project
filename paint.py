import sys
import time
import re
import json

from zrpy import _zrdds_basic as basic
from zrpy import _zrdds_domain as domain
from zrpy import _zrdds_topic as topic
from zrpy import _zrdds_publish as publish
from zrpy import _zrdds_listener as listener
from zrpy import _zrdds_subscribe as subscribe
from zrpy import _zrdds_shapetype as shapetype
from PySide6.QtCore import Qt, QTimer
from PySide6.QtGui import QMouseEvent, QColor, QPen
from PySide6.QtWidgets import (
    QApplication, QGraphicsScene, QGraphicsView, QGraphicsLineItem, QWidget,
    QVBoxLayout, QHBoxLayout, QPushButton, QSlider, QLabel, QColorDialog, QFrame
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



class DoodleBoard(QWidget):
    def __init__(self, dds_writer, dds_reader, self_name):
        super().__init__()
        self.dds_writer = dds_writer
        self.dds_reader = dds_reader
        self.self_name = self_name

        # 画板参数
        self.current_color = QColor(Qt.black)
        self.current_width = 2
        self.current_tool = "pen"  # pen/eraser

        # 画布
        self.scene = QGraphicsScene()
        self.view = QGraphicsView(self.scene)
        self.view.setBackgroundBrush(Qt.white)
        self.view.setMouseTracking(True)

        # 画图标记
        self.drawing = False
        self.last_pos = None

        # 队列和定时器
        self.draw_queue = Queue()
        self.timer = QTimer()
        self.timer.timeout.connect(self.process_draw_queue)
        self.timer.start(30)

        # UI控件区
        self.color_btn = QPushButton("调色盘")
        self.color_btn.clicked.connect(self.choose_color)
        self.width_slider = QSlider(Qt.Horizontal)
        self.width_slider.setMinimum(1)
        self.width_slider.setMaximum(20)
        self.width_slider.setValue(self.current_width)
        self.width_slider.valueChanged.connect(self.change_width)
        self.width_label = QLabel(f"粗细: {self.current_width}")
        self.eraser_btn = QPushButton("橡皮")
        self.eraser_btn.setCheckable(True)
        self.eraser_btn.toggled.connect(self.toggle_eraser)

        # 布局
        tool_layout = QHBoxLayout()
        tool_layout.addWidget(self.color_btn)
        tool_layout.addWidget(self.width_label)
        tool_layout.addWidget(self.width_slider)
        tool_layout.addWidget(self.eraser_btn)

        main_layout = QVBoxLayout(self)
        main_layout.addWidget(self.view)
        main_layout.addLayout(tool_layout)

        self.setLayout(main_layout)

        # 事件绑定
        self.view.mousePressEvent = self.mousePressEvent
        self.view.mouseMoveEvent = self.mouseMoveEvent
        self.view.mouseReleaseEvent = self.mouseReleaseEvent

    def choose_color(self):
        color = QColorDialog.getColor(self.current_color, self, "选择颜色")
        if color.isValid():
            self.current_color = color
            self.eraser_btn.setChecked(False)

    def change_width(self, value):
        self.current_width = value
        self.width_label.setText(f"粗细: {value}")

    def toggle_eraser(self, checked):
        self.current_tool = "eraser" if checked else "pen"
        if checked:
            self.current_color = QColor(Qt.white)
        else:
            self.current_color = QColorDialog.getColor(self.current_color, self, "选择颜色") if self.current_color == QColor(Qt.white) else self.current_color

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drawing = True
            self.last_pos = self.view.mapToScene(event.pos())

    def mouseMoveEvent(self, event: QMouseEvent):
        if self.drawing and self.last_pos:
            scene_pos = self.view.mapToScene(event.pos())
            pen = QPen(self.current_color, self.current_width)
            line = QGraphicsLineItem(self.last_pos.x(), self.last_pos.y(), scene_pos.x(), scene_pos.y())
            line.setPen(pen)
            self.scene.addItem(line)
            # 传入起点用于判断方向
            self.add_or_update_username_label(scene_pos, self.self_name, self.current_color, self.last_pos)
            self.send_drawing_data(self.last_pos, scene_pos, self.current_color, self.current_width, self.current_tool, self.self_name)
            self.last_pos = scene_pos
            self.view.viewport().update()

    def add_or_update_username_label(self, pos, username, color, start_pos=None):
        from PySide6.QtWidgets import QGraphicsTextItem
        if not hasattr(self, '_username_label_item') or self._username_label_item is None:
            self._username_label_item = QGraphicsTextItem(username)
            self._username_label_item.setDefaultTextColor(color)
            self.scene.addItem(self._username_label_item)
        self._username_label_item.setPlainText(username)
        self._username_label_item.setDefaultTextColor(color)
        offset = 10
        label_width = self._username_label_item.boundingRect().width()
        # 调试输出
        print(f"[调试] 本地标签坐标: start=({start_pos.x() if start_pos else 'None'}, {start_pos.y() if start_pos else 'None'}), end=({pos.x()}, {pos.y()}), label_width={label_width}")
        # 判断方向，左移则标签在左侧
        if start_pos is not None and pos.x() < start_pos.x():
            print("[调试] 标签显示在左侧")
            self._username_label_item.setPos(pos.x() - offset - label_width, pos.y() - 10)
        else:
            print("[调试] 标签显示在右侧")
            self._username_label_item.setPos(pos.x() + offset, pos.y() - 10)

    def mouseReleaseEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.drawing = False

    def send_drawing_data(self, start_pos, end_pos, color, width, tool, username):
        send_data = shapetype.ShapeType()
        line_data = {
            'start': {'x': start_pos.x(), 'y': start_pos.y()},
            'end': {'x': end_pos.x(), 'y': end_pos.y()},
            'color': color.name(),
            'width': width,
            'tool': tool,
            'username': username
        }
        send_data.z = json.dumps(line_data)
        ret = self.dds_writer.write(send_data, domain.HANDLE_NIL_NATIVE)
        if ret == basic.RETCODE_OK:
            print(f"[调试] 数据发送成功: {send_data.z}")
        else:
            print(f"[错误] 发送数据失败: {ret}")

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
            # 只保留一个远程用户标签，移动时更新位置
            if username not in self._remote_labels or self._remote_labels[username] is None:
                label_item = QGraphicsTextItem(username)
                label_item.setDefaultTextColor(QColor(color))
                self.scene.addItem(label_item)
                self._remote_labels[username] = label_item
            label_item = self._remote_labels[username]
            label_item.setPlainText(username)
            label_item.setDefaultTextColor(QColor(color))
            label_width = label_item.boundingRect().width()
            # 调试输出
            print(f"[调试] 远程标签坐标: start=({start_pos[0]}, {start_pos[1]}), end=({end_pos[0]}, {end_pos[1]}), label_width={label_width}")
            if end_pos[0] < start_pos[0]:
                print("[调试] 标签显示在左侧")
                label_item.setPos(end_pos[0] - offset - label_width, end_pos[1] - 10)
            else:
                print("[调试] 标签显示在右侧")
                label_item.setPos(end_pos[0] + offset, end_pos[1] - 10)
        self.view.viewport().update()


class ChatListener(listener.DataReaderListener):
    """聊天监听器，处理接收到的消息"""
    def __init__(self, self_name, draw_callback):
        super().__init__()
        self.self_name = self_name
        self.draw_callback = draw_callback  # 接收绘制回调函数

    def on_data_available(self, reader):
        try:
            while True:
                data = shapetype.ShapeType()
                sample_info = shapetype.SampleInfo()
                ret = reader.take_next_sample(data, sample_info)
                if ret == basic.RETCODE_OK and sample_info.valid_data:
                    line_data_json = safe_str(data.z)
                    try:
                        line_data = json.loads(line_data_json)
                        start_pos = (line_data['start']['x'], line_data['start']['y'])
                        end_pos = (line_data['end']['x'], line_data['end']['y'])
                        color = line_data.get('color', '#000000')
                        width = line_data.get('width', 2)
                        tool = line_data.get('tool', 'pen')
                        username = line_data.get('username', '未知用户')
                        self.draw_callback(start_pos, end_pos, color, width, tool, username)
                    except json.JSONDecodeError as e:
                        print(f"[错误] JSON 解析失败: {e}")
                else:
                    break
        except Exception as e:
            print(f"[错误] 处理接收消息时出错: {e}")

def main():
    app = QApplication(sys.argv)
    print("=== ZRDDS Python 共享画板示例 ===")
    print("=" * 40)
    self_name = input("请输入你的名字: ").strip()
    if not self_name:
        self_name = "匿名用户"
    print("🚀 启动共享画板系统...")

    # DDS初始化部分
    domain_id = 80
    participant = None
    topic_name = "SHARED_CANVAS_TOPIC"
    topic = None
    factory = domain.TheParticipantFactory
    if factory is None:
        print("[错误] 获取工厂实例失败")
        return
    print("✅ 获取域参与者工厂成功")
    qos = domain.DomainParticipantQos()
    ret = factory.get_default_participant_qos(qos)
    if ret != basic.RETCODE_OK:
        print(f"[错误] 获取默认 QoS 失败: {ret}")
        return
    participant = factory.create_participant(domain_id, qos, None, 0)
    if participant is None:
        print("[错误] 创建域参与者失败")
        return
    print("✅ 创建域参与者成功")
    shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
    ret = shapetype_support.register_type(participant, None)
    if ret != basic.RETCODE_OK:
        print(f"[错误] 注册类型失败: {ret}")
        return
    print("✅ 注册 ShapeType 类型成功")
    topic_qos = domain.TopicQos()
    ret = participant.get_default_topic_qos(topic_qos)
    if ret != basic.RETCODE_OK:
        print(f"[错误] 获取默认主题 QoS 失败: {ret}")
        return
    topic = participant.create_topic(
        topic_name,
        shapetype_support.get_type_name(),
        topic_qos,
        None,
        0
    )
    if topic is None:
        print("[错误] 创建主题失败")
        return
    print("✅ 创建主题成功")
    publisher_qos = domain.PublisherQos()
    ret = participant.get_default_publisher_qos(publisher_qos)
    if ret != basic.RETCODE_OK:
        print(f"[错误] 获取默认发布者 QoS 失败: {ret}")
        return
    publisher = participant.create_publisher(publisher_qos, None, 0)
    if publisher is None:
        print("[错误] 创建发布者失败")
        return
    print("✅ 创建发布者成功")
    subscriber_qos = domain.SubscriberQos()
    ret = participant.get_default_subscriber_qos(subscriber_qos)
    if ret != basic.RETCODE_OK:
        print(f"[错误] 获取默认订阅者 QoS 失败: {ret}")
        return
    subscriber = participant.create_subscriber(subscriber_qos, None, 0)
    if subscriber is None:
        print("[错误] 创建订阅者失败")
        return
    print("✅ 创建订阅者成功")
    ret, datawriter_qos = publisher.get_default_datawriter_qos()
    if ret != basic.RETCODE_OK:
        print(f"[错误] 获取默认 DataWriter QoS 失败: {ret}")
        return
    datawriter = publisher.create_datawriter(topic, datawriter_qos, None, 0)
    if datawriter is None:
        print("[错误] 创建数据写者失败")
        return
    print("✅ 创建数据写者成功")
    chat_listener = ChatListener(self_name, lambda start, end, color, width, tool, username: None)
    ret, datareader_qos = subscriber.get_default_datareader_qos()
    if ret != basic.RETCODE_OK:
        print(f"[错误] 获取默认 DataReader QoS 失败: {ret}")
        return
    datareader = subscriber.create_datareader(topic, datareader_qos, chat_listener, 1024)
    if datareader is None:
        print("[错误] 创建数据读者失败")
        return
    print("✅ 所有模块导入成功")
    window = DoodleBoard(dds_writer=datawriter, dds_reader=datareader, self_name=self_name)
    chat_listener.draw_callback = window.draw_line
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
