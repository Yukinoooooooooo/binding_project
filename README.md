## 🚀 快速开始

### 构建所有模块

```cmd
# 构建所有核心模块
.\build_module.bat domain    # DomainParticipant管理
.\build_module.bat topic     # Topic创建和管理
.\build_module.bat publish   # Publisher/DataWriter
.\build_module.bat subscribe # Subscriber/DataReader
.\build_module.bat listener  # 各种Listener
.\build_module.bat basic     # GuardCondition, WaitSet, ConditionSeq
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

cmake -DMODULE_TYPE=basic -B build
cmake --build build --config Release
```

# ZRDDS Python Binding 架构修复

### 📁 模块分工

```
_zrdds_domain     - 域参与者、工厂、基础 QoS
├── DomainParticipant
├── DomainParticipantFactory  
├── DomainParticipantQos
├── PublisherQos
├── SubscriberQos
├── TopicQos
└── Duration_t, InstanceHandle_t 等基础类型

_zrdds_publish    - 发布相关
├── Publisher
├── DataWriter
├── DataWriterQos ✅ (已有)
└── 发布相关的监听器和状态

_zrdds_subscribe  - 订阅相关  
├── Subscriber
├── DataReader
├── DataReaderQos ✅ (已修复)
└── 订阅相关的监听器和状态

_zrdds_topic      - 主题相关
├── Topic
├── TopicQos
└── 主题描述相关

_zrdds_shapetype  - 数据类型
├── ShapeType
├── ShapeTypeTypeSupport
└── 数据类型相关
```

## 🔧 修复内容

### 1. `_zrdds_subscribe` 模块修复

**问题**: 缺少 `DataReaderQos` 类绑定，且 `get_default_datareader_qos` 方法签名不一致

**修复**:
```cpp
// 添加 DataReaderQos 类绑定
py::class_<DDS::DataReaderQos>(m, "DataReaderQos")
    .def(py::init<>())
    .def("__repr__", [](const DDS::DataReaderQos& self) {
        return "<DDS.DataReaderQos>";
    });

// 修复 get_default_datareader_qos 方法，使其与 _zrdds_publish 一致
.def("get_default_datareader_qos", [](DDS::Subscriber& self) -> py::tuple {
    DDS::DataReaderQos qos;
    DDS::ReturnCode_t ret = self.get_default_datareader_qos(qos);
    return py::make_tuple(ret, qos);
}, "Get default DataReader QoS")
```

## 🎯 使用示例

```python
import _zrdds_domain
import _zrdds_publish  
import _zrdds_subscribe

# 创建域参与者
participant = factory.create_participant(domain_id, qos, None, 0)

# 创建发布者
publisher = participant.create_publisher(publisher_qos, None, 0)

# 获取 DataWriter QoS (从 Publisher 获取)
ret, datawriter_qos = publisher.get_default_datawriter_qos()

# 创建数据写者
datawriter = publisher.create_datawriter(topic, datawriter_qos, None, 0)

# 创建订阅者  
subscriber = participant.create_subscriber(subscriber_qos, None, 0)

# 获取 DataReader QoS (从 Subscriber 获取)
ret, datareader_qos = subscriber.get_default_datareader_qos()

# 创建数据读者
datareader = subscriber.create_datareader(topic, datareader_qos, None, 0)
```

## 🚀 下一步

1. **重新编译**:
   ```bash
   cd build
   cmake --build . --config Release
   ```

2. **测试运行**:
   ```bash
   python shape_publisher.py
   python shape_subscriber.py
   ```

## 💬 聊天应用

### 实时双向聊天
基于 DDS 监听器模式实现的实时聊天应用：

```bash
# 启动两个聊天实例
python simple_chat.py  # 终端1，输入用户名
python simple_chat.py  # 终端2，输入用户名
```

### 相关文档
- [聊天实现总结](CHAT_IMPLEMENTATION_SUMMARY.md) - 完整的技术实现总结
- [聊天使用指南](CHAT_README.md) - 详细的使用说明

