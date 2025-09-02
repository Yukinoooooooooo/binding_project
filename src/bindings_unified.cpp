#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <string>
#include <vector>

// ZRDDS includes
#include "DomainParticipantFactory.h"
#include "DomainParticipant.h"
#include "Topic.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "DataWriter.h"
#include "DataReader.h"
#include "WaitSet.h"
// #include "GuardCondition.h"
// #include "ReadCondition.h"
// #include "Condition.h"
// #include "Duration_t.h"
#include "ShapeType.h"
#include "ShapeTypeTypeSupport.h"
#include "ShapeTypeDataWriter.h"
#include "ShapeTypeDataReader.h"

namespace py = pybind11;

// Unified DDS Manager - 统一管理所有DDS实体
struct UnifiedDDSManager {
    // 核心实体
    static DDS::DomainParticipant* participant;
    static DDS::Topic* topic;
    static DDS::Publisher* publisher;
    static DDS::Subscriber* subscriber;
    static DDS::DataWriter* datawriter;
    static DDS::DataReader* datareader;
    
    // 辅助实体
    static DDS::WaitSet* waitset;
    // static DDS::GuardCondition* guard_condition;
    // static DDS::ReadCondition* read_condition;
    
    // 类型支持
    static DDS::ShapeTypeTypeSupport* type_support;
    
    static void cleanup() {
        // if (read_condition && datareader) {
        //     datareader->delete_readcondition(read_condition);
        //     read_condition = nullptr;
        // }
        if (datawriter) {
            if (publisher) {
                publisher->delete_datawriter(datawriter);
            }
            datawriter = nullptr;
        }
        if (datareader) {
            if (subscriber) {
                subscriber->delete_datareader(datareader);
            }
            datareader = nullptr;
        }
        if (publisher) {
            if (participant) {
                participant->delete_publisher(publisher);
            }
            publisher = nullptr;
        }
        if (subscriber) {
            if (participant) {
                participant->delete_subscriber(subscriber);
            }
            subscriber = nullptr;
        }
        if (topic) {
            if (participant) {
                participant->delete_topic(topic);
            }
            topic = nullptr;
        }
        if (participant) {
            DDS::DomainParticipantFactory* factory = DDS::DomainParticipantFactory::get_instance();
            if (factory) {
                factory->delete_participant(participant);
            }
            participant = nullptr;
        }
        if (waitset) {
            delete waitset;
            waitset = nullptr;
        }
        // if (guard_condition) {
        //     delete guard_condition;
        //     guard_condition = nullptr;
        // }
        if (type_support) {
            delete type_support;
            type_support = nullptr;
        }
    }
};

// 静态成员定义
DDS::DomainParticipant* UnifiedDDSManager::participant = nullptr;
DDS::Topic* UnifiedDDSManager::topic = nullptr;
DDS::Publisher* UnifiedDDSManager::publisher = nullptr;
DDS::Subscriber* UnifiedDDSManager::subscriber = nullptr;
DDS::DataWriter* UnifiedDDSManager::datawriter = nullptr;
DDS::DataReader* UnifiedDDSManager::datareader = nullptr;
DDS::WaitSet* UnifiedDDSManager::waitset = nullptr;
// DDS::GuardCondition* UnifiedDDSManager::guard_condition = nullptr;
// DDS::ReadCondition* UnifiedDDSManager::read_condition = nullptr;
DDS::ShapeTypeTypeSupport* UnifiedDDSManager::type_support = nullptr;

