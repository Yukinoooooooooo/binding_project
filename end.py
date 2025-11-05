from PySide6.QtGui import QColor, QBrush, QPen, QFont
from PySide6.QtCore import Qt

def draw_game_over_screen(self, painter):
    """绘制游戏结束界面"""
    # 半透明黑色背景
    overlay_color = QColor(0, 0, 0, self.game_over_alpha)
    painter.fillRect(self.rect(), overlay_color)
    
    if self.game_over_alpha < 50:  # 透明度太低时不绘制内容
        return
    
    # 计算中心位置
    center_x = self.width() // 2
    center_y = self.height() // 2
    
    # 游戏结束面板背景
    panel_width = min(450, self.width() - 40)
    panel_height = min(350, self.height() - 40)
    panel_x = center_x - panel_width // 2
    panel_y = center_y - panel_height // 2
    
    # 绘制面板背景（带圆角和阴影效果）
    panel_color = QColor(45, 55, 72, min(240, self.game_over_alpha + 40))
    painter.setBrush(QBrush(panel_color))
    painter.setPen(QPen(QColor(66, 153, 225, min(200, self.game_over_alpha)), 3))
    painter.drawRoundedRect(panel_x, panel_y, panel_width, panel_height, 20, 20)
    
    # 绘制标题
    painter.setPen(QPen(QColor(255, 107, 107, self.game_over_alpha), 3))
    painter.setFont(QFont("Microsoft YaHei", 28, QFont.Bold))
    title_text = "💀 游戏结束"
    title_rect = painter.fontMetrics().boundingRect(title_text)
    title_x = center_x - title_rect.width() // 2
    title_y = panel_y + 60
    painter.drawText(title_x, title_y, title_text)
    
    # 绘制分数区域
    score_bg_x = panel_x + 20
    score_bg_y = panel_y + 100
    score_bg_width = panel_width - 40
    score_bg_height = 80
    
    # 分数背景
    score_bg_color = QColor(66, 153, 225, min(100, self.game_over_alpha // 3))
    painter.setBrush(QBrush(score_bg_color))
    painter.setPen(QPen(QColor(66, 153, 225, min(150, self.game_over_alpha)), 2))
    painter.drawRoundedRect(score_bg_x, score_bg_y, score_bg_width, score_bg_height, 10, 10)
    
    # 绘制分数
    painter.setPen(QPen(QColor(255, 255, 255, self.game_over_alpha), 2))
    painter.setFont(QFont("Microsoft YaHei", 20, QFont.Bold))
    score_text = f"🏆 最终分数: {self.final_score}"
    score_rect = painter.fontMetrics().boundingRect(score_text)
    score_x = center_x - score_rect.width() // 2
    score_y = panel_y + 130
    painter.drawText(score_x, score_y, score_text)
    
    # 绘制等级评价
    level_text = get_score_level(self.final_score)
    painter.setPen(QPen(QColor(255, 215, 0, self.game_over_alpha), 2))
    painter.setFont(QFont("Microsoft YaHei", 14, QFont.Bold))
    level_rect = painter.fontMetrics().boundingRect(level_text)
    level_x = center_x - level_rect.width() // 2
    level_y = panel_y + 160
    painter.drawText(level_x, level_y, level_text)

    # 绘制装饰性元素
    draw_game_over_decorations(self, painter, panel_x, panel_y, panel_width, panel_height)

def get_score_level(score):
    """根据分数返回等级评价"""
    if score >= 500:
        return "🌟 传奇大师！"
    elif score >= 300:
        return "🏅 高手！"
    elif score >= 200:
        return "🥉 不错！"
    elif score >= 100:
        return "👍 还可以"
    elif score >= 50:
        return "😊 继续努力"
    else:
        return "😅 加油！"

def draw_game_over_decorations(self, painter, panel_x, panel_y, panel_width, panel_height):
    """绘制游戏结束界面的装饰元素"""
    # 绘制一些装饰性的小蛇图案
    decoration_color = QColor(66, 153, 225, min(100, self.game_over_alpha // 2))
    painter.setBrush(QBrush(decoration_color))
    painter.setPen(Qt.NoPen)
    
    # 在面板四角绘制小装饰
    corner_size = 20
    corners = [
        (panel_x + 10, panel_y + 10),
        (panel_x + panel_width - corner_size - 10, panel_y + 10),
        (panel_x + 10, panel_y + panel_height - corner_size - 10),
        (panel_x + panel_width - corner_size - 10, panel_y + panel_height - corner_size - 10)
    ]
    
    for x, y in corners:
        painter.drawEllipse(x, y, corner_size, corner_size)
    
    # 绘制一些动态的装饰线条
    line_color = QColor(255, 107, 107, min(80, self.game_over_alpha // 3))
    painter.setPen(QPen(line_color, 2))
    
    # 在面板周围绘制装饰线条
    margin = 15
    painter.drawLine(panel_x + margin, panel_y + margin, panel_x + panel_width - margin, panel_y + margin)
    painter.drawLine(panel_x + margin, panel_y + panel_height - margin, panel_x + panel_width - margin, panel_y + panel_height - margin)
    painter.drawLine(panel_x + margin, panel_y + margin, panel_x + margin, panel_y + panel_height - margin)
    painter.drawLine(panel_x + panel_width - margin, panel_y + margin, panel_x + panel_width - margin, panel_y + panel_height - margin)
    
    # 绘制一些星星装饰
    star_color = QColor(255, 215, 0, min(120, self.game_over_alpha // 2))
    painter.setPen(QPen(star_color, 1))
    painter.setFont(QFont("Microsoft YaHei", 16))
    
    # 在面板周围绘制星星
    stars = [
        (panel_x + 30, panel_y + 30),
        (panel_x + panel_width - 30, panel_y + 30),
        (panel_x + 30, panel_y + panel_height - 30),
        (panel_x + panel_width - 30, panel_y + panel_height - 30),
        (panel_x + panel_width // 2, panel_y + 20),
        (panel_x + panel_width // 2, panel_y + panel_height - 20)
    ]
    
    for x, y in stars:
        painter.drawText(x - 8, y + 8, "✨")