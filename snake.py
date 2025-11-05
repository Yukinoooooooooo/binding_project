# -*- coding: utf-8 -*-
# 漂亮风格的本地贪吃蛇（独立运行）
import sys
import random
from dataclasses import dataclass
from typing import List, Dict, Optional

from PySide6.QtCore import Qt, QTimer, QPoint
from PySide6.QtGui import QPainter, QColor, QPen, QBrush, QFont
from PySide6.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton,
    QFrame, QSlider, QSizePolicy, QListWidget, QListWidgetItem
)

# 导入游戏结束界面函数
from end import draw_game_over_screen, get_score_level, draw_game_over_decorations


@dataclass
class Position:
    x: int
    y: int


class Direction:
    UP = QPoint(0, -1)
    DOWN = QPoint(0, 1)
    LEFT = QPoint(-1, 0)
    RIGHT = QPoint(1, 0)


class SnakeGameLogic:
    """本地贪吃蛇核心逻辑"""

    def __init__(self, width: int = 32, height: int = 22):
        self.width = width
        self.height = height
        self.reset()

    def reset(self, remote_snakes: Dict[int, Dict] = None):
        self.snake: List[Position] = []
        # 随机生成复活位置，避免与远端玩家重叠
        self.generate_random_start_position(remote_snakes)
        self.direction = Direction.RIGHT
        self.pending_direction: Optional[QPoint] = None
        self.score = 0
        self.game_over = False
        self.foods: List[Position] = []  # 多个食物
        self.generate_multiple_foods()

    def generate_food(self):
        while True:
            fx = random.randint(0, self.width - 1)
            fy = random.randint(0, self.height - 1)
            pos = Position(fx, fy)
            if all(pos.x != s.x or pos.y != s.y for s in self.snake):
                self.food = pos
                break
    
    def generate_multiple_foods(self):
        """生成多个食物"""
        self.foods = []
        food_count = 5  # 生成5个食物
        
        for _ in range(food_count):
            while True:
                fx = random.randint(0, self.width - 1)
                fy = random.randint(0, self.height - 1)
                pos = Position(fx, fy)
                
                # 检查不与蛇身重叠
                snake_conflict = any(pos.x == s.x and pos.y == s.y for s in self.snake)
                # 检查不与已有食物重叠
                food_conflict = any(pos.x == f.x and pos.y == f.y for f in self.foods)
                
                if not snake_conflict and not food_conflict:
                    self.foods.append(pos)
                    break
    
    def generate_random_start_position(self, remote_snakes: Dict[int, Dict] = None):
        """生成随机起始位置，避免与远端玩家重叠"""
        # 确保起始位置不会太靠近边界
        margin = 3
        min_x = margin
        max_x = self.width - margin - 4  # 为蛇身留出空间
        min_y = margin
        max_y = self.height - margin
        
        max_attempts = 50  # 最大尝试次数
        for attempt in range(max_attempts):
            # 随机选择起始位置
            start_x = random.randint(min_x, max_x)
            start_y = random.randint(min_y, max_y)
            
            # 生成蛇身（4节）
            snake_positions = [Position(start_x - i, start_y) for i in range(4)]
            
            # 检查是否与远端玩家重叠
            if remote_snakes:
                overlap = False
                for uid, payload in remote_snakes.items():
                    remote_snake = payload.get("snake", [])
                    for seg in remote_snake:
                        seg_pos = Position(seg.get("x", 0), seg.get("y", 0))
                        if any(pos.x == seg_pos.x and pos.y == seg_pos.y for pos in snake_positions):
                            overlap = True
                            break
                    if overlap:
                        break
                
                if not overlap:
                    self.snake = snake_positions
                    print(f"[复活] 随机起始位置: ({start_x}, {start_y}) - 避免重叠")
                    return
            
            # 如果没有远端玩家或没有重叠，直接使用
            if not remote_snakes:
                self.snake = snake_positions
                print(f"[复活] 随机起始位置: ({start_x}, {start_y})")
                return
        
        # 如果尝试次数用完，使用默认位置
        start_x = self.width // 2
        start_y = self.height // 2
        self.snake = [Position(start_x - i, start_y) for i in range(4)]
        print(f"[复活] 使用默认位置: ({start_x}, {start_y})")
    
    def generate_single_food(self):
        """生成单个食物补充"""
        while True:
            fx = random.randint(0, self.width - 1)
            fy = random.randint(0, self.height - 1)
            pos = Position(fx, fy)
            
            # 检查不与蛇身重叠
            snake_conflict = any(pos.x == s.x and pos.y == s.y for s in self.snake)
            # 检查不与已有食物重叠
            food_conflict = any(pos.x == f.x and pos.y == f.y for f in self.foods)
            
            if not snake_conflict and not food_conflict:
                self.foods.append(pos)
                break

    def set_direction(self, new_dir: QPoint):
        # 禁止直接反向
        cur = self.direction
        if cur.x() + new_dir.x() == 0 and cur.y() + new_dir.y() == 0:
            return
        # 采用排队生效，避免同一帧多次变向导致的反向
        self.pending_direction = new_dir

    def step(self, remote_snakes: Dict[int, Dict] = None) -> Dict:
        if self.game_over:
            return self.state()

        if self.pending_direction is not None:
            self.direction = self.pending_direction
            self.pending_direction = None

        head = self.snake[0]
        nx = head.x + self.direction.x()
        ny = head.y + self.direction.y()
        new_head = Position(nx, ny)

        # 撞墙
        if nx < 0 or nx >= self.width or ny < 0 or ny >= self.height:
            self.game_over = True
            return self.state()

        # 撞到自己不会死，可以穿过去
        # if any(new_head.x == s.x and new_head.y == s.y for s in self.snake):
        #     self.game_over = True
        #     return self.state()

        # 撞远端玩家
        if remote_snakes:
            for uid, payload in remote_snakes.items():
                remote_snake = payload.get("snake", [])
                for seg in remote_snake:
                    if new_head.x == seg.get("x", 0) and new_head.y == seg.get("y", 0):
                        self.game_over = True
                        print(f"[碰撞] 撞到玩家 {payload.get('user', 'Unknown')}")
                        return self.state()

        # 前进
        self.snake.insert(0, new_head)

        # 检查是否吃到食物
        eaten_food = None
        for i, food in enumerate(self.foods):
            if new_head.x == food.x and new_head.y == food.y:
                self.score += 10
                eaten_food = i
                break

        if eaten_food is not None:
            # 移除被吃掉的食物
            self.foods.pop(eaten_food)
            # 生成新食物补充
            self.generate_single_food()
        else:
            self.snake.pop()

        return self.state()

    def state(self) -> Dict:
        return {
            "width": self.width,
            "height": self.height,
            "snake": [{"x": s.x, "y": s.y} for s in self.snake],
            "foods": [{"x": f.x, "y": f.y} for f in self.foods],  # 多个食物
            "score": self.score,
            "over": self.game_over,
        }


