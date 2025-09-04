# ZRDDS Python API 开发文档

## 📋 目录
- [概述](#概述)
- [架构设计](#架构设计)
- [模块详解](#模块详解)
- [快速开始](#快速开始)
- [API 参考](#api-参考)
- [使用示例](#使用示例)
- [最佳实践](#最佳实践)
- [故障排除](#故障排除)

## 概述

ZRDDS Python API 是基于 pybind11 的 DDS (Data Distribution Service) Python 绑定库，提供了完整的 DDS 功能接口。该 API 将复杂的 C++ DDS 实现封装为易于使用的 Python 模块，支持分布式数据通信。

### 主要特性
- 🚀 **模块化设计**: 按功能划分为 7 个独立模块
- 🔧 **完整 DDS 支持**: 支持发布/订阅、QoS 配置、监听器等
- 🐍 **Python 友好**: 原生 Python 类型支持，异常处理
- 📦 **类型安全**: 强类型绑定，减少运行时错误
- 🎯 **高性能**: 基于 C++ 实现，性能接近原生 DDS

## 架构设计

### 模块化架构

```
ZRDDS Python API
├── _zrdds_basic      # 基础类型和工具类
├── _zrdds_domain     # 域管理和 QoS 配置
├── _zrdds_topic      # 主题管理
├── _zrdds_publish    # 发布功能
├── _zrdds_subscribe  # 订阅功能
├── _zrdds_listener   # 事件监听器
└── _zrdds_shapetype  # 数据类型定义
```

### 设计原则

1. **单一职责**: 每个模块负责特定的 DDS 功能
2. **依赖最小化**: 模块间依赖关系清晰，避免循环依赖
3. **Python 风格**: 遵循 Python 编程习惯和命名规范
4. **错误处理**: 统一的错误码和异常处理机制

## 模块详解

### 1. _zrdds_basic - 基础模块

**功能**: 提供 DDS 基础类型、状态常量和工具类

**主要类**:
- `Entity`: DDS 实体基类
- `DomainEntity`: 域实体基类
- `Condition`: 条件基类
- `StatusCondition`: 状态条件
- `GuardCondition`: 守护条件
- `WaitSet`: 等待集合

**常量**:
```python
RETCODE_OK = 0                    # 操作成功
RETCODE_ERROR = 1                 # 一般错误
RETCODE_BAD_PARAMETER = 2         # 参数错误
RETCODE_PRECONDITION_NOT_MET = 3  # 前置条件不满足
RETCODE_TIMEOUT = 4               # 超时
RETCODE_NO_DATA = 5               # 无数据
RETCODE_ALREADY_DELETED = 6       # 已删除
RETCODE_NOT_ENABLED = 7           # 未启用
RETCODE_IMMUTABLE_POLICY = 8      # 策略不可变
RETCODE_INCONSISTENT = 9          # 策略不一致
RETCODE_OUT_OF_RESOURCES = 10     # 资源不足
RETCODE_UNSUPPORTED = 11          # 不支持的操作
```

**注意**: 这些常量定义在 `_zrdds_basic` 模块中，可以通过以下方式访问：
```python
import _zrdds_basic

# 方式1: 直接访问模块属性
if ret == _zrdds_basic.RETCODE_OK:
    print("操作成功")

# 方式2: 通过枚举访问
if ret == _zrdds_basic.ReturnCode.RETCODE_OK:
    print("操作成功")
```

### 2. _zrdds_domain - 域管理模块

**功能**: 管理 DDS 域、参与者和 QoS 配置

**主要类**:
- `DomainParticipantFactory`: 域参与者工厂
- `DomainParticipant`: 域参与者
- `DomainParticipantQos`: 域参与者 QoS
- `PublisherQos`: 发布者 QoS
- `SubscriberQos`: 订阅者 QoS
- `TopicQos`: 主题 QoS
- `DataWriterQos`: 数据写者 QoS
- `DataReaderQos`: 数据读者 QoS

**核心方法**:
```python
# 获取工厂实例
factory = _zrdds_domain.TheParticipantFactory

# 创建域参与者
participant = factory.create_participant(domain_id, qos, listener, mask)

# 获取默认 QoS
qos = _zrdds_domain.DomainParticipantQos()
ret = factory.get_default_participant_qos(qos)
```

### 3. _zrdds_topic - 主题模块

**功能**: 管理 DDS 主题和类型支持

**主要类**:
- `TopicDescription`: 主题描述基类
- `Topic`: 主题
- `ContentFilteredTopic`: 内容过滤主题
- `MultiTopic`: 多主题
- `TypeSupport`: 类型支持

**核心方法**:
```python
# 创建主题
topic = participant.create_topic(
    topic_name,           # 主题名称
    type_name,           # 类型名称
    topic_qos,           # 主题 QoS
    listener,            # 监听器
    mask                 # 状态掩码
)

# 获取主题信息
type_name = topic.get_type_name()
topic_name = topic.get_name()
```

### 4. _zrdds_publish - 发布模块

**功能**: 提供数据发布功能

**主要类**:
- `Publisher`: 发布者
- `DataWriter`: 数据写者

**核心方法**:
```python
# 创建发布者
publisher = participant.create_publisher(publisher_qos, listener, mask)

# 创建数据写者
ret, datawriter_qos = publisher.get_default_datawriter_qos()
datawriter = publisher.create_datawriter(topic, datawriter_qos, listener, mask)

# 发布数据
ret = datawriter.write(data, handle)
```

### 5. _zrdds_subscribe - 订阅模块

**功能**: 提供数据订阅功能

**主要类**:
- `Subscriber`: 订阅者
- `DataReader`: 数据读者
- `ReadCondition`: 读取条件

**核心方法**:
```python
# 创建订阅者
subscriber = participant.create_subscriber(subscriber_qos, listener, mask)

# 创建数据读者
ret, datareader_qos = subscriber.get_default_datareader_qos()
datareader = subscriber.create_datareader(topic, datareader_qos, listener, mask)

# 读取数据
data = ShapeType()
sample_info = SampleInfo()
ret = datareader.read_next_sample(data, sample_info)
```

### 6. _zrdds_listener - 监听器模块

**功能**: 提供事件监听和回调机制

**主要类**:
- `Listener`: 监听器基类
- `DataReaderListener`: 数据读者监听器
- `DataWriterListener`: 数据写者监听器
- `DomainParticipantListener`: 域参与者监听器
- `PublisherListener`: 发布者监听器
- `SubscriberListener`: 订阅者监听器
- `TopicListener`: 主题监听器

**监听器方法**:
```python
class MyDataReaderListener(_zrdds_listener.DataReaderListener):
    def on_data_available(self, reader):
        # 处理数据可用事件
        pass
    
    def on_subscription_matched(self, reader, status):
        # 处理订阅匹配事件
        pass
```

### 7. _zrdds_shapetype - 数据类型模块

**功能**: 提供示例数据类型定义

**主要类**:
- `ShapeType`: 形状类型数据
- `ShapeTypeTypeSupport`: 形状类型支持
- `SampleInfo`: 样本信息

**数据结构**:
```python
class ShapeType:
    def __init__(self):
        self.x = 0      # X 坐标
        self.y = 0      # Y 坐标
        self.z = ""     # 描述信息
```

## 快速开始

### 环境准备

1. **安装依赖**:
```bash
pip install pybind11
```

2. **设置环境变量**:
```bash
set ZRDDS_HOME=C:\path\to\zrdds
```

3. **编译模块**:
```bash
# 编译所有模块
.\build_module.bat domain
.\build_module.bat topic
.\build_module.bat publish
.\build_module.bat subscribe
.\build_module.bat listener
.\build_module.bat basic
.\build_module.bat shapetype
```

### 基本使用流程

#### 1. 发布者示例

```python
import _zrdds_basic
import _zrdds_domain
import _zrdds_topic
import _zrdds_publish
import _zrdds_shapetype

# 1. 获取工厂并创建域参与者
factory = _zrdds_domain.TheParticipantFactory
qos = _zrdds_domain.DomainParticipantQos()
factory.get_default_participant_qos(qos)
participant = factory.create_participant(80, qos, None, 0)

# 2. 注册数据类型
shapetype_support = _zrdds_shapetype.ShapeTypeTypeSupport.get_instance()
shapetype_support.register_type(participant, None)

# 3. 创建主题
topic_qos = _zrdds_domain.TopicQos()
participant.get_default_topic_qos(topic_qos)
topic = participant.create_topic(
    "MyTopic",
    shapetype_support.get_type_name(),
    topic_qos, None, 0
)

# 4. 创建发布者和数据写者
publisher_qos = _zrdds_domain.PublisherQos()
participant.get_default_publisher_qos(publisher_qos)
publisher = participant.create_publisher(publisher_qos, None, 0)

ret, datawriter_qos = publisher.get_default_datawriter_qos()
datawriter = publisher.create_datawriter(topic, datawriter_qos, None, 0)

# 5. 发布数据
data = _zrdds_shapetype.ShapeType()
data.x = 10
data.y = 20
data.z = "Hello DDS"

ret = datawriter.write(data, _zrdds_domain.HANDLE_NIL_NATIVE)
if ret == _zrdds_basic.RETCODE_OK:
    print("数据发布成功")
```

#### 2. 订阅者示例

```python
import _zrdds_basic
import _zrdds_domain
import _zrdds_topic
import _zrdds_subscribe
import _zrdds_shapetype

# 1. 创建域参与者（同发布者）
factory = _zrdds_domain.TheParticipantFactory
qos = _zrdds_domain.DomainParticipantQos()
factory.get_default_participant_qos(qos)
participant = factory.create_participant(80, qos, None, 0)

# 2. 注册数据类型（同发布者）
shapetype_support = _zrdds_shapetype.ShapeTypeTypeSupport.get_instance()
shapetype_support.register_type(participant, None)

# 3. 创建主题（同发布者）
topic_qos = _zrdds_domain.TopicQos()
participant.get_default_topic_qos(topic_qos)
topic = participant.create_topic(
    "MyTopic",
    shapetype_support.get_type_name(),
    topic_qos, None, 0
)

# 4. 创建订阅者和数据读者
subscriber_qos = _zrdds_domain.SubscriberQos()
participant.get_default_subscriber_qos(subscriber_qos)
subscriber = participant.create_subscriber(subscriber_qos, None, 0)

ret, datareader_qos = subscriber.get_default_datareader_qos()
datareader = subscriber.create_datareader(topic, datareader_qos, None, 0)

# 5. 读取数据
while True:
    data = _zrdds_shapetype.ShapeType()
    sample_info = _zrdds_shapetype.SampleInfo()
    
    ret = datareader.read_next_sample(data, sample_info)
    if ret == _zrdds_basic.RETCODE_OK and sample_info.valid_data:
        print(f"收到数据: x={data.x}, y={data.y}, z='{data.z}'")
    
    time.sleep(0.1)
```

## API 参考

### 错误处理

所有 API 方法都返回 `ReturnCode_t` 类型的错误码：

```python
# 检查操作结果
if ret == _zrdds_basic.RETCODE_OK:
    print("操作成功")
else:
    print(f"操作失败，错误码: {ret}")
```

### QoS 配置

QoS (Quality of Service) 是 DDS 的核心特性，用于控制数据传输的行为：

```python
# 获取默认 QoS
qos = _zrdds_domain.DomainParticipantQos()
ret = factory.get_default_participant_qos(qos)

# 自定义 QoS 配置
qos.reliability.kind = _zrdds_domain.RELIABLE_RELIABILITY_QOS
qos.durability.kind = _zrdds_domain.TRANSIENT_DURABILITY_QOS
```

### 监听器使用

监听器提供异步事件处理机制：

```python
class MyDataReaderListener(_zrdds_listener.DataReaderListener):
    def on_data_available(self, reader):
        # 处理新数据到达事件
        data = _zrdds_shapetype.ShapeType()
        sample_info = _zrdds_shapetype.SampleInfo()
        
        while reader.read_next_sample(data, sample_info) == _zrdds_basic.RETCODE_OK:
            if sample_info.valid_data:
                print(f"收到数据: {data.x}, {data.y}, {data.z}")

# 设置监听器
listener = MyDataReaderListener()
datareader.set_listener(listener, _zrdds_domain.STATUS_MASK_ALL)
```

## 使用示例

### 完整发布订阅示例

```python
#!/usr/bin/env python3
"""
完整的 DDS 发布订阅示例
"""

import sys
import os
import time
import threading

# 添加模块路径
current_dir = os.path.dirname(os.path.abspath(__file__))
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, build_release_dir)

def safe_str(s):
    """安全字符串转换"""
    try:
        if isinstance(s, bytes):
            return s.decode("utf-8", errors="replace")
        return str(s)
    except Exception:
        return repr(s)

class DDSManager:
    def __init__(self, domain_id=80):
        self.domain_id = domain_id
        self.participant = None
        self.factory = None
        
    def initialize(self):
        """初始化 DDS 环境"""
        try:
            # 导入模块
            import _zrdds_basic
            import _zrdds_domain
            import _zrdds_topic
            import _zrdds_publish
            import _zrdds_subscribe
            import _zrdds_shapetype
            
            self._zrdds_basic = _zrdds_basic
            self._zrdds_domain = _zrdds_domain
            self._zrdds_topic = _zrdds_topic
            self._zrdds_publish = _zrdds_publish
            self._zrdds_subscribe = _zrdds_subscribe
            self._zrdds_shapetype = _zrdds_shapetype
            
            # 获取工厂
            self.factory = self._zrdds_domain.TheParticipantFactory
            if self.factory is None:
                raise Exception("获取工厂实例失败")
            
            # 创建域参与者
            qos = self._zrdds_domain.DomainParticipantQos()
            ret = self.factory.get_default_participant_qos(qos)
            if ret != self._zrdds_basic.RETCODE_OK:
                raise Exception(f"获取默认 QoS 失败: {ret}")
            
            self.participant = self.factory.create_participant(
                self.domain_id, qos, None, 0
            )
            if self.participant is None:
                raise Exception("创建域参与者失败")
            
            # 注册数据类型
            self.shapetype_support = self._zrdds_shapetype.ShapeTypeTypeSupport.get_instance()
            ret = self.shapetype_support.register_type(self.participant, None)
            if ret != self._zrdds_basic.RETCODE_OK:
                raise Exception(f"注册类型失败: {ret}")
            
            print("✅ DDS 环境初始化成功")
            return True
            
        except Exception as e:
            print(f"❌ DDS 环境初始化失败: {e}")
            return False
    
    def create_topic(self, topic_name):
        """创建主题"""
        topic_qos = self._zrdds_domain.TopicQos()
        ret = self.participant.get_default_topic_qos(topic_qos)
        if ret != self._zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认主题 QoS 失败: {ret}")
        
        topic = self.participant.create_topic(
            topic_name,
            self.shapetype_support.get_type_name(),
            topic_qos, None, 0
        )
        if topic is None:
            raise Exception("创建主题失败")
        
        return topic
    
    def cleanup(self):
        """清理资源"""
        if self.participant:
            self.participant.delete_contained_entities()
            self.factory.delete_participant(self.participant)
            print("✅ 资源清理完成")

class Publisher(DDSManager):
    def __init__(self, domain_id=80, topic_name="MyTopic"):
        super().__init__(domain_id)
        self.topic_name = topic_name
        self.publisher = None
        self.datawriter = None
        self.topic = None
        
    def start(self):
        """启动发布者"""
        if not self.initialize():
            return False
        
        try:
            # 创建主题
            self.topic = self.create_topic(self.topic_name)
            
            # 创建发布者
            publisher_qos = self._zrdds_domain.PublisherQos()
            ret = self.participant.get_default_publisher_qos(publisher_qos)
            if ret != self._zrdds_basic.RETCODE_OK:
                raise Exception(f"获取默认发布者 QoS 失败: {ret}")
            
            self.publisher = self.participant.create_publisher(publisher_qos, None, 0)
            if self.publisher is None:
                raise Exception("创建发布者失败")
            
            # 创建数据写者
            ret, datawriter_qos = self.publisher.get_default_datawriter_qos()
            if ret != self._zrdds_basic.RETCODE_OK:
                raise Exception(f"获取默认 DataWriter QoS 失败: {ret}")
            
            self.datawriter = self.publisher.create_datawriter(
                self.topic, datawriter_qos, None, 0
            )
            if self.datawriter is None:
                raise Exception("创建数据写者失败")
            
            print(f"✅ 发布者启动成功，主题: {self.topic_name}")
            return True
            
        except Exception as e:
            print(f"❌ 发布者启动失败: {e}")
            return False
    
    def publish_data(self, x, y, z):
        """发布数据"""
        if not self.datawriter:
            return False
        
        data = self._zrdds_shapetype.ShapeType()
        data.x = x
        data.y = y
        data.z = z
        
        ret = self.datawriter.write(data, self._zrdds_domain.HANDLE_NIL_NATIVE)
        return ret == self._zrdds_basic.RETCODE_OK

class Subscriber(DDSManager):
    def __init__(self, domain_id=80, topic_name="MyTopic"):
        super().__init__(domain_id)
        self.topic_name = topic_name
        self.subscriber = None
        self.datareader = None
        self.topic = None
        self.running = False
        
    def start(self):
        """启动订阅者"""
        if not self.initialize():
            return False
        
        try:
            # 创建主题
            self.topic = self.create_topic(self.topic_name)
            
            # 创建订阅者
            subscriber_qos = self._zrdds_domain.SubscriberQos()
            ret = self.participant.get_default_subscriber_qos(subscriber_qos)
            if ret != self._zrdds_basic.RETCODE_OK:
                raise Exception(f"获取默认订阅者 QoS 失败: {ret}")
            
            self.subscriber = self.participant.create_subscriber(subscriber_qos, None, 0)
            if self.subscriber is None:
                raise Exception("创建订阅者失败")
            
            # 创建数据读者
            ret, datareader_qos = self.subscriber.get_default_datareader_qos()
            if ret != self._zrdds_basic.RETCODE_OK:
                raise Exception(f"获取默认 DataReader QoS 失败: {ret}")
            
            self.datareader = self.subscriber.create_datareader(
                self.topic, datareader_qos, None, 0
            )
            if self.datareader is None:
                raise Exception("创建数据读者失败")
            
            print(f"✅ 订阅者启动成功，主题: {self.topic_name}")
            return True
            
        except Exception as e:
            print(f"❌ 订阅者启动失败: {e}")
            return False
    
    def start_listening(self):
        """开始监听数据"""
        if not self.datareader:
            return
        
        self.running = True
        print(f"📡 开始监听数据，主题: {self.topic_name}")
        
        while self.running:
            data = self._zrdds_shapetype.ShapeType()
            sample_info = self._zrdds_shapetype.SampleInfo()
            
            ret = self.datareader.read_next_sample(data, sample_info)
            if ret == self._zrdds_basic.RETCODE_OK and sample_info.valid_data:
                safe_z = safe_str(data.z)
                print(f"📥 收到数据: x={data.x}, y={data.y}, z='{safe_z}'")
            
            time.sleep(0.1)
    
    def stop_listening(self):
        """停止监听"""
        self.running = False

def main():
    """主函数"""
    print("🚀 启动 DDS 发布订阅示例")
    
    # 创建发布者和订阅者
    publisher = Publisher(domain_id=80, topic_name="TestTopic")
    subscriber = Subscriber(domain_id=80, topic_name="TestTopic")
    
    try:
        # 启动订阅者
        if not subscriber.start():
            return
        
        # 在单独线程中启动监听
        listener_thread = threading.Thread(target=subscriber.start_listening)
        listener_thread.daemon = True
        listener_thread.start()
        
        # 等待一下让订阅者准备就绪
        time.sleep(1)
        
        # 启动发布者
        if not publisher.start():
            return
        
        # 发布一些测试数据
        print("\n📤 开始发布测试数据...")
        for i in range(10):
            success = publisher.publish_data(i, i*2, f"Message {i}")
            if success:
                print(f"📤 发布数据: x={i}, y={i*2}, z='Message {i}'")
            else:
                print(f"❌ 发布失败: x={i}, y={i*2}, z='Message {i}'")
            
            time.sleep(1)
        
        print("\n⏹️  测试完成，按 Enter 键退出...")
        input()
        
    except KeyboardInterrupt:
        print("\n⏹️  收到停止信号")
    except Exception as e:
        print(f"❌ 发生异常: {e}")
        import traceback
        traceback.print_exc()
    finally:
        # 清理资源
        subscriber.stop_listening()
        subscriber.cleanup()
        publisher.cleanup()
        print("✅ 程序结束")

if __name__ == "__main__":
    main()
```

## 最佳实践

### 1. 资源管理

```python
class DDSResourceManager:
    def __init__(self):
        self.participant = None
        self.factory = None
        
    def __enter__(self):
        # 初始化资源
        self.factory = _zrdds_domain.TheParticipantFactory
        qos = _zrdds_domain.DomainParticipantQos()
        self.factory.get_default_participant_qos(qos)
        self.participant = self.factory.create_participant(80, qos, None, 0)
        return self
        
    def __exit__(self, exc_type, exc_val, exc_tb):
        # 自动清理资源
        if self.participant:
            self.participant.delete_contained_entities()
            self.factory.delete_participant(self.participant)

# 使用上下文管理器
with DDSResourceManager() as dds:
    # 使用 DDS 资源
    pass
# 资源自动清理
```

### 2. 错误处理

```python
def safe_dds_operation(operation, *args, **kwargs):
    """安全的 DDS 操作包装器"""
    try:
        result = operation(*args, **kwargs)
        if hasattr(result, '__len__') and len(result) == 2:
            # 处理返回 (retcode, data) 的情况
            retcode, data = result
            if retcode != _zrdds_basic.RETCODE_OK:
                raise DDSException(f"DDS 操作失败，错误码: {retcode}")
            return data
        else:
            # 处理直接返回 retcode 的情况
            if result != _zrdds_basic.RETCODE_OK:
                raise DDSException(f"DDS 操作失败，错误码: {result}")
            return result
    except Exception as e:
        print(f"DDS 操作异常: {e}")
        raise

class DDSException(Exception):
    """DDS 异常类"""
    pass
```

### 3. 配置管理

```python
class DDSConfig:
    """DDS 配置管理"""
    
    def __init__(self):
        self.domain_id = 80
        self.topic_name = "DefaultTopic"
        self.qos_profiles = {}
        
    def load_from_file(self, config_file):
        """从文件加载配置"""
        import json
        with open(config_file, 'r') as f:
            config = json.load(f)
            self.domain_id = config.get('domain_id', 80)
            self.topic_name = config.get('topic_name', 'DefaultTopic')
            self.qos_profiles = config.get('qos_profiles', {})
    
    def get_qos(self, qos_type):
        """获取指定类型的 QoS"""
        return self.qos_profiles.get(qos_type, {})
```

### 4. 性能优化

```python
class HighPerformancePublisher:
    """高性能发布者"""
    
    def __init__(self, batch_size=100):
        self.batch_size = batch_size
        self.data_buffer = []
        
    def publish_batch(self, data_list):
        """批量发布数据"""
        for data in data_list:
            ret = self.datawriter.write(data, _zrdds_domain.HANDLE_NIL_NATIVE)
            if ret != _zrdds_basic.RETCODE_OK:
                print(f"批量发布失败: {ret}")
                return False
        return True
    
    def publish_async(self, data):
        """异步发布数据"""
        self.data_buffer.append(data)
        if len(self.data_buffer) >= self.batch_size:
            self.publish_batch(self.data_buffer)
            self.data_buffer.clear()
```

## 故障排除

### 常见问题

#### 1. 模块导入失败

**问题**: `ImportError: No module named '_zrdds_domain'`

**解决方案**:
```python
# 检查模块路径
import sys
print(sys.path)

# 添加正确的路径
sys.path.insert(0, 'build/Release')
sys.path.insert(0, 'zrpy')

# 检查文件是否存在
import os
print(os.path.exists('build/Release/_zrdds_domain.cp313-win_amd64.pyd'))
```

#### 2. 创建参与者失败

**问题**: `participant is None`

**解决方案**:
```python
# 检查域 ID 是否有效
domain_id = 80  # 使用有效的域 ID

# 检查 QoS 配置
qos = _zrdds_domain.DomainParticipantQos()
ret = factory.get_default_participant_qos(qos)
if ret != _zrdds_basic.RETCODE_OK:
    print(f"获取 QoS 失败: {ret}")

# 检查工厂实例
factory = _zrdds_domain.TheParticipantFactory
if factory is None:
    print("工厂实例为空")
```

#### 3. 数据读取失败

**问题**: `read_next_sample` 返回错误

**解决方案**:
```python
# 检查数据读者状态
if datareader is None:
    print("数据读者未创建")

# 检查主题匹配
topic_name = topic.get_name()
print(f"主题名称: {topic_name}")

# 检查数据类型注册
type_name = shapetype_support.get_type_name()
print(f"类型名称: {type_name}")

# 使用循环读取
while True:
    data = _zrdds_shapetype.ShapeType()
    sample_info = _zrdds_shapetype.SampleInfo()
    
    ret = datareader.read_next_sample(data, sample_info)
    if ret == _zrdds_basic.RETCODE_OK:
        if sample_info.valid_data:
            print(f"收到数据: {data.x}, {data.y}, {data.z}")
        else:
            print("无效数据")
    elif ret == _zrdds_basic.RETCODE_NO_DATA:
        print("暂无数据")
        time.sleep(0.1)
    else:
        print(f"读取失败: {ret}")
        break
```

#### 4. 内存泄漏

**问题**: 长时间运行后内存占用过高

**解决方案**:
```python
# 定期清理资源
def cleanup_resources():
    if participant:
        participant.delete_contained_entities()
        factory.delete_participant(participant)

# 使用弱引用
import weakref

class DDSManager:
    def __init__(self):
        self._participants = weakref.WeakSet()
    
    def add_participant(self, participant):
        self._participants.add(participant)
```

### 调试技巧

#### 1. 启用详细日志

```python
import logging

# 配置日志
logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)

logger = logging.getLogger('DDS')

# 在关键操作处添加日志
logger.debug(f"创建域参与者，域 ID: {domain_id}")
logger.debug(f"创建主题，名称: {topic_name}")
```

#### 2. 状态检查

```python
def check_dds_status(participant, topic, publisher, subscriber):
    """检查 DDS 实体状态"""
    print("=== DDS 状态检查 ===")
    
    # 检查参与者
    if participant:
        print("✅ 域参与者: 正常")
    else:
        print("❌ 域参与者: 未创建")
    
    # 检查主题
    if topic:
        print(f"✅ 主题: {topic.get_name()}")
    else:
        print("❌ 主题: 未创建")
    
    # 检查发布者
    if publisher:
        print("✅ 发布者: 正常")
    else:
        print("❌ 发布者: 未创建")
    
    # 检查订阅者
    if subscriber:
        print("✅ 订阅者: 正常")
    else:
        print("❌ 订阅者: 未创建")
```

#### 3. 性能监控

```python
import time
import psutil

class PerformanceMonitor:
    def __init__(self):
        self.start_time = time.time()
        self.message_count = 0
        
    def record_message(self):
        self.message_count += 1
        
    def get_stats(self):
        elapsed = time.time() - self.start_time
        rate = self.message_count / elapsed if elapsed > 0 else 0
        
        # 获取内存使用情况
        process = psutil.Process()
        memory_mb = process.memory_info().rss / 1024 / 1024
        
        return {
            'elapsed_time': elapsed,
            'message_count': self.message_count,
            'message_rate': rate,
            'memory_mb': memory_mb
        }
```

---

## 总结

ZRDDS Python API 提供了完整的 DDS 功能封装，通过模块化设计使得复杂的分布式数据通信变得简单易用。遵循本文档的最佳实践，可以快速构建高性能的分布式应用程序。

---
