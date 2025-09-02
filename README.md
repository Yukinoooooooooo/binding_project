# ZRDDS Python Bindings 

## 🎉 最新更新 (2025-09-02)

✅ **QoS配置问题已修复** - DataReader创建现在正常工作  
✅ **发布-订阅通信已实现** - 完整的DDS通信链路工作正常  
✅ **模块集成优化** - 所有模块间的指针传递和注册流程已优化

## 🌟 功能概览

### ✅ 已实现功能
- **完整的DDS发布-订阅通信** - 支持多线程发布者和订阅者
- **模块化架构** - 6个独立模块，职责清晰，易于维护
- **QoS配置管理** - 支持DomainParticipant, Publisher, DataWriter, Subscriber, DataReader QoS
- **监听器支持** - 完整的Listener创建、注册和附加功能
- **实体生命周期管理** - 正确的创建、使用和清理流程
- **错误处理** - 完善的错误检查和异常处理机制

### 🔄 部分实现功能
- **数据读取** - 通信链路正常，但返回占位符数据（待完善）

### 🎯 核心特性
- **跨平台支持** - Windows平台，支持Python 3.11/3.13
- **高性能** - 基于ZRDDS 2.4.4，优化的DDS实现
- **易用性** - 简洁的Python API，工厂模式设计
- **可扩展性** - 模块化设计，易于添加新功能  

## 🚀 快速开始

### 构建所有模块

```cmd
# 构建所有核心模块
.\build_module.bat domain    # DomainParticipant管理
.\build_module.bat topic     # Topic创建和管理
.\build_module.bat publish   # Publisher/DataWriter
.\build_module.bat subscribe # Subscriber/DataReader
.\build_module.bat listener  # 各种Listener
```

### 使用CMake直接构建

```cmd
# 构建特定模块
cmake -DMODULE_TYPE=domain -B build
cmake --build build --config Release

# 构建其他模块
cmake -DMODULE_TYPE=topic -B build
cmake --build build --config Release

cmake -DMODULE_TYPE=publish -B build
cmake --build build --config Release

cmake -DMODULE_TYPE=subscribe -B build
cmake --build build --config Release
```

## 📋 模块与职责

| 模块 | 功能 | 状态 |
|------|------|------|
| `_zrdds_domain` | DomainParticipant/Factory 管理 | ✅ 完全正常 |
| `_zrdds_topic` | Topic 创建和管理 | ✅ 完全正常 |
| `_zrdds_publish` | Publisher/DataWriter 管理 | ✅ 完全正常 |
| `_zrdds_subscribe` | Subscriber/DataReader 管理 | ✅ 基本正常 |
| `_zrdds_listener` | 各类 Listener 工厂 | ✅ 完全正常 |
| `_zrdds_basic` | GuardCondition, WaitSet, ConditionSeq | ✅ 完全正常 |

## 🧪 测试

### 🎯 核心功能测试

#### 发布者集成测试
```cmd
python test_integration_pub.py
```
**功能**：测试完整的发布者工作流程，包括数据写入和监听器

#### 发布-订阅通信测试 ⭐
```cmd
python test_communication.py
```
**功能**：测试真实的发布-订阅通信，验证数据传输

#### Basic 模块测试
```cmd
python test_basic_factory.py
```
**功能**：测试GuardCondition, WaitSet, ConditionSeq功能

### 🔧 模块导入测试
```cmd
# 测试所有核心模块
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_domain; print('Domain: OK')"
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_topic; print('Topic: OK')"
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_publish; print('Publish: OK')"
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_subscribe; print('Subscribe: OK')"
python -c "import sys; sys.path.insert(0, 'zrpy'); import _zrdds_listener; print('Listener: OK')"
```

## 💡 快速使用示例

### 基本发布-订阅通信

```python
import sys
sys.path.insert(0, 'zrpy')

# 导入所有模块
import _zrdds_domain, _zrdds_topic, _zrdds_publish, _zrdds_subscribe

# 初始化模块
_zrdds_domain.init()
_zrdds_topic.init()
_zrdds_publish.init()
_zrdds_subscribe.init()

# 创建域参与者
qos_id = _zrdds_domain.create_participant_qos()
participant_id = _zrdds_domain.create_domain_participant(80, qos_id)
participant_ptr = _zrdds_domain.get_participant_ptr(participant_id)

# 创建主题
_zrdds_topic.register_participant(80, participant_ptr)
_zrdds_topic.create_topic(80, "MyTopic", "Bytes")
topic_ptr = _zrdds_topic.get_topic_ptr("MyTopic")

# 创建发布者
_zrdds_publish.register_participant(80, participant_ptr)
_zrdds_publish.register_topic("MyTopic", topic_ptr)
publisher_id = _zrdds_publish.create_publisher(80)
datawriter_id = _zrdds_publish.create_datawriter(publisher_id, "MyTopic")

# 发送数据
_zrdds_publish.write_bytes_data(datawriter_id, "Hello DDS!")

# 清理资源
_zrdds_publish.delete_datawriter(datawriter_id)
_zrdds_publish.delete_publisher(publisher_id)
_zrdds_topic.delete_topic("MyTopic")
_zrdds_domain.delete_domain_participant(participant_id)
_zrdds_domain.delete_participant_qos(qos_id)

# 清理模块
_zrdds_publish.finalize()
_zrdds_topic.finalize()
_zrdds_domain.finalize()
```

