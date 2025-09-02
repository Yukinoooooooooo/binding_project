#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// ZRDDS C++ headers
#include "Publisher.h"
#include "DataWriter.h"
#include "ZRDDSDataWriter.h"
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
#include "ZRBuiltinTypesDataWriter.h"

namespace py = pybind11;

// Simple Publish DDS Manager - only manages publishers and datawriters
struct PublishDDSManager {
    static DDS::Publisher* publisher;
    static DDS::DataWriter* datawriter;
    static DDS::PublisherQos* publisher_qos;
    static DDS::DataWriterQos* datawriter_qos;
    
    static void cleanup() {
        if (datawriter) {
            // Note: DataWriter deletion is handled by Publisher
            datawriter = nullptr;
        }
        if (publisher) {
            // Note: Publisher deletion is handled by DomainParticipant
            publisher = nullptr;
        }
        if (publisher_qos) {
            delete publisher_qos;
            publisher_qos = nullptr;
        }
        if (datawriter_qos) {
            delete datawriter_qos;
            datawriter_qos = nullptr;
        }
    }
};

// Initialize static members
DDS::Publisher* PublishDDSManager::publisher = nullptr;
DDS::DataWriter* PublishDDSManager::datawriter = nullptr;
DDS::PublisherQos* PublishDDSManager::publisher_qos = nullptr;
DDS::DataWriterQos* PublishDDSManager::datawriter_qos = nullptr;

