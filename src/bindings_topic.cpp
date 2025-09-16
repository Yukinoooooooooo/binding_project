#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/operators.h>

// ZRDDS headers
#include "Topic.h"
#include "TopicDescription.h"
#include "ContentFilteredTopic.h"
#include "MultiTopic.h"
#include "TypeSupport.h"
#include "DomainParticipant.h"
#include "ReturnCode_t.h"
#include "TopicQos.h"
#include "TopicListener.h"
#include "InconsistentTopicStatus.h"
#include "ZRSequence.h"
#include "ZRDDSCppWrapper.h"

namespace py = pybind11;

// Note: Topic module provides class bindings only
// Users should create and manage topics through DomainParticipant methods

// Topic module wrapper
PYBIND11_MODULE(_zrdds_topic, m) {
    m.doc() = "ZRDDS Python Wrapper - Topic Module";
    
    // Bind TopicDescription class with nodelete policy (protected destructor)
    py::class_<DDS::TopicDescription, std::unique_ptr<DDS::TopicDescription, py::nodelete>>(m, "TopicDescription")
        .def("get_type_name", &DDS::TopicDescription::get_type_name,
             "Get type name of topic description")
        .def("get_name", &DDS::TopicDescription::get_name,
             "Get name of topic description")
        .def("get_participant", &DDS::TopicDescription::get_participant,
             "Get domain participant of topic description")
        .def("__repr__", [](const DDS::TopicDescription& self) {
            return "<DDS.TopicDescription>";
        });
    
    // Bind Topic class with nodelete policy (protected destructor)
    py::class_<DDS::Topic, DDS::DomainEntity, DDS::TopicDescription, std::unique_ptr<DDS::Topic, py::nodelete>>(m, "Topic")
        .def("set_qos_with_profile", &DDS::Topic::set_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), "Set QoS from QoS repository")
        .def("get_inconsistent_topic_status", [](DDS::Topic& self) -> py::tuple {
            DDS::InconsistentTopicStatus status;
            DDS::ReturnCode_t ret = self.get_inconsistent_topic_status(status);
            return py::make_tuple(ret, status);
        }, "Get inconsistent topic status")
        .def("set_qos", &DDS::Topic::set_qos,
             py::arg("qoslist"), "Set QoS for topic entity")
        .def("get_qos", [](DDS::Topic& self) -> py::tuple {
            DDS::TopicQos qoslist;
            DDS::ReturnCode_t ret = self.get_qos(qoslist);
            return py::make_tuple(ret, qoslist);
        }, "Get QoS settings for topic")
        .def("set_listener", &DDS::Topic::set_listener,
             py::arg("a_listener"), py::arg("mask"), "Set listener for topic")
        .def("get_listener", &DDS::Topic::get_listener,
             "Get listener for topic")
        .def("__repr__", [](const DDS::Topic& self) {
            return "<DDS.Topic>";
        });
    
    // Bind ContentFilteredTopic class with nodelete policy (protected destructor)
    py::class_<DDS::ContentFilteredTopic, DDS::TopicDescription, std::unique_ptr<DDS::ContentFilteredTopic, py::nodelete>>(m, "ContentFilteredTopic")
        .def("get_related_topic", &DDS::ContentFilteredTopic::get_related_topic,
             "Get the base topic associated with this content filtered topic")
        .def("get_expression_parameters", [](DDS::ContentFilteredTopic& self) -> py::tuple {
            DDS::StringSeq exp_paras;
            DDS::ReturnCode_t ret = self.get_expression_parameters(exp_paras);
            return py::make_tuple(ret, exp_paras);
        }, "Get associated filter parameters")
        .def("set_expression_parameters", &DDS::ContentFilteredTopic::set_expression_parameters,
             py::arg("exp_paras"), "Set new filter parameters")
        .def("get_filter_expression", &DDS::ContentFilteredTopic::get_filter_expression,
             "Get filter expression associated with this content filtered topic")
        .def("__repr__", [](const DDS::ContentFilteredTopic& self) {
            return "<DDS.ContentFilteredTopic>";
        });
    
    // Bind MultiTopic class with nodelete policy (protected destructor)
    py::class_<DDS::MultiTopic, DDS::TopicDescription, std::unique_ptr<DDS::MultiTopic, py::nodelete>>(m, "MultiTopic")
        .def("__repr__", [](const DDS::MultiTopic& self) {
            return "<DDS.MultiTopic>";
        });
    
    // Bind TypeSupport class
    py::class_<DDS::TypeSupport>(m, "TypeSupport")
        .def("get_type_name", &DDS::TypeSupport::get_type_name,
             "Get type name")
        .def("register_type", &DDS::TypeSupport::register_type,
             py::arg("participant"), py::arg("type_name"), "Register data type with domain participant")
        .def("unregister_type", &DDS::TypeSupport::unregister_type,
             py::arg("participant"), py::arg("type_name"), "Unregister type from domain participant")
        .def("__repr__", [](const DDS::TypeSupport& self) {
            return "<DDS.TypeSupport>";
        });
    
    // Constants
    m.attr("BUILTIN_PARTICIPANT_TOPIC_NAME") = DDS::BUILTIN_PARTICIPANT_TOPIC_NAME;
    m.attr("BUILTIN_PUBLICATION_TOPIC_NAME") = DDS::BUILTIN_PUBLICATION_TOPIC_NAME;
    m.attr("BUILTIN_SUBSCRIPTION_TOPIC_NAME") = DDS::BUILTIN_SUBSCRIPTION_TOPIC_NAME;
    m.attr("TOPIC_QOS_DEFAULT") = py::cast(DDS::TOPIC_QOS_DEFAULT);
    m.attr("STATUS_MASK_NONE") = py::cast(DDS::STATUS_MASK_NONE);
    
    // Initialize Topic module
    m.def("init", []() {
        return true;
    }, "Initialize ZRDDS Topic system");
    
    // Note: Topic module provides class bindings only
    // Users should create and manage topics through DomainParticipant methods
    
    // Cleanup function
    m.def("finalize", []() {
        return true;
    }, "Cleanup Topic DDS module");
    
    // Create topic 
    m.def("create_topic", [](py::object participant, const std::string& topic_name, const std::string& type_name, py::object qos, py::object listener, py::object mask) -> py::object {
        // 从Python对象获取C++ DomainParticipant指针
        DDS::DomainParticipant* dp = participant.cast<DDS::DomainParticipant*>();
        if (dp == nullptr) {
            return py::none();
        }
        
        // 创建Topic 
        DDS::TopicQos topic_qos;
        // 使用默认QoS，不需要特殊初始化
        
        DDS::Topic* topic = dp->create_topic(
            topic_name.c_str(),           // "DATARECEIVEBYLISTENER"
            type_name.c_str(),            // ShapeTypeTypeSupport::get_instance()->get_type_name()
            topic_qos,                    // 使用初始化的QoS
            nullptr,                      // NULL listener
            DDS::STATUS_MASK_NONE        // STATUS_MASK_NONE
        );
        
        if (topic == nullptr) {
            return py::none();
        }
        
        return py::cast(topic);
    }, "Create topic", py::arg("participant"), py::arg("topic_name"), py::arg("type_name"), py::arg("qos"), py::arg("listener"), py::arg("mask"));
    
    // Delete topic
    m.def("delete_topic", [](py::object topic, py::object participant) -> py::tuple {
        // 从Python对象获取C++ Topic指针
        DDS::Topic* topic_ptr = topic.cast<DDS::Topic*>();
        if (topic_ptr == nullptr) {
            return py::make_tuple(false, DDS::RETCODE_BAD_PARAMETER, "Invalid topic pointer");
        }
        
        // 从Python对象获取C++ DomainParticipant指针
        DDS::DomainParticipant* dp = participant.cast<DDS::DomainParticipant*>();
        if (dp == nullptr) {
            return py::make_tuple(false, DDS::RETCODE_BAD_PARAMETER, "Invalid participant pointer");
        }
        
        // 调用DomainParticipant的delete_topic方法
        DDS::ReturnCode_t ret = dp->delete_topic(topic_ptr);
        
        if (ret == DDS::RETCODE_OK) {
            return py::make_tuple(true, ret, "Topic deleted successfully");
        } else {
            std::string error_msg;
            if (ret == DDS::RETCODE_BAD_PARAMETER) {
                error_msg = "Invalid topic parameter or topic not created by this participant";
            } else if (ret == DDS::RETCODE_PRECONDITION_NOT_MET) {
                error_msg = "Topic cannot be deleted - it may have dependent entities (DataWriters, DataReaders, ContentFilteredTopics)";
            } else {
                error_msg = "Unknown error occurred during topic deletion";
            }
            return py::make_tuple(false, ret, error_msg);
        }
    }, "Delete topic", py::arg("topic"), py::arg("participant"));
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Topic Module - Complete Interface";
        
        py::list classes;
        classes.append(py::str("TopicDescription"));
        classes.append(py::str("Topic"));
        classes.append(py::str("ContentFilteredTopic"));
        classes.append(py::str("MultiTopic"));
        classes.append(py::str("TypeSupport"));
        info["classes"] = classes;
        
        py::list topic_methods;
        topic_methods.append(py::str("set_qos_with_profile"));
        topic_methods.append(py::str("get_inconsistent_topic_status"));
        topic_methods.append(py::str("set_qos"));
        topic_methods.append(py::str("get_qos"));
        topic_methods.append(py::str("set_listener"));
        topic_methods.append(py::str("get_listener"));
        info["topic_methods"] = topic_methods;
        
        py::list content_filtered_topic_methods;
        content_filtered_topic_methods.append(py::str("get_related_topic"));
        content_filtered_topic_methods.append(py::str("get_expression_parameters"));
        content_filtered_topic_methods.append(py::str("set_expression_parameters"));
        content_filtered_topic_methods.append(py::str("get_filter_expression"));
        info["content_filtered_topic_methods"] = content_filtered_topic_methods;
        
        py::list type_support_methods;
        type_support_methods.append(py::str("get_type_name"));
        type_support_methods.append(py::str("register_type"));
        type_support_methods.append(py::str("unregister_type"));
        info["type_support_methods"] = type_support_methods;
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        
        py::list constants;
        constants.append(py::str("BUILTIN_PARTICIPANT_TOPIC_NAME"));
        constants.append(py::str("BUILTIN_PUBLICATION_TOPIC_NAME"));
        constants.append(py::str("BUILTIN_SUBSCRIPTION_TOPIC_NAME"));
        info["constants"] = constants;
        
        return info;
    });
}
