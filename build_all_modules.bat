@echo off
echo Building all ZRDDS modules...
echo ================================

set MODULES=basic domain topic publish subscribe listener

for %%m in (%MODULES%) do (
    echo.
    echo Building %%m module...
    echo --------------------------------
    
    if not exist build mkdir build
    cd build
    
    cmake -DMODULE_TYPE=%%m ..
    if %errorlevel% neq 0 (
        echo Failed to configure %%m module
        cd ..
        pause
        exit /b 1
    )
    
    cmake --build . --config Release
    if %errorlevel% neq 0 (
        echo Failed to build %%m module
        cd ..
        pause
        exit /b 1
    )
    
    cd ..
    echo %%m module built successfully
)

echo.
echo All modules built successfully!
echo ================================
echo.
echo Available modules:
echo - _zrdds_basic.cp313-win_amd64.pyd
echo - _zrdds_domain.cp313-win_amd64.pyd
echo - _zrdds_topic.cp313-win_amd64.pyd
echo - _zrdds_publish.cp313-win_amd64.pyd
echo - _zrdds_subscribe.cp313-win_amd64.pyd
echo - _zrdds_listener.cp313-win_amd64.pyd
echo.
echo You can now run: python test_refactored_modules.py
echo.
pause
