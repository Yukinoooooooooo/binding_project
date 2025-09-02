#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <chrono>
#include <thread>

// ZRDDS C++ headers
#include "Subscriber.h"
#include "DataReader.h"
#include "ZRDDSDataReader.h"
#include "ReadCondition.h"
#include "DomainEntity.h"
#include "StatusKindMask.h"
#include "ReturnCode_t.h"
#include "InstanceHandle_t.h"
#include "ZRDDSCppWrapper.h"
#include "Topic.h"
#include "TopicQos.h"
#include "DomainParticipant.h"
#include "DomainParticipantFactory.h"
#include "ZRBuiltinTypesTypeSupport.h"
#include "ZRBuiltinTypesDataReader.h"
#include "ZRDDSDataReader.h"
#include "WaitSet.h"
#include "Condition.h"
#include "Duration_t.h"

namespace py = pybind11;

// Simple Subscribe DDS Manager - like your simple DDS module
struct SubscribeDDSManager {
    static DDS::DomainParticipant* participant;
    static DDS::Topic* topic;
    static DDS::Subscriber* subscriber;
    static DDS::DataReader* datareader;
    static DDS::SubscriberQos* subscriber_qos;
    static DDS::DataReaderQos* datareader_qos;
    static DDS::ReadCondition* read_condition;
    static DDS::WaitSet* waitset;
    
    static void cleanup() {
        if (read_condition) {
            if (datareader) {
                datareader->delete_readcondition(read_condition);
            }
            read_condition = nullptr;
        }
        if (waitset) {
            delete waitset;
            waitset = nullptr;
        }
        if (datareader) {
            if (subscriber) {
                subscriber->delete_datareader(datareader);
            }
            datareader = nullptr;
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
                participant->delete_contained_entities();
                factory->delete_participant(participant);
            }
            participant = nullptr;
        }
        if (subscriber_qos) {
            delete subscriber_qos;
            subscriber_qos = nullptr;
        }
        if (datareader_qos) {
            delete datareader_qos;
            datareader_qos = nullptr;
        }
    }
};

// Initialize static members
DDS::DomainParticipant* SubscribeDDSManager::participant = nullptr;
DDS::Topic* SubscribeDDSManager::topic = nullptr;
DDS::Subscriber* SubscribeDDSManager::subscriber = nullptr;
DDS::DataReader* SubscribeDDSManager::datareader = nullptr;
DDS::SubscriberQos* SubscribeDDSManager::subscriber_qos = nullptr;
DDS::DataReaderQos* SubscribeDDSManager::datareader_qos = nullptr;
DDS::ReadCondition* SubscribeDDSManager::read_condition = nullptr;
DDS::WaitSet* SubscribeDDSManager::waitset = nullptr;

