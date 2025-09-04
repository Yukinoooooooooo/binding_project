@echo off
echo 启动两个聊天实例进行双向通信测试...
echo.

echo 启动第一个聊天实例 (用户: Alice)...
start "Chat-Alice" cmd /k "python simple_chat.py"

timeout /t 3 /nobreak >nul

echo 启动第二个聊天实例 (用户: Bob)...
start "Chat-Bob" cmd /k "python simple_chat.py"

echo.
echo 两个聊天窗口已启动！
echo 请在两个窗口中分别输入不同的用户名
echo 然后在一个窗口中发送消息，在另一个窗口中查看接收
echo.
pause
