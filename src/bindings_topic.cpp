#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// ZRDDS headers
#include "ZRDDSCppSimpleInterface.h"
#include "ZRBuiltinTypesTypeSupport.h"
#include "Topic.h"
#include "TopicDescription.h"
#include "ContentFilteredTopic.h"
#include "MultiTopic.h"
#include "TypeSupport.h"
#include "DomainEntity.h"
#include "ReturnCode_t.h"
#include "DomainParticipantFactory.h"
#include "ZRDDSCppWrapper.h"

namespace py = pybind11;

// Simple Topic DDS Manager - only manages topics
struct TopicDDSManager {
    static DDS::Topic* topic;
    static DDS::ContentFilteredTopic* content_filtered_topic;
    static DDS::MultiTopic* multi_topic;
    static DDS::TypeSupport* type_support;
    
    static void cleanup() {
        if (content_filtered_topic) {
            // Note: ContentFilteredTopic deletion is handled by DomainParticipant
            content_filtered_topic = nullptr;
        }
        if (multi_topic) {
            // Note: MultiTopic deletion is handled by DomainParticipant
            multi_topic = nullptr;
        }
        if (topic) {
            // Note: Topic deletion is handled by DomainParticipant
            topic = nullptr;
        }
                // TypeSupport is typically static, no need to delete
        type_support = nullptr;
    }
};

// Initialize static members
DDS::Topic* TopicDDSManager::topic = nullptr;
DDS::ContentFilteredTopic* TopicDDSManager::content_filtered_topic = nullptr;
DDS::MultiTopic* TopicDDSManager::multi_topic = nullptr;
DDS::TypeSupport* TopicDDSManager::type_support = nullptr;