// Subscribe module wrapper
PYBIND11_MODULE(_zrdds_subscribe, m) {
    m.doc() = "ZRDDS Python Wrapper - Subscribe Module (Simple Direct Interface)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Subscribe Module - Simple Direct Interface!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Subscribe Module v3.0.0 - Simple Direct Implementation";
    });
    
    // Initialize subscribe module
    m.def("init", []() {
        SubscribeDDSManager::cleanup();
        return true;
    }, "Initialize Subscribe DDS module");
    
    // Create domain participant - direct creation
    m.def("create_domain_participant", [](int domain_id) -> bool {
        if (SubscribeDDSManager::participant) {
            return true; // Already exists
        }
        
        DDS::DomainParticipantFactory* factory = DDS::DomainParticipantFactory::get_instance();
        if (!factory) {
            return false;
        }
        
        // Create participant with default QoS
        SubscribeDDSManager::participant = factory->create_participant(
            domain_id, 
            DDS::DOMAINPARTICIPANT_QOS_DEFAULT, 
            nullptr, 
            DDS::STATUS_MASK_NONE
        );
        
        return (SubscribeDDSManager::participant != nullptr);
    }, py::arg("domain_id"), "Create domain participant");
    
    // Create topic - direct creation
    m.def("create_topic", [](const std::string& topic_name, const std::string& type_name = "Bytes") -> bool {
        if (SubscribeDDSManager::topic) {
            return true; // Already exists
        }
        
        if (!SubscribeDDSManager::participant) {
            return false; // Need participant first
        }
        
        // Register type support
        if (type_name == "Bytes") {
            DDS::ReturnCode_t ret = DDS::BytesTypeSupport::get_instance()->register_type(
                SubscribeDDSManager::participant, 
            "Bytes"
        );
            if (ret != DDS::RETCODE_OK) {
            return false;
            }
        }
        
        // Create topic with default QoS
        SubscribeDDSManager::topic = SubscribeDDSManager::participant->create_topic(
            topic_name.c_str(), 
            type_name.c_str(),
            DDS::TOPIC_QOS_DEFAULT,
            nullptr, 
            DDS::STATUS_MASK_NONE
        );
        
        return (SubscribeDDSManager::topic != nullptr);
    }, py::arg("topic_name"), py::arg("type_name") = "Bytes", "Create Topic");
    
    // Create SubscriberQos - direct creation
    m.def("create_subscriber_qos", []() -> bool {
        if (SubscribeDDSManager::subscriber_qos) {
            return true; // Already exists
        }
        
        SubscribeDDSManager::subscriber_qos = new DDS::SubscriberQos();
        if (SubscribeDDSManager::subscriber_qos) {
            DDS_DefaultSubscriberQosInitial(SubscribeDDSManager::subscriber_qos);
            return true;
        }
        return false;
    }, "Create SubscriberQos with ZRDDS default values");
    
    m.def("delete_subscriber_qos", []() -> bool {
        if (SubscribeDDSManager::subscriber_qos) {
            delete SubscribeDDSManager::subscriber_qos;
            SubscribeDDSManager::subscriber_qos = nullptr;
            return true;
        }
        return false;
    }, "Delete SubscriberQos");
    
    // Create Subscriber - direct creation
    m.def("create_subscriber", []() -> bool {
        if (SubscribeDDSManager::subscriber) {
            return true; // Already exists
        }
        
        if (!SubscribeDDSManager::participant) {
            return false; // Need participant first
        }
        
        DDS::SubscriberQos* qos = SubscribeDDSManager::subscriber_qos;
        if (!qos) {
            // Create default QoS if not exists
            qos = new DDS::SubscriberQos();
            DDS_DefaultSubscriberQosInitial(qos);
        }
        
        SubscribeDDSManager::subscriber = SubscribeDDSManager::participant->create_subscriber(
            *qos,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (SubscribeDDSManager::subscriber != nullptr);
    }, "Create Subscriber");
    
    m.def("delete_subscriber", []() -> bool {
        if (SubscribeDDSManager::subscriber && SubscribeDDSManager::participant) {
            DDS::ReturnCode_t ret = SubscribeDDSManager::participant->delete_subscriber(SubscribeDDSManager::subscriber);
            if (ret == DDS::RETCODE_OK) {
                SubscribeDDSManager::subscriber = nullptr;
                return true;
            }
        }
        return false;
    }, "Delete Subscriber");
    
    // Create DataReaderQos - direct creation
    m.def("create_datareader_qos", []() -> bool {
        if (SubscribeDDSManager::datareader_qos) {
            return true; // Already exists
        }
        
        SubscribeDDSManager::datareader_qos = new DDS::DataReaderQos();
        if (SubscribeDDSManager::datareader_qos) {
            DDS_DefaultDataReaderQosInitial(SubscribeDDSManager::datareader_qos);
            return true;
        }
        return false;
    }, "Create DataReaderQos with ZRDDS default values");
    
    m.def("delete_datareader_qos", []() -> bool {
        if (SubscribeDDSManager::datareader_qos) {
            delete SubscribeDDSManager::datareader_qos;
            SubscribeDDSManager::datareader_qos = nullptr;
            return true;
        }
        return false;
    }, "Delete DataReaderQos");
    
    // Create DataReader - direct creation
    m.def("create_datareader", []() -> bool {
        if (SubscribeDDSManager::datareader) {
            return true; // Already exists
        }
        
        if (!SubscribeDDSManager::subscriber || !SubscribeDDSManager::topic) {
            return false; // Need subscriber and topic first
        }
        
        DDS::DataReaderQos* qos = SubscribeDDSManager::datareader_qos;
        if (!qos) {
            // Create default QoS if not exists
            qos = new DDS::DataReaderQos();
            DDS_DefaultDataReaderQosInitial(qos);
        }
        
        SubscribeDDSManager::datareader = SubscribeDDSManager::subscriber->create_datareader(
            SubscribeDDSManager::topic,
            *qos,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (SubscribeDDSManager::datareader != nullptr);
    }, "Create DataReader");
    
    m.def("delete_datareader", []() -> bool {
        if (SubscribeDDSManager::datareader && SubscribeDDSManager::subscriber) {
            DDS::ReturnCode_t ret = SubscribeDDSManager::subscriber->delete_datareader(SubscribeDDSManager::datareader);
            if (ret == DDS::RETCODE_OK) {
                SubscribeDDSManager::datareader = nullptr;
            return true;
            }
        }
        return false;
    }, "Delete DataReader");
    
    // Create ReadCondition - direct creation
    m.def("create_readcondition", []() -> bool {
        if (SubscribeDDSManager::read_condition) {
            return true; // Already exists
        }
        
        if (!SubscribeDDSManager::datareader) {
            return false; // Need datareader first
        }
        
        SubscribeDDSManager::read_condition = SubscribeDDSManager::datareader->create_readcondition(
            DDS::ANY_SAMPLE_STATE,
            DDS::ANY_VIEW_STATE,
            DDS::ANY_INSTANCE_STATE
        );
        
        return (SubscribeDDSManager::read_condition != nullptr);
    }, "Create ReadCondition");
    
    m.def("delete_readcondition", []() -> bool {
        if (SubscribeDDSManager::read_condition && SubscribeDDSManager::datareader) {
            DDS::ReturnCode_t ret = SubscribeDDSManager::datareader->delete_readcondition(SubscribeDDSManager::read_condition);
            if (ret == DDS::RETCODE_OK) {
                SubscribeDDSManager::read_condition = nullptr;
                return true;
            }
        }
        return false;
    }, "Delete ReadCondition");
    
    // Create WaitSet - direct creation
    m.def("create_waitset", []() -> bool {
        if (SubscribeDDSManager::waitset) {
            return true; // Already exists
        }
        
        SubscribeDDSManager::waitset = new DDS::WaitSet();
        return (SubscribeDDSManager::waitset != nullptr);
    }, "Create WaitSet");
    
    m.def("delete_waitset", []() -> bool {
        if (SubscribeDDSManager::waitset) {
            delete SubscribeDDSManager::waitset;
            SubscribeDDSManager::waitset = nullptr;
            return true;
        }
        return false;
    }, "Delete WaitSet");
    
    // WaitSet operations
    m.def("attach_condition", []() -> bool {
        if (SubscribeDDSManager::waitset && SubscribeDDSManager::read_condition) {
            DDS::ReturnCode_t ret = SubscribeDDSManager::waitset->attach_condition(SubscribeDDSManager::read_condition);
            return (ret == DDS::RETCODE_OK);
        }
        return false;
    }, "Attach read condition to WaitSet");
    
    m.def("detach_condition", []() -> bool {
        if (SubscribeDDSManager::waitset && SubscribeDDSManager::read_condition) {
            DDS::ReturnCode_t ret = SubscribeDDSManager::waitset->detach_condition(SubscribeDDSManager::read_condition);
            return (ret == DDS::RETCODE_OK);
        }
        return false;
    }, "Detach read condition from WaitSet");
    
    m.def("wait_for_data", [](int timeout_seconds, int timeout_nanoseconds) -> py::object {
        if (!SubscribeDDSManager::waitset) {
            return py::none();
        }
        
        // Create duration
        DDS::Duration_t timeout;
        timeout.sec = timeout_seconds;
        timeout.nanosec = timeout_nanoseconds;
        
        // Create condition sequence
        DDS::ConditionSeq active_conditions;
        
        // Wait
        DDS::ReturnCode_t ret = SubscribeDDSManager::waitset->wait(active_conditions, timeout);
        
        if (ret == DDS::RETCODE_TIMEOUT) {
            return py::bool_(false);
        } else if (ret != DDS::RETCODE_OK) {
            return py::none();
        }
        
        // Return list of active condition IDs
        py::list result;
        DDS::Long length = ConditionSeq_get_length(&active_conditions);
        for (DDS::Long i = 0; i < length; ++i) {
            DDS::ConditionPtr* ptr = ConditionSeq_get_reference(&active_conditions, i);
            if (ptr && *ptr) {
                // Check if it's our read condition
                if (*ptr == SubscribeDDSManager::read_condition) {
                    result.append(py::int_(1)); // Read condition ID
                }
            }
        }
        
        return result;
    }, py::arg("timeout_seconds") = 1, py::arg("timeout_nanoseconds") = 0, "Wait for data");

    // Data reading functions
    m.def("read_bytes_data", []() -> py::object {
        if (!SubscribeDDSManager::datareader) {
            return py::none();
        }
        
        // Cast to BytesDataReader for typed reading
        DDS::BytesDataReader* bytes_reader = 
            dynamic_cast<DDS::BytesDataReader*>(SubscribeDDSManager::datareader);
        if (!bytes_reader) {
            return py::none();
        }
        
        // Read data - like your C++ code
        DDS::Bytes sample;
        DDS::SampleInfo info;
        
        // Initialize sample properly - allocate enough space
        DDS_OctetSeq_set_length(&sample.value, 1024);  // Allocate 1KB buffer
        
        // Try read_next_sample first
        DDS::ReturnCode_t rtn = bytes_reader->read_next_sample(sample, info);
        
        if (rtn == DDS::RETCODE_OK && info.valid_data) {
            // Convert Bytes to Python string
            std::string result;
            DDS::ULong length = DDS_OctetSeq_get_length(&sample.value);
            for (DDS::ULong i = 0; i < length; ++i) {
                DDS::Octet* ref = DDS_OctetSeq_get_reference(&sample.value, i);
                if (ref) {
                    result += static_cast<char>(*ref);
                }
            }
            return py::str(result);
        }
        
        // If read failed, try take_next_sample
        DDS_OctetSeq_set_length(&sample.value, 1024);  // Allocate 1KB buffer
        rtn = bytes_reader->take_next_sample(sample, info);
        
        if (rtn == DDS::RETCODE_OK && info.valid_data) {
            // Convert Bytes to Python string
            std::string result;
            DDS::ULong length = DDS_OctetSeq_get_length(&sample.value);
            for (DDS::ULong i = 0; i < length; ++i) {
                DDS::Octet* ref = DDS_OctetSeq_get_reference(&sample.value, i);
                if (ref) {
                    result += static_cast<char>(*ref);
                }
            }
            return py::str(result);
        }
        
        return py::none();
    }, "Read bytes data from DataReader");
    
    m.def("read_string_data", []() -> py::object {
        // For now, treat string data as bytes data
        if (!SubscribeDDSManager::datareader) {
            return py::none();
        }
        
        // Cast to BytesDataReader for typed reading
        DDS::BytesDataReader* bytes_reader = 
            dynamic_cast<DDS::BytesDataReader*>(SubscribeDDSManager::datareader);
        if (!bytes_reader) {
            return py::none();
        }
        
        // Read data - like your C++ code
        DDS::Bytes sample;
        DDS::SampleInfo info;
        
        // Initialize sample properly - allocate enough space
        DDS_OctetSeq_set_length(&sample.value, 1024);  // Allocate 1KB buffer
        
        // Try read_next_sample first
        DDS::ReturnCode_t rtn = bytes_reader->read_next_sample(sample, info);
        
        if (rtn == DDS::RETCODE_OK && info.valid_data) {
            // Convert Bytes to Python string
            std::string result;
            DDS::ULong length = DDS_OctetSeq_get_length(&sample.value);
            for (DDS::ULong i = 0; i < length; ++i) {
                DDS::Octet* ref = DDS_OctetSeq_get_reference(&sample.value, i);
                if (ref) {
                    result += static_cast<char>(*ref);
                }
            }
            return py::str(result);
        }
        
        // If read failed, try take_next_sample
        DDS_OctetSeq_set_length(&sample.value, 1024);  // Allocate 1KB buffer
        rtn = bytes_reader->take_next_sample(sample, info);
        
        if (rtn == DDS::RETCODE_OK && info.valid_data) {
            // Convert Bytes to Python string
            std::string result;
            DDS::ULong length = DDS_OctetSeq_get_length(&sample.value);
            for (DDS::ULong i = 0; i < length; ++i) {
                DDS::Octet* ref = DDS_OctetSeq_get_reference(&sample.value, i);
                if (ref) {
                    result += static_cast<char>(*ref);
                }
            }
            return py::str(result);
        }
        
        return py::none();
    }, "Read string data from DataReader");
    
    // Check if entities exist
    m.def("participant_exists", []() -> bool {
        return (SubscribeDDSManager::participant != nullptr);
    }, "Check if participant exists");
    
    m.def("topic_exists", []() -> bool {
        return (SubscribeDDSManager::topic != nullptr);
    }, "Check if topic exists");
    
    m.def("subscriber_exists", []() -> bool {
        return (SubscribeDDSManager::subscriber != nullptr);
    }, "Check if subscriber exists");
    
    m.def("datareader_exists", []() -> bool {
        return (SubscribeDDSManager::datareader != nullptr);
    }, "Check if datareader exists");
    
    m.def("subscriber_qos_exists", []() -> bool {
        return (SubscribeDDSManager::subscriber_qos != nullptr);
    }, "Check if subscriber QoS exists");
    
    m.def("datareader_qos_exists", []() -> bool {
        return (SubscribeDDSManager::datareader_qos != nullptr);
    }, "Check if datareader QoS exists");
    
    m.def("readcondition_exists", []() -> bool {
        return (SubscribeDDSManager::read_condition != nullptr);
    }, "Check if read condition exists");
    
    m.def("waitset_exists", []() -> bool {
        return (SubscribeDDSManager::waitset != nullptr);
    }, "Check if waitset exists");
    
    // Cleanup function
    m.def("finalize", []() {
        SubscribeDDSManager::cleanup();
        return true;
    }, "Cleanup Subscribe DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Subscribe Module - Simple Direct Interface";
        info["participant_exists"] = (SubscribeDDSManager::participant != nullptr);
        info["topic_exists"] = (SubscribeDDSManager::topic != nullptr);
        info["subscriber_exists"] = (SubscribeDDSManager::subscriber != nullptr);
        info["datareader_exists"] = (SubscribeDDSManager::datareader != nullptr);
        info["subscriber_qos_exists"] = (SubscribeDDSManager::subscriber_qos != nullptr);
        info["datareader_qos_exists"] = (SubscribeDDSManager::datareader_qos != nullptr);
        info["readcondition_exists"] = (SubscribeDDSManager::read_condition != nullptr);
        info["waitset_exists"] = (SubscribeDDSManager::waitset != nullptr);
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_domain_participant"));
        functions.append(py::str("create_topic"));
        functions.append(py::str("create_subscriber_qos"));
        functions.append(py::str("delete_subscriber_qos"));
        functions.append(py::str("create_subscriber"));
        functions.append(py::str("delete_subscriber"));
        functions.append(py::str("create_datareader_qos"));
        functions.append(py::str("delete_datareader_qos"));
        functions.append(py::str("create_datareader"));
        functions.append(py::str("delete_datareader"));
        functions.append(py::str("create_readcondition"));
        functions.append(py::str("delete_readcondition"));
        functions.append(py::str("create_waitset"));
        functions.append(py::str("delete_waitset"));
        functions.append(py::str("attach_condition"));
        functions.append(py::str("detach_condition"));
        functions.append(py::str("wait_for_data"));
        functions.append(py::str("read_bytes_data"));
        functions.append(py::str("read_string_data"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