// Publish module wrapper
PYBIND11_MODULE(_zrdds_publish, m) {
    m.doc() = "ZRDDS Python Wrapper - Publish Module (Simple Direct Interface)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Publish Module - Simple Direct Interface!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Publish Module v3.0.0 - Simple Direct Implementation";
    });
    
    // Initialize publish module
    m.def("init", []() {
        PublishDDSManager::cleanup();
        return true;
    }, "Initialize Publish DDS module");
    
    // Note: Publish module does not create domain participants or topics
    // Domain participants should be created by domain module
    // Topics should be created by topic module
    
    // Create PublisherQos - direct creation
    m.def("create_publisher_qos", []() -> bool {
        if (PublishDDSManager::publisher_qos) {
            return true; // Already exists
        }
        
        PublishDDSManager::publisher_qos = new DDS::PublisherQos();
        if (PublishDDSManager::publisher_qos) {
            DDS_DefaultPublisherQosInitial(PublishDDSManager::publisher_qos);
            return true;
        }
        return false;
    }, "Create PublisherQos with ZRDDS default values");
    
    m.def("delete_publisher_qos", []() -> bool {
        if (PublishDDSManager::publisher_qos) {
            delete PublishDDSManager::publisher_qos;
            PublishDDSManager::publisher_qos = nullptr;
            return true;
        }
        return false;
    }, "Delete PublisherQos");
    
    // Create Publisher - requires participant from domain module
    m.def("create_publisher", [](py::object participant_obj) -> bool {
        if (PublishDDSManager::publisher) {
            return true; // Already exists
        }
        
        // Get participant from domain module
        DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
        if (!participant) {
            return false; // Invalid participant
        }
        
        DDS::PublisherQos* qos = PublishDDSManager::publisher_qos;
        if (!qos) {
            // Create default QoS if not exists
            qos = new DDS::PublisherQos();
            DDS_DefaultPublisherQosInitial(qos);
        }
        
        PublishDDSManager::publisher = participant->create_publisher(
            *qos,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (PublishDDSManager::publisher != nullptr);
    }, py::arg("participant"), "Create Publisher");
    
    m.def("delete_publisher", [](py::object participant_obj) -> bool {
        if (PublishDDSManager::publisher) {
            DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
            if (participant) {
                DDS::ReturnCode_t ret = participant->delete_publisher(PublishDDSManager::publisher);
                if (ret == DDS::RETCODE_OK) {
                    PublishDDSManager::publisher = nullptr;
                    return true;
                }
            }
        }
        return false;
    }, py::arg("participant"), "Delete Publisher");
    
    // Create DataWriterQos - direct creation
    m.def("create_datawriter_qos", []() -> bool {
        if (PublishDDSManager::datawriter_qos) {
            return true; // Already exists
        }
        
        PublishDDSManager::datawriter_qos = new DDS::DataWriterQos();
        if (PublishDDSManager::datawriter_qos) {
            DDS_DefaultDataWriterQosInitial(PublishDDSManager::datawriter_qos);
            return true;
        }
        return false;
    }, "Create DataWriterQos with ZRDDS default values");
    
    m.def("delete_datawriter_qos", []() -> bool {
        if (PublishDDSManager::datawriter_qos) {
            delete PublishDDSManager::datawriter_qos;
            PublishDDSManager::datawriter_qos = nullptr;
            return true;
        }
        return false;
    }, "Delete DataWriterQos");
    
    // Create DataWriter - requires publisher and topic from other modules
    m.def("create_datawriter", [](py::object topic_obj) -> bool {
        if (PublishDDSManager::datawriter) {
            return true; // Already exists
        }
        
        if (!PublishDDSManager::publisher) {
            return false; // Need publisher first
        }
        
        // Get topic from topic module
        DDS::Topic* topic = topic_obj.cast<DDS::Topic*>();
        if (!topic) {
            return false; // Invalid topic
        }
        
        DDS::DataWriterQos* qos = PublishDDSManager::datawriter_qos;
        if (!qos) {
            // Create default QoS if not exists
            qos = new DDS::DataWriterQos();
            DDS_DefaultDataWriterQosInitial(qos);
        }
        
        PublishDDSManager::datawriter = PublishDDSManager::publisher->create_datawriter(
            topic,
            *qos,
            nullptr,
            DDS::STATUS_MASK_NONE
        );
        
        return (PublishDDSManager::datawriter != nullptr);
    }, py::arg("topic"), "Create DataWriter");
    
    m.def("delete_datawriter", []() -> bool {
        if (PublishDDSManager::datawriter && PublishDDSManager::publisher) {
            DDS::ReturnCode_t ret = PublishDDSManager::publisher->delete_datawriter(PublishDDSManager::datawriter);
            if (ret == DDS::RETCODE_OK) {
                PublishDDSManager::datawriter = nullptr;
                return true;
            }
        }
        return false;
    }, "Delete DataWriter");
    
    // Data writing functions
    m.def("write_bytes_data", [](const std::string& data) -> bool {
        if (!PublishDDSManager::datawriter) {
            return false;
        }
        
        // Cast to BytesDataWriter for typed writing
        DDS::BytesDataWriter* bytes_writer = 
            dynamic_cast<DDS::BytesDataWriter*>(PublishDDSManager::datawriter);
        if (!bytes_writer) {
            return false;
        }
        
        // Use DDS::Bytes for simple data writing
        DDS::Bytes bytes_data;
        DDS_OctetSeq_set_length(&bytes_data.value, data.length());
        for (size_t i = 0; i < data.length(); ++i) {
            DDS::Octet* ref = DDS_OctetSeq_get_reference(&bytes_data.value, i);
            if (ref) *ref = static_cast<unsigned char>(data[i]);
        }
        
        DDS::ReturnCode_t ret = bytes_writer->write(bytes_data, DDS::HANDLE_NIL_NATIVE);
        return (ret == DDS::RETCODE_OK);
    }, py::arg("data"), "Write bytes data to DataWriter");
    
    m.def("write_string_data", [](const std::string& data) -> bool {
        // For now, treat string data as bytes data
        if (!PublishDDSManager::datawriter) {
            return false;
        }
        
        // Cast to BytesDataWriter for typed writing
        DDS::BytesDataWriter* bytes_writer = 
            dynamic_cast<DDS::BytesDataWriter*>(PublishDDSManager::datawriter);
        if (!bytes_writer) {
            return false;
        }
        
        // Use DDS::Bytes for simple data writing
        DDS::Bytes bytes_data;
        DDS_OctetSeq_set_length(&bytes_data.value, data.length());
        for (size_t i = 0; i < data.length(); ++i) {
            DDS::Octet* ref = DDS_OctetSeq_get_reference(&bytes_data.value, i);
            if (ref) *ref = static_cast<unsigned char>(data[i]);
        }
        
        DDS::ReturnCode_t ret = bytes_writer->write(bytes_data, DDS::HANDLE_NIL_NATIVE);
        return (ret == DDS::RETCODE_OK);
    }, py::arg("data"), "Write string data to DataWriter");
    
    // Publisher operations
    m.def("begin_coherent_changes", []() -> bool {
        if (PublishDDSManager::publisher) {
            DDS::ReturnCode_t ret = PublishDDSManager::publisher->begin_coherent_changes();
            return (ret == DDS::RETCODE_OK);
        }
        return false;
    }, "Begin coherent changes");
    
    m.def("end_coherent_changes", []() -> bool {
        if (PublishDDSManager::publisher) {
            DDS::ReturnCode_t ret = PublishDDSManager::publisher->end_coherent_changes();
            return (ret == DDS::RETCODE_OK);
        }
        return false;
    }, "End coherent changes");
    
    // Check if entities exist
    m.def("publisher_exists", []() -> bool {
        return (PublishDDSManager::publisher != nullptr);
    }, "Check if publisher exists");
    
    m.def("datawriter_exists", []() -> bool {
        return (PublishDDSManager::datawriter != nullptr);
    }, "Check if datawriter exists");
    
    m.def("publisher_qos_exists", []() -> bool {
        return (PublishDDSManager::publisher_qos != nullptr);
    }, "Check if publisher QoS exists");
    
    m.def("datawriter_qos_exists", []() -> bool {
        return (PublishDDSManager::datawriter_qos != nullptr);
    }, "Check if datawriter QoS exists");
    
    // Cleanup function
    m.def("finalize", []() {
        PublishDDSManager::cleanup();
        return true;
    }, "Cleanup Publish DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Publish Module - Simple Direct Interface";
        info["publisher_exists"] = (PublishDDSManager::publisher != nullptr);
        info["datawriter_exists"] = (PublishDDSManager::datawriter != nullptr);
        info["publisher_qos_exists"] = (PublishDDSManager::publisher_qos != nullptr);
        info["datawriter_qos_exists"] = (PublishDDSManager::datawriter_qos != nullptr);
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_publisher_qos"));
        functions.append(py::str("delete_publisher_qos"));
        functions.append(py::str("create_publisher"));
        functions.append(py::str("delete_publisher"));
        functions.append(py::str("create_datawriter_qos"));
        functions.append(py::str("delete_datawriter_qos"));
        functions.append(py::str("create_datawriter"));
        functions.append(py::str("delete_datawriter"));
        functions.append(py::str("write_bytes_data"));
        functions.append(py::str("write_string_data"));
        functions.append(py::str("begin_coherent_changes"));
        functions.append(py::str("end_coherent_changes"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