class SnakeCanvas(QWidget):
    """美观画布：暗色主题，柔和网格，圆角方块，发光食物"""

    def __init__(self, logic: SnakeGameLogic, parent=None):
        super().__init__(parent)
        self.logic = logic
        self.cell = 24  # 初始格子大小（较小）
        self.offset_x = 0  # 水平偏移
        self.offset_y = 0  # 垂直偏移
        self.setMinimumSize(400, 300)  # 设置最小尺寸
        self.setFocusPolicy(Qt.StrongFocus)
        self.primary = QColor("#4ECDC4")
        self.primary_head = QColor("#76EAD7")
        self.grid_color = QColor(45, 55, 72)
        self.bg_color = QColor(26, 32, 44)
        self.food_color = QColor(255, 107, 107)
        self.remote_snakes: Dict[int, Dict] = {}
        
        # 游戏结束界面相关变量
        self.game_over_alpha = 0  # 游戏结束界面透明度
        self.final_score = 0  # 最终分数
        self.game_over_timer = QTimer(self)  # 游戏结束动画定时器
        self.game_over_timer.timeout.connect(self.update_game_over_alpha)

    def update_game_over_alpha(self):
        """更新游戏结束界面透明度"""
        if self.game_over_alpha < 200:
            self.game_over_alpha += 5
            self.update()
        else:
            self.game_over_timer.stop()

    def start_game_over_animation(self, final_score):
        """开始游戏结束动画"""
        self.final_score = final_score
        self.game_over_alpha = 0
        self.game_over_timer.start(50)  # 每50毫秒更新一次

    def calculate_cell_size(self):
        """计算自适应的格子大小和居中偏移"""
        widget_width = self.width()
        widget_height = self.height()
        
        # 确保有有效的尺寸
        if widget_width <= 0 or widget_height <= 0:
            self.cell = 24  # 使用较小的默认值
            self.offset_x = 0
            self.offset_y = 0
            return
        
        # 检查窗口是否最大化
        window = self.window()
        is_maximized = window.isMaximized()
        
        if is_maximized:
            # 最大化时：计算水平和垂直方向的最大格子大小，但限制最大比例
            cell_width = widget_width / self.logic.width
            cell_height = widget_height / self.logic.height
            
            # 选择较小的值，但限制最大格子大小
            max_cell_size = 30  # 限制最大格子大小
            new_cell = min(cell_width, cell_height, max_cell_size)
        else:
            # 非最大化时：使用较小的固定大小
            new_cell = 24
        
        # 计算网格总尺寸
        grid_width = self.logic.width * new_cell
        grid_height = self.logic.height * new_cell
        
        # 计算居中偏移
        self.offset_x = (widget_width - grid_width) / 2
        self.offset_y = (widget_height - grid_height) / 2
        
        # 只有当格子大小变化较大时才更新，避免频繁重绘
        if abs(new_cell - self.cell) > 1:
            self.cell = new_cell
            print(f"[调试] 格子大小更新: {self.cell:.1f}, 窗口: {widget_width}x{widget_height}, 最大化: {is_maximized}, 偏移: ({self.offset_x:.1f}, {self.offset_y:.1f})")

    def resizeEvent(self, event):
        """窗口大小改变时重新计算格子大小"""
        super().resizeEvent(event)
        self.calculate_cell_size()

    def keyPressEvent(self, event):
        key = event.key()
        mapping = {
            Qt.Key_Up: Direction.UP,
            Qt.Key_W: Direction.UP,
            Qt.Key_Down: Direction.DOWN,
            Qt.Key_S: Direction.DOWN,
            Qt.Key_Left: Direction.LEFT,
            Qt.Key_A: Direction.LEFT,
            Qt.Key_Right: Direction.RIGHT,
            Qt.Key_D: Direction.RIGHT,
        }
        if key in mapping:
            self.logic.set_direction(mapping[key])
    
    def draw_snake_eyes(self, painter, sx, sy, head_seg):
        """绘制蛇头眼睛 - 紧凑的黑点"""
        # 眼睛颜色 - 直接使用黑色
        eye_color = QColor(0, 0, 0)  # 黑色眼睛
        
        # 根据蛇的移动方向确定眼睛位置
        direction = self.logic.direction
        
        # 眼睛大小（根据格子大小自适应调整，更大一些）
        eye_size = max(3, int(self.cell * 0.12))  # 格子大小的12%，最小3像素
        
        # 眼睛在蛇头中的位置（更靠近中心）
        eye_offset = max(3, int(self.cell * 0.25))  # 格子大小的25%，最小3像素
        
        if direction == Direction.RIGHT:
            # 向右移动：眼睛在右侧，上下排列
            left_eye_x = sx + self.cell - eye_offset - eye_size
            right_eye_x = sx + self.cell - eye_offset - eye_size
            left_eye_y = sy + eye_offset
            right_eye_y = sy + self.cell - eye_offset - eye_size
        elif direction == Direction.LEFT:
            # 向左移动：眼睛在左侧，上下排列
            left_eye_x = sx + eye_offset
            right_eye_x = sx + eye_offset
            left_eye_y = sy + eye_offset
            right_eye_y = sy + self.cell - eye_offset - eye_size
        elif direction == Direction.UP:
            # 向上移动：眼睛在上方，左右排列
            left_eye_x = sx + eye_offset
            right_eye_x = sx + self.cell - eye_offset - eye_size
            left_eye_y = sy + eye_offset
            right_eye_y = sy + eye_offset
        else:  # DOWN
            # 向下移动：眼睛在下方，左右排列
            left_eye_x = sx + eye_offset
            right_eye_x = sx + self.cell - eye_offset - eye_size
            left_eye_y = sy + self.cell - eye_offset - eye_size
            right_eye_y = sy + self.cell - eye_offset - eye_size
        
        # 绘制左眼（黑色圆点）
        painter.setBrush(QBrush(eye_color))
        painter.setPen(Qt.NoPen)
        painter.drawEllipse(left_eye_x, left_eye_y, eye_size, eye_size)
        
        # 绘制右眼（黑色圆点）
        painter.setBrush(QBrush(eye_color))
        painter.drawEllipse(right_eye_x, right_eye_y, eye_size, eye_size)
    
    def draw_remote_snake_eyes(self, painter, sx, sy, head_seg, snake_body):
        """绘制远端蛇头眼睛 - 根据移动方向绘制"""
        # 远端蛇眼睛颜色（深灰色，与本地蛇区分）
        eye_color = QColor(50, 50, 50)  # 深灰色眼睛
        
        # 眼睛大小（根据格子大小自适应调整，更大一些）
        eye_size = max(3, int(self.cell * 0.12))  # 格子大小的12%，最小3像素
        eye_offset = max(3, int(self.cell * 0.25))  # 格子大小的25%，最小3像素
        
        # 根据蛇身推断移动方向
        direction = self.infer_remote_snake_direction(snake_body)
        
        # 根据方向确定眼睛位置
        if direction == Direction.RIGHT:
            # 向右移动：眼睛在右侧，上下排列
            left_eye_x = sx + self.cell - eye_offset - eye_size
            right_eye_x = sx + self.cell - eye_offset - eye_size
            left_eye_y = sy + eye_offset
            right_eye_y = sy + self.cell - eye_offset - eye_size
        elif direction == Direction.LEFT:
            # 向左移动：眼睛在左侧，上下排列
            left_eye_x = sx + eye_offset
            right_eye_x = sx + eye_offset
            left_eye_y = sy + eye_offset
            right_eye_y = sy + self.cell - eye_offset - eye_size
        elif direction == Direction.UP:
            # 向上移动：眼睛在上方，左右排列
            left_eye_x = sx + eye_offset
            right_eye_x = sx + self.cell - eye_offset - eye_size
            left_eye_y = sy + eye_offset
            right_eye_y = sy + eye_offset
        else:  # DOWN
            # 向下移动：眼睛在下方，左右排列
            left_eye_x = sx + eye_offset
            right_eye_x = sx + self.cell - eye_offset - eye_size
            left_eye_y = sy + self.cell - eye_offset - eye_size
            right_eye_y = sy + self.cell - eye_offset - eye_size
        
        # 绘制左眼（深灰色圆点）
        painter.setBrush(QBrush(eye_color))
        painter.setPen(Qt.NoPen)
        painter.drawEllipse(left_eye_x, left_eye_y, eye_size, eye_size)
        
        # 绘制右眼（深灰色圆点）
        painter.setBrush(QBrush(eye_color))
        painter.drawEllipse(right_eye_x, right_eye_y, eye_size, eye_size)

    def infer_remote_snake_direction(self, snake_body):
        """根据蛇身推断远端蛇的移动方向"""
        if len(snake_body) < 2:
            return Direction.RIGHT  # 默认向右
        
        # 获取蛇头和第二节的位置
        head = snake_body[0]
        neck = snake_body[1]
        
        head_x = head.get("x", 0)
        head_y = head.get("y", 0)
        neck_x = neck.get("x", 0)
        neck_y = neck.get("y", 0)
        
        # 计算移动方向
        dx = head_x - neck_x
        dy = head_y - neck_y
        
        if dx > 0:
            return Direction.RIGHT
        elif dx < 0:
            return Direction.LEFT
        elif dy > 0:
            return Direction.DOWN
        elif dy < 0:
            return Direction.UP
        else:
            return Direction.RIGHT  # 默认向右

    def paintEvent(self, _):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        # 确保格子大小已计算
        self.calculate_cell_size()

        # 背景
        painter.fillRect(self.rect(), self.bg_color)

        # 网格
        painter.setPen(QPen(self.grid_color, 1))
        w = self.logic.width
        h = self.logic.height
        for x in range(w + 1):
            x_pos = self.offset_x + 1 + x * self.cell
            painter.drawLine(x_pos, self.offset_y + 1, x_pos, self.offset_y + 1 + h * self.cell)
        for y in range(h + 1):
            y_pos = self.offset_y + 1 + y * self.cell
            painter.drawLine(self.offset_x + 1, y_pos, self.offset_x + 1 + w * self.cell, y_pos)

        # 多个食物（发光圆形）
        painter.setPen(Qt.NoPen)
        painter.setBrush(QBrush(self.food_color))
        for food in self.logic.foods:
            fx = self.offset_x + 1 + food.x * self.cell
            fy = self.offset_y + 1 + food.y * self.cell
            painter.drawEllipse(fx + 4, fy + 4, self.cell - 8, self.cell - 8)

        # 蛇：头部更亮，圆角矩形
        snake = self.logic.snake
        for i, seg in enumerate(snake):
            sx = self.offset_x + 1 + seg.x * self.cell
            sy = self.offset_y + 1 + seg.y * self.cell
            color = self.primary_head if i == 0 else self.primary
            painter.setBrush(QBrush(color))
            painter.setPen(QPen(QColor(0, 0, 0, 180), 1))
            painter.drawRoundedRect(sx + 2, sy + 2, self.cell - 4, self.cell - 4, 6, 6)
            
            # 为蛇头添加眼睛
            if i == 0:
                self.draw_snake_eyes(painter, sx, sy, seg)

        # 远端蛇（使用不同配色）
        for uid, payload in self.remote_snakes.items():
            body = payload.get("snake", [])
            color_body = QColor("#FFD166")
            color_head = QColor("#FFE08A")
            for i, seg in enumerate(body):

                sx = self.offset_x + 1 + int(seg.get("x", 0)) * self.cell
                sy = self.offset_y + 1 + int(seg.get("y", 0)) * self.cell
                color = color_head if i == 0 else color_body
                painter.setBrush(QBrush(color))
                painter.setPen(QPen(QColor(0, 0, 0, 160), 1))
                painter.drawRoundedRect(sx + 2, sy + 2, self.cell - 4, self.cell - 4, 6, 6)
                
                # 为远端蛇头添加眼睛
                if i == 0:
                    self.draw_remote_snake_eyes(painter, sx, sy, seg, body)

        # 如果游戏结束，绘制游戏结束界面
        if self.logic.game_over and self.game_over_alpha > 0:
            draw_game_over_screen(self, painter)


