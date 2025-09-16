# -*- coding: utf-8 -*-
# 简化的DDS发布器：每次移动发送蛇与食物位置（使用 shapetype.ShapeType）
import os, sys, json, time
from PySide6.QtCore import QObject, Signal

# ========== ZRDDS 模块加载 ==========
current_dir = os.path.dirname(os.path.abspath(__file__))
zrpy_dir = os.path.join(current_dir, 'zrpy')
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, zrpy_dir)
sys.path.insert(0, build_release_dir)

import _zrdds_basic as basic
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
import _zrdds_listener as listener
import _zrdds_subscribe as subscribe
import _zrdds_shapetype as shapetype


class SnakeSignalProxy(QObject):
    stateReceived = Signal(str, int, dict)  # username, user_id, payload


class SnakeDDS:
    """仅发布当前状态；主题默认 PRETTY_SNAKE_STATE，域 82"""

    def __init__(self, username: str, user_id: int, topic_name: str = "PRETTY_SNAKE_STATE", domain_id: int = 82):
        self.username = username
        self.user_id = user_id
        self.topic_name = topic_name
        self.domain_id = domain_id
        self.participant = None
        self.writer = None
        self.proxy = SnakeSignalProxy()
        self._listener = None

    def initialize(self) -> bool:
        try:
            factory = domain.TheParticipantFactory
            qos = domain.DomainParticipantQos()
            factory.get_default_participant_qos(qos)
            self.participant = factory.create_participant(self.domain_id, qos, None, 0)

            shapetype_support = shapetype.ShapeTypeTypeSupport.get_instance()
            shapetype_support.register_type(self.participant, None)

            topic_qos = domain.TopicQos()
            self.participant.get_default_topic_qos(topic_qos)
            topic_obj = self.participant.create_topic(self.topic_name, shapetype_support.get_type_name(), topic_qos, None, 0)

            pub_qos = domain.PublisherQos()
            self.participant.get_default_publisher_qos(pub_qos)
            publisher = self.participant.create_publisher(pub_qos, None, 0)

            ret, dw_qos = publisher.get_default_datawriter_qos()
            self.writer = publisher.create_datawriter(topic_obj, dw_qos, None, 0)

            # 订阅者
            sub_qos = domain.SubscriberQos()
            self.participant.get_default_subscriber_qos(sub_qos)
            subscriber = self.participant.create_subscriber(sub_qos, None, 0)

            self._listener = SnakeListener(self.user_id, self.proxy)
            ret, dr_qos = subscriber.get_default_datareader_qos()
            subscriber.create_datareader(topic_obj, dr_qos, self._listener, 1024)
            return True
        except Exception as e:
            print(f"[DDS] 初始化失败: {e}")
            return False

    def send_state(self, snake: list, food: dict, score: int, over: bool = False) -> bool:
        if not self.writer:
            return False
        try:
             # 紧凑编码，避免超过 shapetype.z 限制
            snake_pairs = [[int(p.get("x", 0)), int(p.get("y", 0))] for p in snake]
            food_pair = [int(food.get("x", 0)), int(food.get("y", 0))]
            ts = int(time.time() * 1000)
            payload = {"u": self.username, "s": snake_pairs, "f": food_pair, "sc": int(score), "o": bool(over), "t": ts}
            encoded = json.dumps(payload, ensure_ascii=False, separators=(',', ':'))

            # 长度保护：限制总字节数
            max_bytes = 240
            if len(encoded.encode('utf-8')) > max_bytes:
                max_segments = 120
                if len(snake_pairs) > max_segments:
                    step = max(1, len(snake_pairs) // max_segments)
                    snake_pairs = snake_pairs[::step]
                    payload["s"] = snake_pairs
                    encoded = json.dumps(payload, ensure_ascii=False, separators=(',', ':'))
            if len(encoded.encode('utf-8')) > max_bytes and snake_pairs:
                payload = {"u": self.username, "s": [snake_pairs[0]], "l": len(snake_pairs), "f": food_pair, "sc": int(score), "o": bool(over)}
                encoded = json.dumps(payload, ensure_ascii=False, separators=(',', ':'))

            msg = shapetype.ShapeType()
            msg.x = int(self.user_id)
            msg.y = ts % 1000
            msg.z = encoded
            self.writer.write(msg, domain.HANDLE_NIL_NATIVE)
            return True
        except Exception as e:
            print(f"[DDS] 发送失败: {e}")
            return False

    def cleanup(self):
        try:
            if self.participant:
                print("[DDS] 资源清理完成")
        except Exception as _:
            pass

    def get_proxy(self) -> SnakeSignalProxy:
        return self.proxy


class SnakeListener(listener.DataReaderListener):
    def __init__(self, self_id: int, proxy: SnakeSignalProxy):
        super().__init__()
        self.self_id = self_id
        self.proxy = proxy

    def on_data_available(self, reader):
        try:
            while True:
                data = shapetype.ShapeType()
                info = shapetype.SampleInfo()
                ret = reader.read_next_sample(data, info)
                if ret == basic.RETCODE_OK and info.valid_data:
                    sender_id = int(data.x)
                    if sender_id == int(self.self_id):
                        continue
                    try:
                        payload = json.loads(data.z)
                        # 将简化的payload转换为完整格式
                        full_payload = {
                            "user": payload.get("u", ""),
                            "snake": [{"x": p[0], "y": p[1]} for p in payload.get("s", [])],
                            "food": {"x": payload.get("f", [0, 0])[0], "y": payload.get("f", [0, 0])[1]},
                            "score": payload.get("sc", 0),
                            "over": payload.get("o", False),
                            "ts": payload.get("t", 0)
                        }
                        user = full_payload.get("user", "")
                        self.proxy.stateReceived.emit(user, sender_id, full_payload)
                    except Exception as e:
                        print(f"[DDS] 数据解析失败: {e}")
                        pass
                else:
                    break
        except Exception as e:
            print(f"[DDS] 订阅处理失败: {e}")