PYBIND11_MODULE(_zrdds_unified, m) {
    m.doc() = "Unified ZRDDS Module - Direct DDS Usage like C++";
    
    // 初始化
    m.def("init", []() -> bool {
        UnifiedDDSManager::cleanup();
        return true;
    }, "Initialize unified DDS manager");
    
    // 清理
    m.def("cleanup", []() -> bool {
        UnifiedDDSManager::cleanup();
        return true;
    }, "Cleanup all DDS entities");
    
    // 1. 创建域参与者 - 像C++那样直接
    m.def("create_participant", [](int domain_id) -> bool {
        if (UnifiedDDSManager::participant) {
            return true; // Already exists
        }
        
        DDS::DomainParticipantFactory* factory = DDS::DomainParticipantFactory::get_instance();
        if (!factory) {
            return false;
        }
        
        UnifiedDDSManager::participant = factory->create_participant(
            domain_id,
            DDS::DOMAINPARTICIPANT_QOS_DEFAULT,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (UnifiedDDSManager::participant != nullptr);
    }, py::arg("domain_id"), "Create DomainParticipant");
    
    // 2. 创建主题 - 严格按照C++代码
    m.def("create_topic", [](const std::string& topic_name) -> bool {
        if (UnifiedDDSManager::topic) {
            return true; // Already exists
        }
        
        if (!UnifiedDDSManager::participant) {
            return false; // Need participant first
        }
        
        // 注册类型支持 - 严格按照C++代码
        UnifiedDDSManager::type_support = DDS::ShapeTypeTypeSupport::get_instance();
        DDS::ReturnCode_t ret = UnifiedDDSManager::type_support->register_type(
            UnifiedDDSManager::participant, 
            nullptr
        );
        if (ret != DDS::RETCODE_OK) {
            return false;
        }
        
        // 创建主题 - 严格按照C++代码
        UnifiedDDSManager::topic = UnifiedDDSManager::participant->create_topic(
            topic_name.c_str(),
            UnifiedDDSManager::type_support->get_type_name(),
            DDS::TOPIC_QOS_DEFAULT,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (UnifiedDDSManager::topic != nullptr);
    }, py::arg("topic_name"), "Create Topic");
    
    // 3. 创建发布者 - 直接使用participant
    m.def("create_publisher", []() -> bool {
        if (UnifiedDDSManager::publisher) {
            return true; // Already exists
        }
        
        if (!UnifiedDDSManager::participant) {
            return false; // Need participant first
        }
        
        UnifiedDDSManager::publisher = UnifiedDDSManager::participant->create_publisher(
            DDS::PUBLISHER_QOS_DEFAULT,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (UnifiedDDSManager::publisher != nullptr);
    }, "Create Publisher");
    
    // 4. 创建订阅者 - 直接使用participant
    m.def("create_subscriber", []() -> bool {
        if (UnifiedDDSManager::subscriber) {
            return true; // Already exists
        }
        
        if (!UnifiedDDSManager::participant) {
            return false; // Need participant first
        }
        
        UnifiedDDSManager::subscriber = UnifiedDDSManager::participant->create_subscriber(
            DDS::SUBSCRIBER_QOS_DEFAULT,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (UnifiedDDSManager::subscriber != nullptr);
    }, "Create Subscriber");
    
    // 5. 创建数据写入器 - 直接使用publisher和topic
    m.def("create_datawriter", []() -> bool {
        if (UnifiedDDSManager::datawriter) {
            return true; // Already exists
        }
        
        if (!UnifiedDDSManager::publisher || !UnifiedDDSManager::topic) {
            return false; // Need publisher and topic first
        }
        
        UnifiedDDSManager::datawriter = UnifiedDDSManager::publisher->create_datawriter(
            UnifiedDDSManager::topic,
            DDS::DATAWRITER_QOS_DEFAULT,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (UnifiedDDSManager::datawriter != nullptr);
    }, "Create DataWriter");
    
    // 6. 创建数据读取器 - 直接使用subscriber和topic
    m.def("create_datareader", []() -> bool {
        if (UnifiedDDSManager::datareader) {
            return true; // Already exists
        }
        
        if (!UnifiedDDSManager::subscriber || !UnifiedDDSManager::topic) {
            return false; // Need subscriber and topic first
        }
        
        UnifiedDDSManager::datareader = UnifiedDDSManager::subscriber->create_datareader(
            UnifiedDDSManager::topic,
            DDS::DATAREADER_QOS_DEFAULT,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (UnifiedDDSManager::datareader != nullptr);
    }, "Create DataReader");
    
    // 7. 写入数据 - 严格按照C++代码
    m.def("write_data", [](const std::string& data) -> bool {
        if (!UnifiedDDSManager::datawriter) {
            return false;
        }
        
        // 转换为ShapeTypeDataWriter - 严格按照C++代码
        DDS::ShapeTypeDataWriter* shape_writer = 
            dynamic_cast<DDS::ShapeTypeDataWriter*>(UnifiedDDSManager::datawriter);
        if (!shape_writer) {
            return false;
        }
        
        // 创建数据样本 - 严格按照C++代码
        DDS::ShapeType sample;
        DDS::ShapeTypeInitialize(&sample);
        sample.x = 0;
        sample.y = 0;
        
        // 复制字符串数据到z字段
        strncpy(sample.z, data.c_str(), sizeof(sample.z) - 1);
        sample.z[sizeof(sample.z) - 1] = '\0';
        
        // 写入数据 - 严格按照C++代码
        DDS::ReturnCode_t ret = shape_writer->write(sample, DDS::HANDLE_NIL_NATIVE);
        return (ret == DDS::RETCODE_OK);
    }, py::arg("data"), "Write data");
    
    // 8. 读取数据 - 严格按照C++代码使用take方法
    m.def("read_data", []() -> py::object {
        if (!UnifiedDDSManager::datareader) {
            return py::none();
        }
        
        // 转换为ShapeTypeDataReader - 严格按照C++代码
        DDS::ShapeTypeDataReader* shape_reader = 
            dynamic_cast<DDS::ShapeTypeDataReader*>(UnifiedDDSManager::datareader);
        if (!shape_reader) {
            return py::none();
        }
        
        // 使用take方法 - 严格按照C++代码
        DDS::ShapeTypeSeq dataSeq;
        DDS::SampleInfoSeq infoSeq;
        
        DDS::ReturnCode_t ret = shape_reader->take(dataSeq, infoSeq, LENGTH_UNLIMITED,
            DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
        
        if (ret == DDS::RETCODE_OK && DDS_SampleInfoSeq_get_length(&infoSeq) > 0) {
            // 处理第一个有效数据 - 严格按照C++代码
            for (DDS::ULong i = 0; i < DDS_SampleInfoSeq_get_length(&infoSeq); ++i) {
                DDS::SampleInfo* info = DDS_SampleInfoSeq_get_reference(&infoSeq, i);
                if (info && info->valid_data) {
                    // 获取数据
                    DDS::ShapeType* data = DDS_ShapeTypeSeq_get_reference(&dataSeq, i);
                    if (data) {
                        // 归还数据 - 严格按照C++代码
                        shape_reader->return_loan(dataSeq, infoSeq);
                        return py::str(data->z);
                    }
                }
            }
            // 归还数据
            shape_reader->return_loan(dataSeq, infoSeq);
        }
        
        return py::none();
    }, "Read data using take method");
    
    // 9. 检查实体是否存在
    m.def("participant_exists", []() -> bool {
        return (UnifiedDDSManager::participant != nullptr);
    }, "Check if participant exists");
    
    m.def("topic_exists", []() -> bool {
        return (UnifiedDDSManager::topic != nullptr);
    }, "Check if topic exists");
    
    m.def("publisher_exists", []() -> bool {
        return (UnifiedDDSManager::publisher != nullptr);
    }, "Check if publisher exists");
    
    m.def("subscriber_exists", []() -> bool {
        return (UnifiedDDSManager::subscriber != nullptr);
    }, "Check if subscriber exists");
    
    m.def("datawriter_exists", []() -> bool {
        return (UnifiedDDSManager::datawriter != nullptr);
    }, "Check if datawriter exists");
    
    m.def("datareader_exists", []() -> bool {
        return (UnifiedDDSManager::datareader != nullptr);
    }, "Check if datareader exists");
    
    // 10. 获取状态信息
    m.def("get_status", []() -> py::dict {
        py::dict status;
        status["participant"] = (UnifiedDDSManager::participant != nullptr);
        status["topic"] = (UnifiedDDSManager::topic != nullptr);
        status["publisher"] = (UnifiedDDSManager::publisher != nullptr);
        status["subscriber"] = (UnifiedDDSManager::subscriber != nullptr);
        status["datawriter"] = (UnifiedDDSManager::datawriter != nullptr);
        status["datareader"] = (UnifiedDDSManager::datareader != nullptr);
        return status;
    }, "Get all entities status");
}
