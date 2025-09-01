#!/usr/bin/env pwsh
# ZRDDS Python Bindings Build Script (PowerShell)

param(
    [Parameter(Position=0)]
    [ValidateSet("basic", "topic", "domain", "waitset", "subscribe", "publish", "listener", "main")]
    [string]$ModuleType = "basic",
    
    [Parameter()]
    [ValidateSet("Release", "Debug")]
    [string]$Config = "Release",
    
    [Parameter()]
    [switch]$Clean,
    
    [Parameter()]
    [switch]$Help
)

# 显示帮助信息
if ($Help) {
    Write-Host "ZRDDS Python Bindings Build Script" -ForegroundColor Cyan
    Write-Host "===================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage: .\build_module.ps1 [ModuleType] [Options]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Module Types:" -ForegroundColor Green
    Write-Host "  basic     - ZRDDS Basic Module (_zrdds_basic)" -ForegroundColor White
    Write-Host "  topic     - ZRDDS Topic Module (zrdds_python)" -ForegroundColor White
    Write-Host "  domain    - ZRDDS Domain Module (_zrdds_domain)" -ForegroundColor White
    Write-Host "  waitset   - ZRDDS WaitSet Module (_zrdds_waitset)" -ForegroundColor White
    Write-Host "  subscribe - ZRDDS Subscribe Module (_zrdds_subscribe)" -ForegroundColor White
    Write-Host "  publish   - ZRDDS Publish Module (_zrdds_publish)" -ForegroundColor White
    Write-Host "  listener  - ZRDDS Listener Module (_zrdds_listener)" -ForegroundColor White
    Write-Host "  main      - ZRDDS Main Module (zrdds_python)" -ForegroundColor White
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Green
    Write-Host "  -Config Release|Debug  - Build configuration (default: Release)" -ForegroundColor White
    Write-Host "  -Clean                 - Clean build directory before building" -ForegroundColor White
    Write-Host "  -Help                  - Show this help message" -ForegroundColor White
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Green
    Write-Host "  .\build_module.ps1 basic" -ForegroundColor White
    Write-Host "  .\build_module.ps1 topic -Config Debug" -ForegroundColor White
    Write-Host "  .\build_module.ps1 domain -Clean" -ForegroundColor White
    Write-Host ""
    exit 0
}

# 模块信息映射
$ModuleInfo = @{
    "basic" = @{
        Name = "_zrdds_basic"
        Description = "ZRDDS Basic Module (GuardCondition, WaitSet, ConditionSeq)"
        TestCommand = "python test_basic_factory.py"
    }
    "topic" = @{
        Name = "_zrdds_topic"
        Description = "ZRDDS Topic Module (DomainParticipant, Topic, DataWriter, DataReader)"
        TestCommand = "python test_real_functionality.py"
    }
    "domain" = @{
        Name = "_zrdds_domain"
        Description = "ZRDDS Domain Module (DomainParticipant, DomainParticipantFactory)"
        TestCommand = "python test_domain_module.py"
    }
    "waitset" = @{
        Name = "_zrdds_waitset"
        Description = "ZRDDS WaitSet Module (WaitSet, Condition)"
        TestCommand = "python -c `"import sys; sys.path.insert(0, 'zrpy'); import _zrdds_waitset; print('Success!')`""
    }
    "subscribe" = @{
        Name = "_zrdds_subscribe"
        Description = "ZRDDS Subscribe Module (DataReader, Subscriber, ReadCondition)"
        TestCommand = "python test_subscribe_module.py"
    }
    "publish" = @{
        Name = "_zrdds_publish"
        Description = "ZRDDS Publish Module (DataWriter, Publisher)"
        TestCommand = "python test_publish_module.py"
    }
    "listener" = @{
        Name = "_zrdds_listener"
        Description = "ZRDDS Listener Module (Listeners)"
        TestCommand = "python test_listener_module.py"
    }
    "main" = @{
        Name = "zrdds_python"
        Description = "ZRDDS Main Module (Main functionality)"
        TestCommand = "python -c `"import sys; sys.path.insert(0, 'zrpy'); import zrdds_python; print('Success!')`""
    }
}

# 获取模块信息
$ModuleName = $ModuleInfo[$ModuleType].Name
$ModuleDescription = $ModuleInfo[$ModuleType].Description
$TestCommand = $ModuleInfo[$ModuleType].TestCommand

Write-Host "Building $ModuleType module..." -ForegroundColor Cyan
Write-Host "Module: $ModuleName" -ForegroundColor Yellow
Write-Host "Description: $ModuleDescription" -ForegroundColor Yellow
Write-Host "Configuration: $Config" -ForegroundColor Yellow
Write-Host ""

# 清理构建目录
if ($Clean) {
    Write-Host "Cleaning build directory..." -ForegroundColor Yellow
    if (Test-Path "build") {
        Remove-Item -Recurse -Force "build"
    }
}

# 创建构建目录
if (-not (Test-Path "build")) {
    Write-Host "Creating build directory..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# 配置 CMake
Write-Host "Configuring CMake for $ModuleType module..." -ForegroundColor Yellow
$cmakeResult = cmake -DMODULE_TYPE=$ModuleType -B build
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: CMake configuration failed" -ForegroundColor Red
    exit 1
}

# 编译
Write-Host ""
Write-Host "Building $ModuleType module..." -ForegroundColor Yellow
$buildResult = cmake --build build --config $Config
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error: Build failed" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host "Module files copied to zrpy/ directory." -ForegroundColor Green

# 显示测试信息
Write-Host ""
Write-Host "Module Information:" -ForegroundColor Cyan
Write-Host "  Name: $ModuleName" -ForegroundColor White
Write-Host "  Description: $ModuleDescription" -ForegroundColor White
Write-Host "  Test Command: $TestCommand" -ForegroundColor White

Write-Host ""
Write-Host "Done!" -ForegroundColor Green
