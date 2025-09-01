# ZRDDS Python Bindings (Modular)

## 🚀 快速开始

### 构建模块

```cmd
# 构建 Basic 模块 (GuardCondition, WaitSet, ConditionSeq)
cmake -DMODULE_TYPE=basic -B build
cmake --build build --config Release

# 构建 Topic 模块 (DomainParticipant, Topic - 纯 Topic 功能)
cmake -DMODULE_TYPE=topic -B build
cmake --build build --config Release

# 构建 Domain 模块 (DomainParticipant, DomainParticipantFactory)
cmake -DMODULE_TYPE=domain -B build
cmake --build build --config Release
```

### 使用批处理脚本

```cmd
# 构建 Basic 模块
.\build_module.bat basic

# 构建 Topic 模块
.\build_module.bat topic

# 构建 Domain 模块
.\build_module.bat domain
```

## 📋 模块与职责

- `_zrdds_domain`: DomainParticipant/Factory 管理（创建/删除/指针导出）
- `_zrdds_topic`: 纯 Topic 功能（注册 participant、创建 topic、指针导出）
- `_zrdds_publish`: Publisher/DataWriter 管理、监听器注册与通过 ID 挂载
- `_zrdds_listener`: 各类 Listener 工厂与指针导出

## 🧪 测试

### Basic 模块测试
```cmd
python test_basic_factory.py
```

### 发布链路集成测试
```cmd
python test_integration_pub.py
```

### 其他模块测试
```cmd
# 测试 Domain 模块
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_domain; print('Success!')"

# 测试 WaitSet 模块
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_waitset; print('Success!')"
```

## 📁 项目结构

```
project/
├── src/                    # 源代码目录
│   ├── bindings_basic.cpp   # Basic 模块绑定
│   ├── bindings_topic.cpp  # Topic 模块绑定（纯 Topic）
│   ├── bindings_domain.cpp # Domain 模块绑定
│   └── ...                 # 其他模块绑定
├── include/                # ZRDDS 头文件
├── zrpy/                   # 编译后的 Python 模块
│   ├── _zrdds_basic.cp313-win_amd64.pyd
│   ├── _zrdds_topic.cp313-win_amd64.pyd
│   └── __init__.py
├── build/                  # 构建目录
├── CMakeLists.txt          # CMake 配置
├── build_module.bat        # 批处理构建脚本
├── build_module.ps1        # PowerShell 构建脚本
├── test_basic_factory.py   # Basic 模块测试
├── test_real_functionality.py # Topic 模块测试
├── README.md               # 项目说明
├── README_BUILD.md         # 构建说明
└── README_MODULAR.md       # 模块化架构说明
```

## 🔧 环境要求

- **ZRDDS_HOME** 环境变量指向 ZRDDS 安装目录
- CMake 3.15+
- Visual Studio 2019+
- Python 3.11/3.13（与 .pyd 匹配）
- pybind11

## 🛠️ 故障排除

1. **确保环境变量设置正确**
   - `ZRDDS_HOME` 指向 ZRDDS 安装目录

2. **清理构建**
   ```cmd
   rmdir /s build
   cmake -DMODULE_TYPE=domain -B build
   cmake --build build --config Release
   ```

3. **检查模块导入**
   ```cmd
   python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_domain; print('Success!')"
   ```

## 📝 注意事项

- 每次只能构建一个模块
- 构建新模块会覆盖之前的模块文件
- 模块文件会自动复制到 `zrpy/` 目录
