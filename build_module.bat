@echo off
setlocal enabledelayedexpansion

echo ZRDDS Python Bindings Build Script
echo ===================================

:: 检查参数
if "%~1"=="" (
    echo Usage: build_module.bat [module_type]
    echo.
    echo Available module types:
    echo   basic     - ZRDDS Basic Module (_zrdds_basic)
    echo   topic     - ZRDDS Topic Module (_zrdds_topic)
    echo   domain    - ZRDDS Domain Module (_zrdds_domain)
    echo   waitset   - ZRDDS WaitSet Module (_zrdds_waitset)
    echo   subscribe - ZRDDS Subscribe Module (_zrdds_subscribe)
    echo   publish   - ZRDDS Publish Module (_zrdds_publish)
    echo   listener  - ZRDDS Listener Module (_zrdds_listener)
    echo   main      - ZRDDS Main Module (zrdds_python)
    echo.
    echo Examples:
    echo   build_module.bat basic
    echo   build_module.bat topic
    echo   build_module.bat domain
    echo.
    exit /b 1
)

set MODULE_TYPE=%~1

echo Building %MODULE_TYPE% module...
echo.

:: 创建 build 目录（如果不存在）
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

:: 配置 CMake
echo Configuring CMake for %MODULE_TYPE% module...
cmake -DMODULE_TYPE=%MODULE_TYPE% -B build

if %ERRORLEVEL% neq 0 (
    echo Error: CMake configuration failed
    exit /b 1
)

:: 编译
echo.
echo Building %MODULE_TYPE% module...
cmake --build build --config Release

if %ERRORLEVEL% neq 0 (
    echo Error: Build failed
    exit /b 1
)

echo.
echo Build completed successfully!
echo Module files copied to zrpy/ directory.

:: 显示模块信息
if "%MODULE_TYPE%"=="basic" (
    echo Module name: _zrdds_basic
    echo Test with: python test_basic_factory.py
) else if "%MODULE_TYPE%"=="topic" (
    echo Module name: zrdds_python
    echo Test with: python test_real_functionality.py
) else if "%MODULE_TYPE%"=="domain" (
    echo Module name: _zrdds_domain
    echo Test with: python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_domain; print('Success!')"
) else if "%MODULE_TYPE%"=="waitset" (
    echo Module name: _zrdds_waitset
    echo Test with: python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_waitset; print('Success!')"
) else if "%MODULE_TYPE%"=="subscribe" (
    echo Module name: _zrdds_subscribe
    echo Test with: python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_subscribe; print('Success!')"
) else if "%MODULE_TYPE%"=="publish" (
    echo Module name: _zrdds_publish
    echo Test with: python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_publish; print('Success!')"
) else if "%MODULE_TYPE%"=="listener" (
    echo Module name: _zrdds_listener
    echo Test with: python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_listener; print('Success!')"
) else if "%MODULE_TYPE%"=="main" (
    echo Module name: zrdds_python
    echo Test with: python -c "import sys; sys.path.insert(0, 'zrpy'); import zrdds_python; print('Success!')"
)

echo.
echo Done!
