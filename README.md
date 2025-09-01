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

## ⚠️ 当前存在的问题

### 🚫 数据读取功能受限

**问题描述**：Subscribe 模块的数据读取功能暂时被禁用，无法进行实际的数据交互读取。

**影响范围**：
- `read_bytes_data()` - 返回 None
- `read_string_data()` - 返回 None  
- `wait_for_data()` - 总是返回 False

**根本原因**：
1. **模板兼容性问题**：`ZRDDSDataReader` 模板期望序列类型有 C++ 风格的成员函数（如 `length()`, `maximum()`, `has_ownership()`），但 ZRDDS 的序列类型只有 C 风格的函数接口
2. **序列类型接口不匹配**：ZRDDS 使用 `DDS_SEQUENCE_CPP` 宏生成的序列类型缺少必要的 C++ 成员函数

### 🔧 QoS 配置问题

**问题描述**：DataReader 创建时出现 QoS 验证错误。

**错误信息**：
```
DataReaderQos.deadline.period(0 0) invalid, request greater than 0
DataReaderQos.liveliness.lease_duration(0 0) invalid, request greater than 0
DataReaderQos.reliability.kind invalid
DataReaderQos.history.depth(0) invalid request greater than zero
DataReaderQos.resource_limits(0 0 0 0) invalid request greater than zero
```

**影响**：DataReader 创建失败，无法建立数据订阅。

### 📊 当前状态总结

| 功能模块 | 状态 | 说明 |
|---------|------|------|
| Basic 模块 | ✅ 正常 | GuardCondition, WaitSet, ConditionSeq 功能完整 |
| Topic 模块 | ✅ 正常 | DomainParticipant, Topic 创建和管理正常 |
| Domain 模块 | ✅ 正常 | DomainParticipantFactory 功能正常 |
| Publish 模块 | ✅ 正常 | Publisher, DataWriter 创建和写入功能正常 |
| Subscribe 模块 | ⚠️ 部分正常 | 实体创建正常，但数据读取功能被禁用 |
| Listener 模块 | ✅ 正常 | 各类 Listener 创建和注册正常 |

### 🎯 解决方案优先级

#### 高优先级（影响核心功能）
1. **修复 QoS 配置问题**：确保 DataReader 能正常创建
2. **解决模板兼容性问题**：恢复数据读取功能

#### 中优先级（功能增强）
1. **创建序列类型包装器**：为 ZRDDS 序列类型添加 C++ 风格接口
2. **使用底层 C 接口**：绕过有问题的 C++ 模板

#### 低优先级（长期优化）
1. **联系 ZRDDS 技术支持**：了解正确的使用方法和最佳实践
2. **考虑替代方案**：评估其他 DDS 实现的兼容性

### 🔍 技术细节

**问题代码位置**：
- `src/bindings_subscribe.cpp` 第 440-470 行
- `src/bindings_subscribe.cpp` 第 475-495 行  
- `src/bindings_subscribe.cpp` 第 500-530 行

**临时解决方案**：
```cpp
// 暂时禁用的代码示例
// TODO: Fix ZRDDSDataReader template compatibility
return py::none();
```

**需要的修复**：
1. 为 `DDS_StringSeq` 和 `DDS_BytesSeq` 添加 C++ 风格接口
2. 修复 `ZRDDSDataReader` 模板的序列类型兼容性
3. 正确配置 DataReader QoS 参数

## 📝 注意事项

- 每次只能构建一个模块
- 构建新模块会覆盖之前的模块文件
- 模块文件会自动复制到 `zrpy/` 目录

### ⚠️ 重要提醒

1. **数据读取功能限制**：当前 Subscribe 模块无法进行实际数据读取，仅支持实体创建和管理
2. **QoS 配置要求**：创建 DataReader 时需要正确配置 QoS 参数，避免验证错误
3. **模板兼容性**：ZRDDS 的 C++ 模板与标准 DDS 接口存在兼容性问题
4. **测试验证**：建议先测试基本功能，数据交互功能需要等待问题修复

### 🔄 开发状态

- **当前版本**：v2.0.0（功能受限版本）
- **目标版本**：v2.1.0（完整功能版本）
- **主要里程碑**：解决数据读取和 QoS 配置问题