class Snake(QWidget):
    """带控制面板贪吃蛇"""

    def __init__(self, username: str = "Player", user_id: int = 0, enable_dds: bool = True):
        super().__init__()
        self.setWindowTitle("🐍 贪吃蛇")
        self.setStyleSheet("""
            QWidget { background-color: #1a202c; color: #ffffff; }
            QPushButton {
                background-color: #4299e1; border: none; border-radius: 6px;
                padding: 8px 16px; color: #fff; font-weight: bold; font-family: 'Microsoft YaHei';
            }
            QPushButton:hover { background-color: #3182ce; }
            QPushButton:pressed { background-color: #2c5282; }
            QFrame#panel { background-color: #2d3748; border-radius: 8px; }
        """)

        self.logic = SnakeGameLogic()
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.on_tick)
        self.interval_ms = 140
        self.username = username
        self.user_id = user_id
        self.enable_dds = enable_dds
        self.dds = None
        
        # 排行榜数据管理
        self.leaderboard_data = {}  # {user_id: {"username": str, "score": int, "is_self": bool}}

        root = QVBoxLayout(self)
        root.setContentsMargins(16, 16, 16, 16)
        root.setSpacing(12)

        # 标题栏
        title = QLabel("🐍 贪吃蛇")
        title.setFont(QFont("Microsoft YaHei", 18, QFont.Bold))
        title.setAlignment(Qt.AlignCenter)
        root.addWidget(title)

        # 主体区域
        body = QHBoxLayout()
        body.setSpacing(12)
        root.addLayout(body)

        # 画布（设置为可伸缩）
        self.canvas = SnakeCanvas(self.logic)
        self.canvas.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        body.addWidget(self.canvas, 1)

        # 控制面板
        panel = QFrame()
        panel.setObjectName("panel")
        panel_layout = QVBoxLayout(panel)
        panel_layout.setContentsMargins(14, 14, 14, 14)
        panel_layout.setSpacing(12)

        self.status_label = QLabel("就绪")
        self.score_label = QLabel("分数：0")
        self.remote_label = QLabel("其他玩家：0")
        
        # 设置状态标签样式
        self.status_label.setStyleSheet("""
            color: #E2E8F0; 
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
            font-size: 14px; 
            font-weight: 500;
            padding: 6px 0px;
        """)
        panel_layout.addWidget(self.status_label)
        
        # 设置分数标签样式（更突出）
        self.score_label.setStyleSheet("""
            color: #4ECDC4; 
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
            font-size: 16px; 
            font-weight: bold;
            padding: 8px 12px;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                stop:0 rgba(78, 205, 196, 0.1), stop:1 rgba(78, 205, 196, 0.05));
            border-radius: 8px;
            border: 1px solid rgba(78, 205, 196, 0.3);
        """)
        panel_layout.addWidget(self.score_label)
        
        # 设置其他玩家标签样式
        self.remote_label.setStyleSheet("""
            color: #A0AEC0; 
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
            font-size: 13px; 
            font-weight: 400;
            padding: 4px 0px;
        """)
        panel_layout.addWidget(self.remote_label)

        self.btn_start = QPushButton("开始")
        self.btn_reset = QPushButton("重置")
        
        # 美化开始按钮
        self.btn_start.setStyleSheet("""
            QPushButton {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #4ECDC4, stop:1 #45B7B8);
                color: #1a202c;
                border: none;
                border-radius: 8px;
                padding: 10px 20px;
                font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
                font-size: 14px;
                font-weight: bold;
                min-height: 20px;
            }
            QPushButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #76EAD7, stop:1 #6BDDDD);
                transform: translateY(-1px);
            }
            QPushButton:pressed {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #3BB5B6, stop:1 #3A9B9C);
                transform: translateY(1px);
            }
        """)
        
        # 美化重置按钮
        self.btn_reset.setStyleSheet("""
            QPushButton {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #FF6B6B, stop:1 #FF5252);
                color: white;
                border: none;
                border-radius: 8px;
                padding: 10px 20px;
                font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
                font-size: 14px;
                font-weight: bold;
                min-height: 20px;
            }
            QPushButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #FF8E8E, stop:1 #FF7979);
                transform: translateY(-1px);
            }
            QPushButton:pressed {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #E55555, stop:1 #E53E3E);
                transform: translateY(1px);
            }
        """)
        
        btn_row = QHBoxLayout()
        btn_row.addWidget(self.btn_start)
        btn_row.addWidget(self.btn_reset)
        panel_layout.addLayout(btn_row)

        speed_title = QLabel("⚡ 速度控制")
        speed_title.setStyleSheet("""
            color: #E2E8F0; 
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
            font-size: 14px; 
            font-weight: 600;
            padding: 8px 0px 4px 0px;
        """)
        panel_layout.addWidget(speed_title)

        speed_row = QHBoxLayout()
        self.slider = QSlider(Qt.Horizontal)
        self.slider.setRange(60, 400)
        self.slider.setValue(self.interval_ms)
        self.slider.valueChanged.connect(self.on_speed_change)
        
        # 美化滑块样式
        self.slider.setStyleSheet("""
            QSlider::groove:horizontal {
                border: 1px solid #4A5568;
                height: 6px;
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0, 
                    stop:0 #2D3748, stop:1 #4A5568);
                border-radius: 3px;
            }
            QSlider::handle:horizontal {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #4ECDC4, stop:1 #45B7B8);
                border: 2px solid #1a202c;
                width: 18px;
                height: 18px;
                border-radius: 9px;
                margin: -6px 0;
            }
            QSlider::handle:horizontal:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #76EAD7, stop:1 #6BDDDD);
            }
        """)
        
        self.speed_value_label = QLabel(str(self.interval_ms))
        self.speed_value_label.setStyleSheet("""
            color: #4ECDC4; 
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
            font-size: 16px; 
            font-weight: bold;
            min-width: 50px;
            padding: 4px 8px;
            background: rgba(78, 205, 196, 0.1);
            border-radius: 6px;
            border: 1px solid rgba(78, 205, 196, 0.3);
        """)
        speed_row.addWidget(self.slider, 1)
        speed_row.addWidget(self.speed_value_label)
        panel_layout.addLayout(speed_row)

        # 在线玩家排行榜
        leaderboard_title = QLabel("🏆排行榜")
        leaderboard_title.setStyleSheet("""
            color: #FFD700; 
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
            font-weight: bold; 
            font-size: 16px;
            margin-top: 20px;
            padding: 8px 12px;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                stop:0 rgba(255, 215, 0, 0.15), stop:1 rgba(255, 215, 0, 0.05));
            border-radius: 8px;
            border: 1px solid rgba(255, 215, 0, 0.3);
        """)
        leaderboard_title.setAlignment(Qt.AlignCenter)
        panel_layout.addWidget(leaderboard_title)
        
        # 排行榜列表
        self.leaderboard_list = QListWidget()
        self.leaderboard_list.setMaximumHeight(200)
        self.leaderboard_list.setStyleSheet("""
            QListWidget {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #2d3748, stop:1 #1a202c);
                border: 2px solid #4a5568;
                border-radius: 8px;
                color: #e2e8f0;
                font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
                font-size: 13px;
                font-weight: 500;
            }
            QListWidget::item {
                padding: 8px 12px;
                border-bottom: 1px solid rgba(74, 85, 104, 0.3);
                margin: 2px;
                border-radius: 4px;
            }
            QListWidget::item:hover {
                background-color: rgba(66, 153, 225, 0.1);
                border: 1px solid rgba(66, 153, 225, 0.3);
            }
            QListWidget::item:selected {
                background-color: rgba(66, 153, 225, 0.2);
                border: 1px solid rgba(66, 153, 225, 0.5);
            }
        """)
        panel_layout.addWidget(self.leaderboard_list)

        panel_layout.addStretch(1)
        body.addWidget(panel, 0)

        # 绑定事件
        self.btn_start.clicked.connect(self.start)
        self.btn_reset.clicked.connect(self.reset)

        # 初始化DDS（仅发布本地状态）
        if self.enable_dds:
            try:
                from snake_dds import SnakeDDS
                self.dds = SnakeDDS(self.username, self.user_id)
                if self.dds.initialize():
                    proxy = self.dds.get_proxy()
                    proxy.stateReceived.connect(self.on_remote_state)
                else:
                    self.dds = None
            except Exception as e:
                print(f"[DDS] 初始化失败: {e}")

    def on_speed_change(self, value: int):
        self.interval_ms = int(value)
        self.speed_value_label.setText(str(self.interval_ms))
        if self.timer.isActive():
            self.timer.start(self.interval_ms)

    def start(self):
        if self.logic.game_over:
            # 游戏结束后重新开始，使用随机位置
            self.logic.reset(self.canvas.remote_snakes)
            self.canvas.update()
        self.timer.start(self.interval_ms)
        self.status_label.setText("进行中…")
        self.btn_start.setEnabled(False)
        # 更新排行榜
        self.update_leaderboard_data()
        self.update_leaderboard_display()
        self.canvas.setFocus()

    def reset(self):
        self.timer.stop()
        # 重置时使用随机位置
        self.logic.reset(self.canvas.remote_snakes)
        self.status_label.setText("就绪")
        self.score_label.setText("分数：0")
        self.btn_start.setEnabled(True)
        # 重置游戏结束界面状态
        self.canvas.game_over_alpha = 0
        self.canvas.game_over_timer.stop()
        # 更新排行榜
        self.update_leaderboard_data()
        self.update_leaderboard_display()
        self.canvas.update()
        self.canvas.setFocus()

    def on_tick(self):
        state = self.logic.step(self.canvas.remote_snakes)
        self.score_label.setText(f"分数：{state['score']}")
        
        # 更新排行榜
        self.update_leaderboard_data()
        self.update_leaderboard_display()
        
        self.canvas.update()
        # 每步通过DDS发送蛇与食物位置
        if self.dds:
            try:
                # 发送第一个食物（为了兼容性）
                first_food = state["foods"][0] if state["foods"] else {"x": 0, "y": 0}
                self.dds.send_state(state["snake"], first_food, state["score"], state["over"])
            except Exception as _:
                pass
        if state["over"]:
            self.timer.stop()
            self.status_label.setText("游戏结束")
            self.btn_start.setEnabled(True)
            # 开始游戏结束界面动画
            self.canvas.start_game_over_animation(state["score"])

    def on_remote_state(self, user: str, user_id: int, payload: dict):
        # 保存远端状态并刷新画布
        print(f"[DDS] 收到远端状态: 用户={user}, ID={user_id}, 蛇长度={len(payload.get('snake', []))}")
        if payload.get("over"):
            # 若对方结束，清理其蛇
            if user_id in self.canvas.remote_snakes:
                del self.canvas.remote_snakes[user_id]
                print(f"[DDS] 清理结束的蛇: {user}")
        else:
            self.canvas.remote_snakes[user_id] = payload
            print(f"[DDS] 添加/更新远端蛇: {user}, 当前远端蛇数量: {len(self.canvas.remote_snakes)}")
        
        # 更新远端玩家数量显示
        self.remote_label.setText(f"其他玩家：{len(self.canvas.remote_snakes)}")
        
        # 更新排行榜数据
        self.update_leaderboard_data()
        self.update_leaderboard_display()
        self.canvas.update()

    def update_leaderboard_data(self):
        """更新排行榜数据"""
        # 添加自己的数据
        self.leaderboard_data[self.user_id] = {
            "username": self.username,
            "score": self.logic.score,
            "is_self": True
        }
        
        # 添加其他玩家的数据
        for user_id, payload in self.canvas.remote_snakes.items():
            if not payload.get("over", False):  # 只显示未结束的玩家
                self.leaderboard_data[user_id] = {
                    "username": payload.get("user", f"玩家{user_id}"),
                    "score": payload.get("score", 0),
                    "is_self": False
                }

    def update_leaderboard_display(self):
        """更新排行榜显示"""
        # 按分数降序排序
        sorted_players = sorted(
            self.leaderboard_data.values(),
            key=lambda x: x["score"],
            reverse=True
        )
        
        # 清空列表
        self.leaderboard_list.clear()
        
        # 添加排序后的玩家
        for i, player in enumerate(sorted_players):
            rank = i + 1
            username = player["username"]
            score = player["score"]
            is_self = player["is_self"]
            
            # 设置显示文本和样式
            if is_self:
                if rank == 1:
                    item_text = f"👑 {rank}. {username} (你) - {score}分"
                    item_color = "#FFD700"  # 金色
                elif rank == 2:
                    item_text = f"🥈 {rank}. {username} (你) - {score}分"
                    item_color = "#C0C0C0"  # 银色
                elif rank == 3:
                    item_text = f"🥉 {rank}. {username} (你) - {score}分"
                    item_color = "#CD7F32"  # 铜色
                else:
                    item_text = f"⭐ {rank}. {username} (你) - {score}分"
                    item_color = "#FFD700"  # 金色
            else:
                if rank == 1:
                    item_text = f"👑 {rank}. {username} - {score}分"
                    item_color = "#FFD700"  # 金色
                elif rank == 2:
                    item_text = f"🥈 {rank}. {username} - {score}分"
                    item_color = "#C0C0C0"  # 银色
                elif rank == 3:
                    item_text = f"🥉 {rank}. {username} - {score}分"
                    item_color = "#CD7F32"  # 铜色
                else:
                    item_text = f"🎯 {rank}. {username} - {score}分"
                    item_color = "#E2E8F0"  # 普通颜色
            
            # 创建列表项
            item = QListWidgetItem(item_text)
            item.setForeground(QColor(item_color))
            self.leaderboard_list.addItem(item)

    def closeEvent(self, event):
        try:
            if self.dds:
                self.dds.cleanup()
        finally:
            super().closeEvent(event)


def main():
    app = QApplication(sys.argv)
    
    # 获取用户输入（使用对话框）
    from username_dialog import get_username_from_dialog
    username, user_id = get_username_from_dialog()
    
    # 如果用户取消了输入，退出程序
    if username is None:
        print("用户取消了登录，程序退出")
        return
    
    w = Snake(username, user_id)
    w.resize(1200, 800)  # 增加窗口大小以适应更大的游戏区域
    w.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()