// Topic module wrapper
PYBIND11_MODULE(_zrdds_topic, m) {
    m.doc() = "ZRDDS Python Wrapper - Topic Module (Simple Direct Interface)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Topic Module - Simple Direct Interface!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Topic Module v3.0.0 - Simple Direct Implementation";
    });
    
    // Initialize Topic module
    m.def("init", []() {
        TopicDDSManager::cleanup();
            return true;
    }, "Initialize ZRDDS Topic system");
    
    // Note: Topic module does not create domain participants
    // Domain participants should be created by domain module
    
    // Create Topic - requires participant from domain module
    m.def("create_topic", [](py::object participant_obj, const std::string& topic_name, const std::string& type_name = "Bytes") -> bool {
        if (TopicDDSManager::topic) {
            return true; // Already exists
        }
        
        // Get participant from domain module
        DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
        if (!participant) {
            return false; // Invalid participant
        }
        
        // Register type support
        if (type_name == "Bytes") {
            TopicDDSManager::type_support = DDS::BytesTypeSupport::get_instance();
            DDS::ReturnCode_t ret = TopicDDSManager::type_support->register_type(
            participant,
                "Bytes"
            );
            if (ret != DDS::RETCODE_OK) {
                return false;
            }
        }
        
        // Create topic with default QoS
        TopicDDSManager::topic = participant->create_topic(
             topic_name.c_str(), 
             type_name.c_str(),
            DDS::TOPIC_QOS_DEFAULT,
             nullptr, 
             DDS::STATUS_MASK_NONE
         );
        
        return (TopicDDSManager::topic != nullptr);
    }, py::arg("participant"), py::arg("topic_name"), py::arg("type_name") = "Bytes", "Create Topic");
    
    m.def("delete_topic", [](py::object participant_obj) -> bool {
        if (TopicDDSManager::topic) {
            // Get participant from domain module
            DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
            if (participant) {
                DDS::ReturnCode_t ret = participant->delete_topic(TopicDDSManager::topic);
                if (ret == DDS::RETCODE_OK) {
                    TopicDDSManager::topic = nullptr;
                    return true;
                }
            }
        }
        return false;
    }, py::arg("participant"), "Delete Topic");
    
    // Create ContentFilteredTopic - requires participant from domain module
    m.def("create_content_filtered_topic", [](py::object participant_obj, const std::string& name, const std::string& related_topic_name, 
                                              const std::string& filter_expression, const std::vector<std::string>& expression_parameters) -> bool {
        if (TopicDDSManager::content_filtered_topic) {
            return true; // Already exists
        }
        
        // Get participant from domain module
        DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
        if (!participant || !TopicDDSManager::topic) {
            return false; // Need participant and topic first
        }
        
        // Create string sequence for expression parameters
        DDS::StringSeq params;
        DDS_StringSeq_set_length(&params, expression_parameters.size());
        for (size_t i = 0; i < expression_parameters.size(); ++i) {
            DDS::String* ref = DDS_StringSeq_get_reference(&params, i);
            if (ref) {
                *ref = const_cast<char*>(expression_parameters[i].c_str());
            }
        }
        
        // Create content filtered topic
        TopicDDSManager::content_filtered_topic = participant->create_contentfilteredtopic(
            name.c_str(),
            TopicDDSManager::topic,
            filter_expression.c_str(),
            params
        );
        
        return (TopicDDSManager::content_filtered_topic != nullptr);
    }, py::arg("participant"), py::arg("name"), py::arg("related_topic_name"), py::arg("filter_expression"), py::arg("expression_parameters"), "Create ContentFilteredTopic");
    
    m.def("delete_content_filtered_topic", [](py::object participant_obj) -> bool {
        if (TopicDDSManager::content_filtered_topic) {
            DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
            if (participant) {
                DDS::ReturnCode_t ret = participant->delete_contentfilteredtopic(TopicDDSManager::content_filtered_topic);
                if (ret == DDS::RETCODE_OK) {
                    TopicDDSManager::content_filtered_topic = nullptr;
                    return true;
                }
            }
        }
        return false;
    }, py::arg("participant"), "Delete ContentFilteredTopic");
    
    // Create MultiTopic - direct creation
    m.def("create_multi_topic", [](py::object participant_obj, const std::string& name, const std::string& type_name, 
                                   const std::string& subscription_expression) -> bool {
        if (TopicDDSManager::multi_topic) {
            return true; // Already exists
        }
        
        // Get participant from domain module
        DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
        if (!participant) {
            return false; // Invalid participant
        }
        
        // Create multi topic
        TopicDDSManager::multi_topic = participant->create_multitopic(
            name.c_str(),
            type_name.c_str(),
            subscription_expression.c_str(),
            nullptr
        );
        
        return (TopicDDSManager::multi_topic != nullptr);
    }, py::arg("participant"), py::arg("name"), py::arg("type_name"), py::arg("subscription_expression"), "Create MultiTopic");
    
    m.def("delete_multi_topic", [](py::object participant_obj) -> bool {
        if (TopicDDSManager::multi_topic) {
            DDS::DomainParticipant* participant = participant_obj.cast<DDS::DomainParticipant*>();
            if (participant) {
                DDS::ReturnCode_t ret = participant->delete_multitopic(TopicDDSManager::multi_topic);
                if (ret == DDS::RETCODE_OK) {
                    TopicDDSManager::multi_topic = nullptr;
                    return true;
                }
            }
        }
        return false;
    }, py::arg("participant"), "Delete MultiTopic");
    
    // Topic operations
    m.def("get_topic_name", []() -> py::object {
        if (TopicDDSManager::topic) {
            return py::str(TopicDDSManager::topic->get_name());
        }
            return py::none();
    }, "Get Topic name");
    
    m.def("get_topic_type_name", []() -> py::object {
        if (TopicDDSManager::topic) {
            return py::str(TopicDDSManager::topic->get_type_name());
        }
        return py::none();
    }, "Get Topic type name");
    
    m.def("get_content_filtered_topic_name", []() -> py::object {
        if (TopicDDSManager::content_filtered_topic) {
            return py::str(TopicDDSManager::content_filtered_topic->get_name());
        }
        return py::none();
    }, "Get ContentFilteredTopic name");
    
    m.def("get_multi_topic_name", []() -> py::object {
        if (TopicDDSManager::multi_topic) {
            return py::str(TopicDDSManager::multi_topic->get_name());
        }
        return py::none();
    }, "Get MultiTopic name");
    
    // Check if entities exist
    m.def("topic_exists", []() -> bool {
        return (TopicDDSManager::topic != nullptr);
    }, "Check if topic exists");
    
    m.def("content_filtered_topic_exists", []() -> bool {
        return (TopicDDSManager::content_filtered_topic != nullptr);
    }, "Check if content filtered topic exists");
    
    m.def("multi_topic_exists", []() -> bool {
        return (TopicDDSManager::multi_topic != nullptr);
    }, "Check if multi topic exists");
    
    m.def("type_support_exists", []() -> bool {
        return (TopicDDSManager::type_support != nullptr);
    }, "Check if type support exists");
    
    // Cleanup function
    m.def("finalize", []() {
        TopicDDSManager::cleanup();
            return true;
    }, "Cleanup Topic DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Topic Module - Simple Direct Interface";
        info["topic_exists"] = (TopicDDSManager::topic != nullptr);
        info["content_filtered_topic_exists"] = (TopicDDSManager::content_filtered_topic != nullptr);
        info["multi_topic_exists"] = (TopicDDSManager::multi_topic != nullptr);
        info["type_support_exists"] = (TopicDDSManager::type_support != nullptr);
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_topic"));
        functions.append(py::str("delete_topic"));
        functions.append(py::str("create_content_filtered_topic"));
        functions.append(py::str("delete_content_filtered_topic"));
        functions.append(py::str("create_multi_topic"));
        functions.append(py::str("delete_multi_topic"));
        functions.append(py::str("get_topic_name"));
        functions.append(py::str("get_topic_type_name"));
        functions.append(py::str("get_content_filtered_topic_name"));
        functions.append(py::str("get_multi_topic_name"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
