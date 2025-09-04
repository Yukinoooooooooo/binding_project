#!/usr/bin/env python3
"""
ShapeType 发布者测试代码
模拟 C++ main_pub.cpp 的功能
"""

import sys
import os
import time

# 添加模块路径
current_dir = os.path.dirname(os.path.abspath(__file__))
build_release_dir = os.path.join(current_dir, 'build', 'Release')
sys.path.insert(0, current_dir)
sys.path.insert(0, build_release_dir)

def safe_str(s):
    """
    将数据安全转换为字符串，避免 UnicodeDecodeError
    """
    try:
        if isinstance(s, bytes):
            # 尝试用 utf-8 解码，遇到无法解码的字符用 替换
            return s.decode("utf-8", errors="replace")
        return str(s)
    except Exception:
        # 如果所有方法都失败，返回 repr 表示
        return repr(s)

def main():
    try:
        print("🚀 启动 ShapeType 发布者...")

        import _zrdds_basic
        import _zrdds_domain
        import _zrdds_topic
        import _zrdds_publish
        import _zrdds_listener
        import _zrdds_subscribe
        import _zrdds_shapetype

        print("✅ 所有模块导入成功")

        domain_id = 80
        factory = _zrdds_domain.TheParticipantFactory
        if factory is None:
            raise Exception("获取工厂实例失败")
        print("✅ 获取域参与者工厂成功")

        qos = _zrdds_domain.DomainParticipantQos()
        ret = factory.get_default_participant_qos(qos)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认 QoS 失败: {ret}")

        participant = factory.create_participant(domain_id, qos, None, 0)
        if participant is None:
            raise Exception("创建域参与者失败")
        print("✅ 创建域参与者成功")

        shapetype_support = _zrdds_shapetype.ShapeTypeTypeSupport.get_instance()
        ret = shapetype_support.register_type(participant, None)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"注册类型失败: {ret}")
        print("✅ 注册 ShapeType 类型成功")

        topic_qos = _zrdds_domain.TopicQos()
        ret = participant.get_default_topic_qos(topic_qos)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认主题 QoS 失败: {ret}")

        topic = participant.create_topic(
            "DATARECEIVEBYLISTENER",
            shapetype_support.get_type_name(),
            topic_qos,
            None,
            0
        )
        if topic is None:
            raise Exception("创建主题失败")
        print("✅ 创建主题成功")

        publisher_qos = _zrdds_domain.PublisherQos()
        ret = participant.get_default_publisher_qos(publisher_qos)
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认发布者 QoS 失败: {ret}")

        publisher = participant.create_publisher(publisher_qos, None, 0)
        if publisher is None:
            raise Exception("创建发布者失败")
        print("✅ 创建发布者成功")

        # 获取默认 DataWriter QoS
        ret, datawriter_qos = publisher.get_default_datawriter_qos()
        if ret != _zrdds_basic.RETCODE_OK:
            raise Exception(f"获取默认 DataWriter QoS 失败: {ret}")

        datawriter = publisher.create_datawriter(topic, datawriter_qos, None, 0)
        if datawriter is None:
            raise Exception("创建数据写者失败")
        print("✅ 创建数据写者成功")

        data = _zrdds_shapetype.ShapeType()
        data.x = 0
        data.y = 0
        data.z = "Data Receive by Listener"
        print("✅ 初始化数据成功")

        print("\n📡 开始发送数据...")
        print("   主题: DATARECEIVEBYLISTENER")
        print("   域号: 80")
        print("   按 Ctrl+C 停止\n")

        # 循环发送数据
        try:
            while True:
                ret = datawriter.write(data, _zrdds_domain.HANDLE_NIL_NATIVE)
                if ret != _zrdds_basic.RETCODE_OK:
                    print(f"❌ 写入失败: {ret}")
                else:
                    # 使用安全字符串转换函数
                    safe_z = safe_str(data.z)
                    print(f"📤 发送数据: x={data.x}, y={data.y}, z='{safe_z}'")

                data.x += 1
                time.sleep(2)

        except KeyboardInterrupt:
            print("\n⏹️  收到停止信号，开始清理...")

        print("🧹 清理资源...")
        ret = participant.delete_contained_entities()
        if ret != _zrdds_basic.RETCODE_OK:
            print(f"⚠️  删除包含实体失败: {ret}")

        ret = factory.delete_participant(participant)
        if ret != _zrdds_basic.RETCODE_OK:
            print(f"⚠️  删除域参与者失败: {ret}")

        print("✅ 资源清理完成")

    except Exception as e:
        print(f"❌ 发生异常: {e}")
        import traceback
        traceback.print_exc()


if __name__ == "__main__":
    main()
