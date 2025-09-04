#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <cstring>

// ZRDDS C++ headers
#include "DomainParticipant.h"
#include "DomainParticipantFactory.h"
#include "DomainEntity.h"
#include "ReturnCode_t.h"
#include "DomainParticipantQos.h"
#include "DomainParticipantFactoryQos.h"
#include "DomainParticipantListener.h"
#include "StatusKindMask.h"
#include "PublisherQos.h"
#include "SubscriberQos.h"
#include "TopicQos.h"
#include "DataWriterQos.h"
#include "DataReaderQos.h"
#include "PublisherListener.h"
#include "SubscriberListener.h"
#include "TopicListener.h"
#include "ContentFilteredTopic.h"
#include "MultiTopic.h"
#include "Topic.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "DataWriter.h"
#include "DataReader.h"
#include "DataWriterListener.h"
#include "DataReaderListener.h"
#include "TypeSupport.h"
#include "Duration_t.h"
#include "ZRDDSCppWrapper.h"
#include "InstanceHandle_t.h"
#include "ParticipantBuiltinTopicData.h"
#include "ZRSequence.h"

namespace py = pybind11;

// Domain module wrapper
PYBIND11_MODULE(_zrdds_domain, m) {
    m.doc() = "ZRDDS Python Wrapper - Domain Module (Complete Interface)";
    
    // ReturnCode_t enum is now defined in _zrdds_basic module
    // No need to duplicate enum registration here
    
    // Bind StatusKindMask constants (it's a typedef, not an enum)
    // 明确转换为 Python int 类型，避免类型不匹配
    m.attr("STATUS_MASK_NONE") = py::int_(static_cast<int>(DDS::STATUS_MASK_NONE));
    m.attr("STATUS_MASK_ALL") = py::int_(static_cast<int>(DDS::STATUS_MASK_ALL));
    
    // Bind DomainParticipantQos class
    py::class_<DDS::DomainParticipantQos>(m, "DomainParticipantQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DomainParticipantQos& self) {
            return "<DDS.DomainParticipantQos>";
        });
    
    // Bind DomainParticipantFactoryQos class
    py::class_<DDS::DomainParticipantFactoryQos>(m, "DomainParticipantFactoryQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DomainParticipantFactoryQos& self) {
            return "<DDS.DomainParticipantFactoryQos>";
        });
    
    // Bind PublisherQos class
    py::class_<DDS::PublisherQos>(m, "PublisherQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::PublisherQos& self) {
            return "<DDS.PublisherQos>";
        });
    
    // Bind SubscriberQos class
    py::class_<DDS::SubscriberQos>(m, "SubscriberQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::SubscriberQos& self) {
            return "<DDS.SubscriberQos>";
        });
    
    // Bind TopicQos class
    py::class_<DDS::TopicQos>(m, "TopicQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::TopicQos& self) {
            return "<DDS.TopicQos>";
        });
    
    // Bind DataWriterQos class
    py::class_<DDS::DataWriterQos>(m, "DataWriterQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DataWriterQos& self) {
            return "<DDS.DataWriterQos>";
        });
    
    // Bind DataReaderQos class
    py::class_<DDS::DataReaderQos>(m, "DataReaderQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DataReaderQos& self) {
            return "<DDS.DataReaderQos>";
        });
    
    // Bind Duration_t class (Time_t is typedef of Duration_t in Duration_t.h line 229)
    py::class_<DDS::Duration_t>(m, "Duration_t")
        .def(py::init<>())
        .def_readwrite("sec", &DDS::Duration_t::sec)
        .def_readwrite("nanosec", &DDS::Duration_t::nanosec)
        .def("__repr__", [](const DDS::Duration_t& self) {
            return "<DDS.Duration_t(sec=" + std::to_string(self.sec) + ", nanosec=" + std::to_string(self.nanosec) + ")>";
        });
    
    // Time_t is typedef of Duration_t, so create an alias instead of duplicate registration
    m.attr("Time_t") = m.attr("Duration_t");
    
    // Bind InstanceHandle_t
    py::class_<DDS::InstanceHandle_t>(m, "InstanceHandle_t")
        .def(py::init<>())
        .def("__repr__", [](const DDS::InstanceHandle_t& self) {
            return "<DDS.InstanceHandle_t>";
        });
    

    
    // Bind DomainParticipant class with nodelete policy (protected destructor)
    py::class_<DDS::DomainParticipant, std::unique_ptr<DDS::DomainParticipant, py::nodelete>>(m, "DomainParticipant")
        // QoS methods
        .def("get_qos", [](DDS::DomainParticipant& self, DDS::DomainParticipantQos& qos) -> DDS::ReturnCode_t {
            return self.get_qos(qos);
        }, py::arg("qos"))
        .def("set_qos", [](DDS::DomainParticipant& self, const DDS::DomainParticipantQos& qos) -> DDS::ReturnCode_t {
            return self.set_qos(qos);
        }, py::arg("qos"))
        .def("set_qos_with_profile", &DDS::DomainParticipant::set_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        
        // Listener methods
        .def("get_listener", [](DDS::DomainParticipant& self) -> DDS::DomainParticipantListener* {
            return self.get_listener();
        })
        .def("set_listener", [](DDS::DomainParticipant& self, DDS::DomainParticipantListener* a_listener, const DDS::StatusKindMask& mask) -> DDS::ReturnCode_t {
            return self.set_listener(a_listener, mask);
        }, py::arg("a_listener"), py::arg("mask"))
        
        // Publisher methods
        .def("create_publisher", [](DDS::DomainParticipant& self, const DDS::PublisherQos& qoslist, DDS::PublisherListener* a_listener, const DDS::StatusKindMask& mask) -> DDS::Publisher* {
            return self.create_publisher(qoslist, a_listener, mask);
        }, py::arg("qoslist"), py::arg("a_listener") = nullptr, py::arg("mask") = 0)
        .def("create_publisher_with_qos_profile", &DDS::DomainParticipant::create_publisher_with_qos_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), 
             py::arg("listener") = nullptr, py::arg("mask") = 0)
        .def("delete_publisher", [](DDS::DomainParticipant& self, DDS::Publisher* pub) -> DDS::ReturnCode_t {
            return self.delete_publisher(pub);
        }, py::arg("pub"))
        .def("get_auto_created_publisher", [](DDS::DomainParticipant& self) -> DDS::Publisher* {
            return self.get_auto_created_publisher();
        })
        
        // Subscriber methods
        .def("create_subscriber", [](DDS::DomainParticipant& self, const DDS::SubscriberQos& qoslist, DDS::SubscriberListener* a_listener, const DDS::StatusKindMask& mask) -> DDS::Subscriber* {
            return self.create_subscriber(qoslist, a_listener, mask);
        }, py::arg("qoslist"), py::arg("a_listener") = nullptr, py::arg("mask") = 0)
        .def("create_subscriber_with_qos_profile", &DDS::DomainParticipant::create_subscriber_with_qos_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), 
             py::arg("listener") = nullptr, py::arg("mask") = 0)
        .def("delete_subscriber", [](DDS::DomainParticipant& self, DDS::Subscriber* sub) -> DDS::ReturnCode_t {
            return self.delete_subscriber(sub);
        }, py::arg("sub"))
        .def("get_auto_created_subscriber", [](DDS::DomainParticipant& self) -> DDS::Subscriber* {
            return self.get_auto_created_subscriber();
        })
        .def("get_builtin_subscriber", [](DDS::DomainParticipant& self) -> DDS::Subscriber* {
            return self.get_builtin_subscriber();
        })
        
        // Topic methods
        .def("create_topic", [](DDS::DomainParticipant& self, const char* topic_name, const char* type_name, const DDS::TopicQos& qoslist, DDS::TopicListener* a_listener, const DDS::StatusKindMask& mask) -> DDS::Topic* {
            return self.create_topic(topic_name, type_name, qoslist, a_listener, mask);
        }, py::arg("topic_name"), py::arg("type_name"), py::arg("qoslist"), py::arg("a_listener") = nullptr, py::arg("mask") = 0)
        .def("create_topic_w_type_support", [](DDS::DomainParticipant& self, const char* topic_name, DDS::TypeSupport* type_support, const DDS::TopicQos& qoslist, DDS::TopicListener* a_listener, const DDS::StatusKindMask& mask) -> DDS::Topic* {
            return self.create_topic_w_type_support(topic_name, type_support, qoslist, a_listener, mask);
        }, py::arg("topic_name"), py::arg("type_support"), py::arg("qoslist"), py::arg("a_listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("create_topic_with_qos_profile", &DDS::DomainParticipant::create_topic_with_qos_profile,
             py::arg("topic_name"), py::arg("type_name"), py::arg("library_name"), py::arg("profile_name"), 
             py::arg("qos_name"), py::arg("listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("delete_topic", [](DDS::DomainParticipant& self, DDS::Topic* topic) -> DDS::ReturnCode_t {
            return self.delete_topic(topic);
        }, py::arg("topic"))
        .def("find_topic", [](DDS::DomainParticipant& self, const char* topic_name, const DDS::Duration_t& timeout) -> DDS::Topic* {
            return self.find_topic(topic_name, timeout);
        }, py::arg("topic_name"), py::arg("timeout"))
        
        // DataWriter/DataReader creation with QoS profiles
        .def("create_datawriter_with_topic_and_qos_profile", &DDS::DomainParticipant::create_datawriter_with_topic_and_qos_profile,
             py::arg("topicName"), py::arg("typeSupport"), py::arg("library_name"), py::arg("profile_name"), 
             py::arg("qos_name"), py::arg("dw_listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("create_datareader_with_topic_and_qos_profile", &DDS::DomainParticipant::create_datareader_with_topic_and_qos_profile,
             py::arg("topicName"), py::arg("typeSupport"), py::arg("library_name"), py::arg("profile_name"), 
             py::arg("qos_name"), py::arg("dr_listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        
        // Default QoS methods
        .def("set_default_topic_qos", [](DDS::DomainParticipant& self, const DDS::TopicQos& qos) -> DDS::ReturnCode_t {
            return self.set_default_topic_qos(qos);
        }, py::arg("qos"))
        .def("set_default_topic_qos_with_profile", &DDS::DomainParticipant::set_default_topic_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("set_default_publisher_qos", [](DDS::DomainParticipant& self, const DDS::PublisherQos& qos) -> DDS::ReturnCode_t {
            return self.set_default_publisher_qos(qos);
        }, py::arg("qos"))
        .def("set_default_publisher_qos_with_profile", &DDS::DomainParticipant::set_default_publisher_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("set_default_subscriber_qos", [](DDS::DomainParticipant& self, const DDS::SubscriberQos& qos) -> DDS::ReturnCode_t {
            return self.set_default_subscriber_qos(qos);
        }, py::arg("qos"))
        .def("set_default_subscriber_qos_with_profile", &DDS::DomainParticipant::set_default_subscriber_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_default_topic_qos", [](DDS::DomainParticipant& self, DDS::TopicQos& qos) -> DDS::ReturnCode_t {
            return self.get_default_topic_qos(qos);
        }, py::arg("qos"))
        .def("get_default_publisher_qos", [](DDS::DomainParticipant& self, DDS::PublisherQos& qos) -> DDS::ReturnCode_t {
            return self.get_default_publisher_qos(qos);
        }, py::arg("qos"))
        .def("get_default_subscriber_qos", [](DDS::DomainParticipant& self, DDS::SubscriberQos& qos) -> DDS::ReturnCode_t {
            return self.get_default_subscriber_qos(qos);
        }, py::arg("qos"))
        
        // Utility methods
        .def("delete_contained_entities", [](DDS::DomainParticipant& self) -> DDS::ReturnCode_t {
            return self.delete_contained_entities();
        })
        .def("get_current_time", [](DDS::DomainParticipant& self, DDS::Time_t& current_time) -> DDS::ReturnCode_t {
            return self.get_current_time(current_time);
        }, py::arg("current_time"))
        .def("get_domain_id", [](DDS::DomainParticipant& self) -> DDS::DomainId_t {
            return self.get_domain_id();
        })
        .def("assert_liveliness", [](DDS::DomainParticipant& self) -> DDS::ReturnCode_t {
            return self.assert_liveliness();
        })
        .def("contains_entity", [](DDS::DomainParticipant& self, const DDS::InstanceHandle_t& handle) -> bool {
            return self.contains_entity(handle);
        }, py::arg("handle"))
        
        // Discovery and management methods
        .def("get_publishers", [](DDS::DomainParticipant& self, DDS::PublisherSeq& publisherList) -> DDS::ReturnCode_t {
            return self.get_publishers(publisherList);
        }, py::arg("publisherList"))
        .def("get_subscribers", [](DDS::DomainParticipant& self, DDS::SubscriberSeq& subscriberList) -> DDS::ReturnCode_t {
            return self.get_subscribers(subscriberList);
        }, py::arg("subscriberList"))
        .def("lookup_topicdescription", [](DDS::DomainParticipant& self, const char* name) -> DDS::TopicDescription* {
            return self.lookup_topicdescription(name);
        }, py::arg("name"))
        
        // Ignore methods
        .def("ignore_participant", [](DDS::DomainParticipant& self, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.ignore_participant(handle);
        }, py::arg("handle"))
        .def("ignore_publication", [](DDS::DomainParticipant& self, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.ignore_publication(handle);
        }, py::arg("handle"))
        .def("ignore_subscription", [](DDS::DomainParticipant& self, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.ignore_subscription(handle);
        }, py::arg("handle"))
        .def("ignore_topic", [](DDS::DomainParticipant& self, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.ignore_topic(handle);
        }, py::arg("handle"))
        
        // Discovery methods
        .def("get_discovered_participants", [](DDS::DomainParticipant& self, DDS::InstanceHandleSeq& discoved_handleList) -> DDS::ReturnCode_t {
            return self.get_discovered_participants(discoved_handleList);
        }, py::arg("discoved_handleList"))
        .def("get_discovered_participant_data", [](DDS::DomainParticipant& self, DDS::ParticipantBuiltinTopicData& a_pd, const DDS::InstanceHandle_t& a_handle) -> DDS::ReturnCode_t {
            return self.get_discovered_participant_data(a_pd, a_handle);
        }, py::arg("a_pd"), py::arg("a_handle"))
        .def("get_discovered_topics", [](DDS::DomainParticipant& self, DDS::InstanceHandleSeq& discoved_handleList) -> DDS::ReturnCode_t {
            return self.get_discovered_topics(discoved_handleList);
        }, py::arg("discoved_handleList"))
        
        .def("__repr__", [](const DDS::DomainParticipant& self) {
            return "<DDS.DomainParticipant>";
        });
    
    // Bind DomainParticipantFactory class with nodelete policy (protected destructor)
    py::class_<DDS::DomainParticipantFactory, std::unique_ptr<DDS::DomainParticipantFactory, py::nodelete>>(m, "DomainParticipantFactory")
        .def_static("get_instance", []() -> DDS::DomainParticipantFactory* {
            return DDS::DomainParticipantFactory::get_instance();
        })
        .def_static("get_instance_w_qos", [](const DDS::DomainParticipantFactoryQos& qos) -> DDS::DomainParticipantFactory* {
            return DDS::DomainParticipantFactory::get_instance_w_qos(qos);
        }, py::arg("qos"))
        .def_static("get_instance_w_profile", [](const char* qosFilePath, const char* libName, const char* profileName, const char* qosName) -> DDS::DomainParticipantFactory* {
            return DDS::DomainParticipantFactory::get_instance_w_profile(qosFilePath, libName, profileName, qosName);
        }, py::arg("qosFilePath") = nullptr, py::arg("libName"), py::arg("profileName"), py::arg("qosName"))
        .def_static("finalize_instance", []() -> DDS::ReturnCode_t {
            return DDS::DomainParticipantFactory::finalize_instance();
        })
        
        // Participant creation
        .def("create_participant", [](DDS::DomainParticipantFactory& self, DDS::DomainId_t domainId, const DDS::DomainParticipantQos& qoslist, DDS::DomainParticipantListener* a_listener, DDS::StatusKindMask mask) -> DDS::DomainParticipant* {
            return self.create_participant(domainId, qoslist, a_listener, mask);
        }, py::arg("domainId"), py::arg("qoslist"), py::arg("a_listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("create_participant_with_qos_profile", &DDS::DomainParticipantFactory::create_participant_with_qos_profile,
             py::arg("domainId"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), 
             py::arg("listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("delete_participant", [](DDS::DomainParticipantFactory& self, DDS::DomainParticipant* a_dp) -> DDS::ReturnCode_t {
            return self.delete_participant(a_dp);
        }, py::arg("a_dp"))
        .def("lookup_participant", [](DDS::DomainParticipantFactory& self, DDS::DomainId_t domainId) -> DDS::DomainParticipant* {
            return self.lookup_participant(domainId);
        }, py::arg("domainId"))
        .def("delete_contained_entities", [](DDS::DomainParticipantFactory& self) -> DDS::ReturnCode_t {
            return self.delete_contained_entities();
        })
        
        // QoS methods
        .def("get_default_participant_qos", [](DDS::DomainParticipantFactory& self, DDS::DomainParticipantQos& qos) -> DDS::ReturnCode_t {
            return self.get_default_participant_qos(qos);
        }, py::arg("qos"))
        .def("set_default_participant_qos", [](DDS::DomainParticipantFactory& self, const DDS::DomainParticipantQos& qos) -> DDS::ReturnCode_t {
            return self.set_default_participant_qos(qos);
        }, py::arg("qos"))
        .def("set_default_participant_qos_with_profile", &DDS::DomainParticipantFactory::set_default_participant_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_qos", [](DDS::DomainParticipantFactory& self, DDS::DomainParticipantFactoryQos& qos) -> DDS::ReturnCode_t {
            return self.get_qos(qos);
        }, py::arg("qos"))
        .def("set_qos", [](DDS::DomainParticipantFactory& self, const DDS::DomainParticipantFactoryQos& qos) -> DDS::ReturnCode_t {
            return self.set_qos(qos);
        }, py::arg("qos"))
        .def("set_qos_with_profile", &DDS::DomainParticipantFactory::set_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        
        // QoS profile methods
        .def("get_participant_qos_from_profile", &DDS::DomainParticipantFactory::get_participant_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_publisher_qos_from_profile", &DDS::DomainParticipantFactory::get_publisher_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_subscriber_qos_from_profile", &DDS::DomainParticipantFactory::get_subscriber_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_topic_qos_from_profile", &DDS::DomainParticipantFactory::get_topic_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_datawriter_qos_from_profile", &DDS::DomainParticipantFactory::get_datawriter_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_datareader_qos_from_profile", &DDS::DomainParticipantFactory::get_datareader_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_participant_factory_qos_from_profile", &DDS::DomainParticipantFactory::get_participant_factory_qos_from_profile,
             py::arg("qos"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        
        // QoS library management
        .def("add_qos_library", &DDS::DomainParticipantFactory::add_qos_library, py::arg("xml_representation"))
        .def("remove_qos_library", &DDS::DomainParticipantFactory::remove_qos_library, py::arg("qos_library_name"))
        .def("add_qos_profile", &DDS::DomainParticipantFactory::add_qos_profile, py::arg("qos_library_name"), py::arg("xml_representation"))
        .def("remove_qos_profile", &DDS::DomainParticipantFactory::remove_qos_profile, py::arg("qos_library_name"), py::arg("qos_profile_name"))
        .def("lookup_qos_libraries", &DDS::DomainParticipantFactory::lookup_qos_libraries, py::arg("pattern"), py::arg("qos_library_names"))
        .def("lookup_qos_profiles", &DDS::DomainParticipantFactory::lookup_qos_profiles, py::arg("qos_library_name"), py::arg("pattern"), py::arg("qos_profile_names"))
        .def("qos_library_to_xml", [](DDS::DomainParticipantFactory& self, const char* qos_library_name) -> std::pair<DDS::ReturnCode_t, std::string> {
            const char* result = nullptr;
            DDS::ReturnCode_t ret = self.qos_library_to_xml(qos_library_name, result);
            return std::make_pair(ret, result ? std::string(result) : std::string());
        }, py::arg("qos_library_name"))
        .def("qos_profile_to_xml", [](DDS::DomainParticipantFactory& self, const char* qos_library_name, const char* qos_profile_name) -> std::pair<DDS::ReturnCode_t, std::string> {
            const char* result = nullptr;
            DDS::ReturnCode_t ret = self.qos_profile_to_xml(qos_library_name, qos_profile_name, result);
            return std::make_pair(ret, result ? std::string(result) : std::string());
        }, py::arg("qos_library_name"), py::arg("qos_profile_name"))
        .def("reload_qos_profiles", [](DDS::DomainParticipantFactory& self) -> DDS::ReturnCode_t {
            return self.reload_qos_profiles();
        })
        .def("unload_qos_profiles", [](DDS::DomainParticipantFactory& self) -> void {
            self.unload_qos_profiles();
        })
        .def("__repr__", [](const DDS::DomainParticipantFactory& self) {
            return "<DDS.DomainParticipantFactory>";
        });
    
    // Macro definition
    m.attr("TheParticipantFactory") = py::cast(DDS::DomainParticipantFactory::get_instance());
    
    // Constants - 确保导出为 Python 原生类型
    // STATUS_MASK 常量 - 明确转换为 Python int
    m.attr("STATUS_MASK_NONE") = py::int_(static_cast<int>(DDS::STATUS_MASK_NONE));
    m.attr("STATUS_MASK_ALL") = py::int_(static_cast<int>(DDS::STATUS_MASK_ALL));
    
    // QoS 默认值 - 创建新实例而不是引用全局常量
    m.attr("DOMAINPARTICIPANT_QOS_DEFAULT") = DDS::DomainParticipantQos();
    m.attr("PUBLISHER_QOS_DEFAULT") = DDS::PublisherQos();
    m.attr("SUBSCRIBER_QOS_DEFAULT") = DDS::SubscriberQos();
    m.attr("TOPIC_QOS_DEFAULT") = DDS::TopicQos();
    m.attr("DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT") = DDS::DomainParticipantFactoryQos();
    
    // 其他常量
    m.attr("HANDLE_NIL_NATIVE") = py::cast(DDS::HANDLE_NIL_NATIVE);
    

}