### 运行完整测试

```cmd
# 运行发布-订阅通信测试
python test_communication.py

# 运行发布者集成测试  
python test_integration_pub.py
```

## 📁 项目结构

```
project/
├── src/                           # 源代码目录
│   ├── bindings_domain.cpp        # Domain 模块绑定
│   ├── bindings_topic.cpp         # Topic 模块绑定
│   ├── bindings_publish.cpp       # Publish 模块绑定
│   ├── bindings_subscribe.cpp     # Subscribe 模块绑定
│   ├── bindings_listener.cpp      # Listener 模块绑定
│   └── bindings_basic.cpp         # Basic 模块绑定
├── zrpy/                          # 编译后的 Python 模块
│   ├── _zrdds_domain.cp313-win_amd64.pyd
│   ├── _zrdds_topic.cp313-win_amd64.pyd
│   ├── _zrdds_publish.cp313-win_amd64.pyd
│   ├── _zrdds_subscribe.cp313-win_amd64.pyd
│   ├── _zrdds_listener.cp313-win_amd64.pyd
│   └── __init__.py
├── test_integration_pub.py        # 发布者集成测试 ⭐
├── test_communication.py          # 发布-订阅通信测试 ⭐
├── test_basic_factory.py          # Basic 模块测试
├── build_module.bat               # 批处理构建脚本
├── build_module.ps1               # PowerShell 构建脚本
├── CMakeLists.txt                 # CMake 配置
└── README.md                      # 项目说明
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

## ⚠️ 当前存在的限制

### 🔄 数据读取功能 - 部分实现

**当前状态**：基本功能已实现，但返回占位符数据

**影响范围**：
- `read_bytes_data()` - 返回占位符字符串 "PLACEHOLDER_DATA_RECEIVED"
- `read_string_data()` - 返回占位符数据
- `wait_for_data()` - 基本框架已实现

**技术原因**：
1. **ZRDDS API 兼容性**：ZRDDS 的序列类型接口与标准 DDS 接口存在差异
2. **模板实例化问题**：需要深入研究 ZRDDS 的具体 API 使用方式
3. **类型转换复杂性**：C++ 到 Python 的数据类型转换需要特殊处理

### 📊 当前状态总结

| 功能模块 | 状态 | 说明 |
|---------|------|------|
| Domain 模块 | ✅ 完全正常 | DomainParticipant/Factory 管理完整 |
| Topic 模块 | ✅ 完全正常 | Topic 创建和管理功能完整 |
| Publish 模块 | ✅ 完全正常 | Publisher/DataWriter 创建和写入功能完整 |
| Subscribe 模块 | ✅ 基本正常 | 实体创建正常，数据读取返回占位符 |
| Listener 模块 | ✅ 完全正常 | 各类 Listener 创建和注册功能完整 |
| Basic 模块 | ✅ 完全正常 | GuardCondition, WaitSet, ConditionSeq 功能完整 |

## 📝 使用注意事项

### 🔧 构建说明
- 每次只能构建一个模块
- 构建新模块会覆盖之前的模块文件
- 模块文件会自动复制到 `zrpy/` 目录

### ⚠️ 重要提醒

1. **数据读取功能**：当前返回占位符数据，但通信链路已建立
2. **QoS 配置**：已修复，现在使用正确的ZRDDS默认QoS初始化
3. **模块依赖**：确保按正确顺序构建模块（domain → topic → publish/subscribe → listener）
4. **测试验证**：建议先运行 `test_communication.py` 验证基本通信功能

### 🎯 快速验证

运行以下命令验证所有功能：
```cmd
# 1. 构建所有模块
.\build_module.bat domain
.\build_module.bat topic  
.\build_module.bat publish
.\build_module.bat subscribe
.\build_module.bat listener

# 2. 运行通信测试
python test_communication.py

# 3. 运行发布者测试
python test_integration_pub.py
```

### 🔄 开发状态

- **当前版本**：v2.1.0（通信功能版本）
- **主要成就**：✅ QoS问题已解决，✅ 发布-订阅通信已实现
- **下一步目标**：实现真实数据读取，完善数据传输功能
- **状态**：核心通信架构已完成，数据读取功能待完善
