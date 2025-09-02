# ZRDDS Python Bindings - 重构后模块架构

## 概述

本项目已经重构为模块分离架构，每个模块只负责自己的功能，实现了真正的模块化设计。

## 模块架构

### 1. 域模块 (`_zrdds_domain`)
- **功能**: 管理域参与者 (DomainParticipant)
- **主要函数**:
  - `create_domain_participant(domain_id)` - 创建域参与者
  - `get_participant()` - 获取域参与者对象
  - `get_participant_domain_id()` - 获取域ID
  - `participant_exists()` - 检查域参与者是否存在

### 2. 主题模块 (`_zrdds_topic`)
- **功能**: 管理主题 (Topic)
- **主要函数**:
  - `create_topic(participant, topic_name, type_name)` - 创建主题
  - `get_topic()` - 获取主题对象
  - `get_topic_name()` - 获取主题名称
  - `get_topic_type_name()` - 获取主题类型

### 3. 发布模块 (`_zrdds_publish`)
- **功能**: 管理发布者和数据写入器
- **主要函数**:
  - `create_publisher(participant)` - 创建发布者
  - `create_datawriter(topic)` - 创建数据写入器
  - `write_bytes_data(data)` - 写入字节数据
  - `write_string_data(data)` - 写入字符串数据

### 4. 订阅模块 (`_zrdds_subscribe`)
- **功能**: 管理订阅者和数据读取器
- **主要函数**:
  - `create_subscriber(participant)` - 创建订阅者
  - `create_datareader(topic)` - 创建数据读取器
  - `read_bytes_data()` - 读取字节数据
  - `read_string_data()` - 读取字符串数据

### 5. 监听器模块 (`_zrdds_listener`)
- **功能**: 管理各种监听器
- **主要函数**:
  - `create_datareader_listener()` - 创建数据读取器监听器
  - `create_datawriter_listener()` - 创建数据写入器监听器
  - `create_participant_listener()` - 创建域参与者监听器

### 6. 基础模块 (`_zrdds_basic`)
- **功能**: 管理基础DDS功能
- **主要函数**:
  - `create_guard_condition()` - 创建GuardCondition
  - `create_waitset()` - 创建WaitSet
  - `attach_condition()` - 附加条件
  - `wait_for_conditions()` - 等待条件

## 使用方法

### 1. 构建所有模块

```bash
# 使用批处理脚本构建所有模块
build_all_modules.bat

# 或者手动构建单个模块
cmake -DMODULE_TYPE=domain ..
cmake --build build --config Release
```

### 2. 基本使用示例

```python
import _zrdds_domain as domain
import _zrdds_topic as topic
import _zrdds_publish as publish
import _zrdds_subscribe as subscribe

# 1. 创建域参与者
domain.init()
domain.create_domain_participant(80)
participant = domain.get_participant()

# 2. 创建主题
topic.init()
topic.create_topic(participant, "MyTopic", "Bytes")
topic_obj = topic.get_topic()

# 3. 创建发布者
publish.init()
publish.create_publisher(participant)
publish.create_datawriter(topic_obj)

# 4. 创建订阅者
subscribe.init()
subscribe.create_subscriber(participant)
subscribe.create_datareader(topic_obj)

# 5. 发布数据
publish.write_bytes_data("Hello World!")

# 6. 读取数据
import time
time.sleep(1)  # 等待数据传播
data = subscribe.read_bytes_data()
print(f"Received: {data}")
```

### 3. 运行测试

```bash
python test_refactored_modules.py
```

## 模块依赖关系

```
domain (域参与者)
  ↓
topic (主题) ← 需要 domain 的 participant
  ↓
publish (发布) ← 需要 domain 的 participant 和 topic 的 topic
  ↓
subscribe (订阅) ← 需要 domain 的 participant 和 topic 的 topic
  ↓
listener (监听器) ← 可独立使用
  ↓
basic (基础功能) ← 可独立使用
```

## 构建系统

### 支持的模块类型
- `basic` - 基础模块
- `domain` - 域模块
- `topic` - 主题模块
- `publish` - 发布模块
- `subscribe` - 订阅模块
- `listener` - 监听器模块

### 构建命令
```bash
# 构建特定模块
cmake -DMODULE_TYPE=domain ..
cmake --build build --config Release

# 构建所有模块
build_all_modules.bat
```

## 文件结构

```
project/
├── src/
│   ├── bindings_basic.cpp      # 基础模块
│   ├── bindings_domain.cpp     # 域模块
│   ├── bindings_topic.cpp      # 主题模块
│   ├── bindings_publish.cpp    # 发布模块
│   ├── bindings_subscribe.cpp  # 订阅模块
│   └── bindings_listener.cpp   # 监听器模块
├── build_all_modules.bat       # 构建脚本
├── test_refactored_modules.py  # 测试脚本
├── CMakeLists.txt              # 构建配置
└── README_REFACTORED.md        # 本文档
```

## 优势

1. **模块分离**: 每个模块只负责自己的功能
2. **依赖清晰**: 模块间的依赖关系明确
3. **易于维护**: 修改一个模块不影响其他模块
4. **可扩展性**: 可以轻松添加新模块
5. **测试友好**: 每个模块可以独立测试

## 注意事项

1. 使用模块时，必须按照依赖关系顺序创建实体
2. 域参与者必须在其他模块之前创建
3. 主题必须在发布者和订阅者之前创建
4. 每个模块都有独立的初始化和清理函数
5. 对象在模块间传递时使用Python对象引用

## 故障排除

如果遇到问题，请检查：
1. 模块是否正确构建
2. 依赖关系是否正确
3. 对象是否在正确的模块中创建
4. 是否按照正确的顺序调用函数
