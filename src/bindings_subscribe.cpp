#define _ZRDDSCPPINTERFACE
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
#include "Topic.h"
#include "SubscriberQos.h"
#include "DataReaderQos.h"
#include "SampleStateKind.h"
#include "ViewStateKind.h"
#include "InstanceStateKind.h"
#include "ZRSequence.h"
#include "TopicDescription.h"
#include "TypeSupport.h"
#include "DataReaderListener.h"
#include "SubscriberListener.h"
#include "LivelinessChangedStatus.h"
#include "RequestedDeadlineMissedStatus.h"
#include "RequestedIncompatibleQosStatus.h"
#include "SampleLostStatus.h"
#include "SampleRejectedStatus.h"
#include "SubscriptionMatchedStatus.h"
#include "PublicationBuiltinTopicData.h"
#include "Duration_t.h"
#include "Condition.h"
#include "DomainParticipant.h"
#include "ZRBuiltinTypesDataReader.h"
#include "ZRDDSCppWrapper.h"
#include "SampleInfo.h"

namespace py = pybind11;

// Subscribe module wrapper
PYBIND11_MODULE(_zrdds_subscribe, m) {
    m.doc() = "ZRDDS Python Wrapper - Subscribe Module ";
    
    // Bind Subscriber class with nodelete policy (protected destructor)
    py::class_<DDS::Subscriber, DDS::DomainEntity, std::unique_ptr<DDS::Subscriber, py::nodelete>>(m, "Subscriber")
        .def("create_datareader", [](DDS::Subscriber& self, DDS::TopicDescription* topic, const DDS::DataReaderQos& qos, DDS::DataReaderListener* listener, DDS::StatusKindMask mask) -> DDS::DataReader* {
            return self.create_datareader(topic, qos, listener, mask);
        }, py::arg("topic"), py::arg("qos"), py::arg("listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("create_datareader_with_qos_profile", [](DDS::Subscriber& self, DDS::TopicDescription* topic, const char* library_name, const char* profile_name, const char* qos_name, DDS::DataReaderListener* listener, DDS::StatusKindMask mask) -> DDS::DataReader* {
            return self.create_datareader_with_qos_profile(topic, library_name, profile_name, qos_name, listener, mask);
        }, py::arg("topic"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), py::arg("listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("create_datareader_with_topic_and_qos_profile", [](DDS::Subscriber& self, const char* topic_name, DDS::TypeSupport* type_support, const char* library_name, const char* profile_name, const char* qos_name, DDS::DataReaderListener* listener, DDS::StatusKindMask mask) -> DDS::DataReader* {
            return self.create_datareader_with_topic_and_qos_profile(topic_name, type_support, library_name, profile_name, qos_name, listener, mask);
        }, py::arg("topic_name"), py::arg("type_support"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), py::arg("listener") = nullptr, py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("delete_datareader", [](DDS::Subscriber& self, DDS::DataReader* datareader) -> DDS::ReturnCode_t {
            return self.delete_datareader(datareader);
        }, py::arg("datareader"))
        .def("lookup_datareader", [](DDS::Subscriber& self, const char* topic_name) -> DDS::DataReader* {
            return self.lookup_datareader(topic_name);
        }, py::arg("topic_name"))
        .def("begin_access", [](DDS::Subscriber& self) -> DDS::ReturnCode_t {
            return self.begin_access();
        })
        .def("end_access", [](DDS::Subscriber& self) -> DDS::ReturnCode_t {
            return self.end_access();
        })
        .def("get_datareaders", [](DDS::Subscriber& self, DDS::DataReaderSeq& datareaders, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) -> DDS::ReturnCode_t {
            return self.get_datareaders(datareaders, sample_states, view_states, instance_states);
        }, py::arg("datareaders"), py::arg("sample_states"), py::arg("view_states"), py::arg("instance_states"))
        .def("notify_datareaders", [](DDS::Subscriber& self) -> DDS::ReturnCode_t {
            return self.notify_datareaders();
        })
        .def("get_participant", [](DDS::Subscriber& self) -> DDS::DomainParticipant* {
            return self.get_participant();
        })
        .def("delete_contained_entities", [](DDS::Subscriber& self) -> DDS::ReturnCode_t {
            return self.delete_contained_entities();
        })
        .def("get_default_datareader_qos", [](DDS::Subscriber& self) -> py::tuple {
            DDS::DataReaderQos qos;
            DDS::ReturnCode_t ret = self.get_default_datareader_qos(qos);
            return py::make_tuple(ret, qos);
        }, "Get default DataReader QoS")
        .def("set_default_datareader_qos", [](DDS::Subscriber& self, const DDS::DataReaderQos& qos) -> DDS::ReturnCode_t {
            return self.set_default_datareader_qos(qos);
        }, py::arg("qos"))
        .def("set_default_datareader_qos_with_profile", [](DDS::Subscriber& self, const char* library_name, const char* profile_name, const char* qos_name) -> DDS::ReturnCode_t {
            return self.set_default_datareader_qos_with_profile(library_name, profile_name, qos_name);
        }, py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("copy_from_topic_qos", [](DDS::Subscriber& self, DDS::DataReaderQos& datareader_qos, const DDS::TopicQos& topic_qos) -> DDS::ReturnCode_t {
            return self.copy_from_topic_qos(datareader_qos, topic_qos);
        }, py::arg("datareader_qos"), py::arg("topic_qos"))
        .def("get_qos", [](DDS::Subscriber& self, DDS::SubscriberQos& qos) -> DDS::ReturnCode_t {
            return self.get_qos(qos);
        }, py::arg("qos"))
        .def("set_qos", [](DDS::Subscriber& self, const DDS::SubscriberQos& qos) -> DDS::ReturnCode_t {
            return self.set_qos(qos);
        }, py::arg("qos"))
        .def("set_qos_with_profile", [](DDS::Subscriber& self, const char* library_name, const char* profile_name, const char* qos_name) -> DDS::ReturnCode_t {
            return self.set_qos_with_profile(library_name, profile_name, qos_name);
        }, py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("get_listener", [](DDS::Subscriber& self) -> DDS::SubscriberListener* {
            return self.get_listener();
        })
        .def("set_listener", [](DDS::Subscriber& self, DDS::SubscriberListener* listener, DDS::StatusKindMask mask) -> DDS::ReturnCode_t {
            return self.set_listener(listener, mask);
        }, py::arg("listener"), py::arg("mask") = DDS::STATUS_MASK_NONE)

        .def("__repr__", [](const DDS::Subscriber& self) {
            return "<DDS.Subscriber>";
        });
    
    // Bind DataReaderQos class - 补充缺失的类绑定
    py::class_<DDS::DataReaderQos>(m, "DataReaderQos")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DataReaderQos& self) {
            return "<DDS.DataReaderQos>";
        });
    
    // Bind DataReader class with nodelete policy (protected destructor)
    py::class_<DDS::DataReader, DDS::DomainEntity, std::unique_ptr<DDS::DataReader, py::nodelete>>(m, "DataReader")
        .def("set_qos_with_profile", [](DDS::DataReader& self, const char* library_name, const char* profile_name, const char* qos_name) -> DDS::ReturnCode_t {
            return self.set_qos_with_profile(library_name, profile_name, qos_name);
        }, py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"))
        .def("create_readcondition", [](DDS::DataReader& self, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) -> DDS::ReadCondition* {
            return self.create_readcondition(sample_states, view_states, instance_states);
        }, py::arg("sample_states"), py::arg("view_states"), py::arg("instance_states"))
        .def("delete_readcondition", [](DDS::DataReader& self, DDS::ReadCondition* condition) -> DDS::ReturnCode_t {
            return self.delete_readcondition(condition);
        }, py::arg("condition"))
        .def("delete_contained_entities", [](DDS::DataReader& self) -> DDS::ReturnCode_t {
            return self.delete_contained_entities();
        })
        .def("wait_for_historical_data", [](DDS::DataReader& self, const DDS::Duration_t& max_wait) -> DDS::ReturnCode_t {
            return self.wait_for_historical_data(max_wait);
        }, py::arg("max_wait"))
        .def("get_liveliness_changed_status", [](DDS::DataReader& self, DDS::LivelinessChangedStatus& status) -> DDS::ReturnCode_t {
            return self.get_liveliness_changed_status(status);
        }, py::arg("status"))
        .def("get_requested_deadline_missed_status", [](DDS::DataReader& self, DDS::RequestedDeadlineMissedStatus& status) -> DDS::ReturnCode_t {
            return self.get_requested_deadline_missed_status(status);
        }, py::arg("status"))
        .def("get_requested_incompatible_qos_status", [](DDS::DataReader& self, DDS::RequestedIncompatibleQosStatus& status) -> DDS::ReturnCode_t {
            return self.get_requested_incompatible_qos_status(status);
        }, py::arg("status"))
        .def("get_sample_lost_status", [](DDS::DataReader& self, DDS::SampleLostStatus& status) -> DDS::ReturnCode_t {
            return self.get_sample_lost_status(status);
        }, py::arg("status"))
        .def("get_sample_rejected_status", [](DDS::DataReader& self, DDS::SampleRejectedStatus& status) -> DDS::ReturnCode_t {
            return self.get_sample_rejected_status(status);
        }, py::arg("status"))
        .def("get_subscription_matched_status", [](DDS::DataReader& self, DDS::SubscriptionMatchedStatus& status) -> DDS::ReturnCode_t {
            return self.get_subscription_matched_status(status);
        }, py::arg("status"))
        .def("get_topicdescription", [](DDS::DataReader& self) -> DDS::TopicDescription* {
            return self.get_topicdescription();
        })
        .def("get_subscriber", [](DDS::DataReader& self) -> DDS::Subscriber* {
            return self.get_subscriber();
        })
        .def("get_matched_publication_data", [](DDS::DataReader& self, DDS::PublicationBuiltinTopicData& publication_data, const DDS::InstanceHandle_t& publication_handle) -> DDS::ReturnCode_t {
            return self.get_matched_publication_data(publication_data, publication_handle);
        }, py::arg("publication_data"), py::arg("publication_handle"))
        .def("get_matched_publications", [](DDS::DataReader& self, DDS::InstanceHandleSeq& publication_handles) -> DDS::ReturnCode_t {
            return self.get_matched_publications(publication_handles);
        }, py::arg("publication_handles"))
        .def("set_qos", [](DDS::DataReader& self, const DDS::DataReaderQos& qos) -> DDS::ReturnCode_t {
            return self.set_qos(qos);
        }, py::arg("qos"))
        .def("get_qos", [](DDS::DataReader& self, DDS::DataReaderQos& qos) -> DDS::ReturnCode_t {
            return self.get_qos(qos);
        }, py::arg("qos"))
        .def("set_listener", [](DDS::DataReader& self, DDS::DataReaderListener* listener, DDS::StatusKindMask mask) -> DDS::ReturnCode_t {
            return self.set_listener(listener, mask);
        }, py::arg("listener"), py::arg("mask") = DDS::STATUS_MASK_NONE)
        .def("get_listener", [](DDS::DataReader& self) -> DDS::DataReaderListener* {
            return self.get_listener();
        })
        .def("get_statuscondition", [](DDS::DataReader& self) -> DDS::StatusCondition* {
            return self.get_statuscondition();
        })
        .def("get_status_changes", [](DDS::DataReader& self) -> DDS::StatusKindMask {
            return self.get_status_changes();
        })
        .def("get_instance_handle", [](DDS::DataReader& self) -> DDS::InstanceHandle_t {
            return self.get_instance_handle();
        })
        .def("enable", [](DDS::DataReader& self) -> DDS::ReturnCode_t {
            return self.enable();
        })
        .def("get_data_instance", [](DDS::DataReader& self, DDS::InstanceHandleSeq& data_seq, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.get_data_instance(data_seq, sample_mask, view_mask, instance_mask);
        }, py::arg("data_seq"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))

        .def("__repr__", [](const DDS::DataReader& self) {
            return "<DDS.DataReader>";
        });
    
    // Bind ReadCondition class
    py::class_<DDS::ReadCondition, DDS::Condition>(m, "ReadCondition")
        .def("get_sample_state_mask", [](DDS::ReadCondition& self) -> DDS::SampleStateMask {
            return self.get_sample_state_mask();
        })
        .def("get_view_state_mask", [](DDS::ReadCondition& self) -> DDS::ViewStateMask {
            return self.get_view_state_mask();
        })
        .def("get_instance_state_mask", [](DDS::ReadCondition& self) -> DDS::InstanceStateMask {
            return self.get_instance_state_mask();
        })
        .def("get_datareader", [](DDS::ReadCondition& self) -> DDS::DataReader* {
            return self.get_datareader();
        })
        .def("__repr__", [](const DDS::ReadCondition& self) {
            return "<DDS.ReadCondition>";
        });
    

    
    // Bind pre-defined BytesDataReader (ZRDDS provides this for built-in types)
    py::class_<DDS::BytesDataReader, DDS::DataReader, std::unique_ptr<DDS::BytesDataReader, py::nodelete>>(m, "BytesDataReader")
        .def("read_next_sample", &DDS::BytesDataReader::read_next_sample, 
             py::arg("data_value"), py::arg("sample_info"))
        .def("take_next_sample", &DDS::BytesDataReader::take_next_sample, 
             py::arg("data_value"), py::arg("sample_info"))
        .def("read", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.read(data_values, sample_infos, max_samples, sample_mask, view_mask, instance_mask);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))
        .def("take", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.take(data_values, sample_infos, max_samples, sample_mask, view_mask, instance_mask);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))
        .def("read_instance", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, const DDS::InstanceHandle_t& handle, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.read_instance(data_values, sample_infos, max_samples, handle, sample_mask, view_mask, instance_mask);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("handle"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))
        .def("take_instance", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, const DDS::InstanceHandle_t& handle, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.take_instance(data_values, sample_infos, max_samples, handle, sample_mask, view_mask, instance_mask);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("handle"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))
        .def("read_next_instance", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, const DDS::InstanceHandle_t& previous_handle, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.read_next_instance(data_values, sample_infos, max_samples, previous_handle, sample_mask, view_mask, instance_mask);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("previous_handle"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))
        .def("take_next_instance", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, const DDS::InstanceHandle_t& previous_handle, DDS::SampleStateMask sample_mask, DDS::ViewStateMask view_mask, DDS::InstanceStateMask instance_mask) -> DDS::ReturnCode_t {
            return self.take_next_instance(data_values, sample_infos, max_samples, previous_handle, sample_mask, view_mask, instance_mask);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("previous_handle"), py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"))
        .def("read_next_instance_w_condition", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, const DDS::InstanceHandle_t& previous_handle, DDS::ReadCondition* condition) -> DDS::ReturnCode_t {
            return self.read_next_instance_w_condition(data_values, sample_infos, max_samples, previous_handle, condition);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("previous_handle"), py::arg("condition"))
        .def("take_next_instance_w_condition", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, const DDS::InstanceHandle_t& previous_handle, DDS::ReadCondition* condition) -> DDS::ReturnCode_t {
            return self.take_next_instance_w_condition(data_values, sample_infos, max_samples, previous_handle, condition);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("previous_handle"), py::arg("condition"))
        .def("read_w_condition", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, DDS::ReadCondition* condition) -> DDS::ReturnCode_t {
            return self.read_w_condition(data_values, sample_infos, max_samples, condition);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("condition"))
        .def("take_w_condition", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos, DDS::Long max_samples, DDS::ReadCondition* condition) -> DDS::ReturnCode_t {
            return self.take_w_condition(data_values, sample_infos, max_samples, condition);
        }, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"), py::arg("condition"))
        .def("return_loan", [](DDS::BytesDataReader& self, DDS::BytesSeq& data_values, DDS::SampleInfoSeq& sample_infos) -> DDS::ReturnCode_t {
            return self.return_loan(data_values, sample_infos);
        }, py::arg("data_values"), py::arg("sample_infos"))
        .def("get_key_value", &DDS::BytesDataReader::get_key_value, 
             py::arg("key_holder"), py::arg("handle"))
        .def("lookup_instance", &DDS::BytesDataReader::lookup_instance, 
             py::arg("instance"))
        .def("__repr__", [](const DDS::BytesDataReader& self) {
            return "<DDS.BytesDataReader>";
        });
    
    // Bind SubscriberSeq struct
    py::class_<DDS::SubscriberSeq>(m, "SubscriberSeq")
        .def(py::init<>())
        .def("__len__", [](const DDS::SubscriberSeq& self) {
            return SubscriberSeq_get_length(&self);
        })
        .def("__getitem__", [](const DDS::SubscriberSeq& self, DDS::Long index) -> DDS::Subscriber* {
            if (index >= 0 && index < SubscriberSeq_get_length(&self)) {
                DDS::SubscriberPtr* ptr = SubscriberSeq_get_reference(&self, index);
                return ptr ? *ptr : nullptr;
            }
            throw py::index_error("Index out of range");
        })
        .def("__repr__", [](const DDS::SubscriberSeq& self) {
            return "<DDS.SubscriberSeq>";
        });
    
    // Type aliases
    m.attr("SubscriberPtr") = py::type::of<DDS::Subscriber>();
    
    // Constants
    m.attr("ANY_SAMPLE_STATE") = DDS::ANY_SAMPLE_STATE;
    m.attr("READ_SAMPLE_STATE") = DDS::READ_SAMPLE_STATE;
    m.attr("NOT_READ_SAMPLE_STATE") = DDS::NOT_READ_SAMPLE_STATE;
    m.attr("ANY_VIEW_STATE") = DDS::ANY_VIEW_STATE;
    m.attr("NEW_VIEW_STATE") = DDS::NEW_VIEW_STATE;
    m.attr("NOT_NEW_VIEW_STATE") = DDS::NOT_NEW_VIEW_STATE;
    m.attr("ANY_INSTANCE_STATE") = DDS::ANY_INSTANCE_STATE;
    m.attr("ALIVE_INSTANCE_STATE") = DDS::ALIVE_INSTANCE_STATE;
    m.attr("NOT_ALIVE_DISPOSED_INSTANCE_STATE") = DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE;
    m.attr("NOT_ALIVE_NO_WRITERS_INSTANCE_STATE") = DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE;
    
    // Initialize subscribe module
    m.def("init", []() {
        return true;
    }, "Initialize Subscribe DDS module");
    
    // Cleanup function
    m.def("finalize", []() {
        return true;
    }, "Cleanup Subscribe DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Subscribe Module - Complete Interface";
        
        py::list classes;
        classes.append(py::str("Subscriber"));
        classes.append(py::str("DataReader"));
        classes.append(py::str("ReadCondition"));
        classes.append(py::str("BytesDataReader"));
        classes.append(py::str("SubscriberSeq"));
        info["classes"] = classes;
        
        py::list subscriber_methods;
        subscriber_methods.append(py::str("create_datareader"));
        subscriber_methods.append(py::str("create_datareader_with_qos_profile"));
        subscriber_methods.append(py::str("create_datareader_with_topic_and_qos_profile"));
        subscriber_methods.append(py::str("delete_datareader"));
        subscriber_methods.append(py::str("lookup_datareader"));
        subscriber_methods.append(py::str("begin_access"));
        subscriber_methods.append(py::str("end_access"));
        subscriber_methods.append(py::str("get_datareaders"));
        subscriber_methods.append(py::str("notify_datareaders"));
        subscriber_methods.append(py::str("get_participant"));
        subscriber_methods.append(py::str("delete_contained_entities"));
        subscriber_methods.append(py::str("get_default_datareader_qos"));
        subscriber_methods.append(py::str("set_default_datareader_qos"));
        subscriber_methods.append(py::str("set_default_datareader_qos_with_profile"));
        subscriber_methods.append(py::str("copy_from_topic_qos"));
        subscriber_methods.append(py::str("get_qos"));
        subscriber_methods.append(py::str("set_qos"));
        subscriber_methods.append(py::str("set_qos_with_profile"));
        subscriber_methods.append(py::str("get_listener"));
        subscriber_methods.append(py::str("set_listener"));

        info["subscriber_methods"] = subscriber_methods;
        
        py::list datareader_methods;
        datareader_methods.append(py::str("set_qos_with_profile"));
        datareader_methods.append(py::str("create_readcondition"));
        datareader_methods.append(py::str("delete_readcondition"));
        datareader_methods.append(py::str("delete_contained_entities"));
        datareader_methods.append(py::str("wait_for_historical_data"));
        datareader_methods.append(py::str("get_liveliness_changed_status"));
        datareader_methods.append(py::str("get_requested_deadline_missed_status"));
        datareader_methods.append(py::str("get_requested_incompatible_qos_status"));
        datareader_methods.append(py::str("get_sample_lost_status"));
        datareader_methods.append(py::str("get_sample_rejected_status"));
        datareader_methods.append(py::str("get_subscription_matched_status"));
        datareader_methods.append(py::str("get_topicdescription"));
        datareader_methods.append(py::str("get_subscriber"));
        datareader_methods.append(py::str("get_matched_publication_data"));
        datareader_methods.append(py::str("get_matched_publications"));
        datareader_methods.append(py::str("set_qos"));
        datareader_methods.append(py::str("get_qos"));
        datareader_methods.append(py::str("set_listener"));
        datareader_methods.append(py::str("get_listener"));
        datareader_methods.append(py::str("get_statuscondition"));
        datareader_methods.append(py::str("get_status_changes"));
        datareader_methods.append(py::str("get_instance_handle"));
        datareader_methods.append(py::str("enable"));
        datareader_methods.append(py::str("get_data_instance"));

        info["datareader_methods"] = datareader_methods;
        
        py::list readcondition_methods;
        readcondition_methods.append(py::str("get_sample_state_mask"));
        readcondition_methods.append(py::str("get_view_state_mask"));
        readcondition_methods.append(py::str("get_instance_state_mask"));
        readcondition_methods.append(py::str("get_datareader"));
        info["readcondition_methods"] = readcondition_methods;
        
        py::list querycondition_methods;

        
        py::list bytes_datareader_methods;
        bytes_datareader_methods.append(py::str("read_next_sample"));
        bytes_datareader_methods.append(py::str("take_next_sample"));
        bytes_datareader_methods.append(py::str("read"));
        bytes_datareader_methods.append(py::str("take"));
        bytes_datareader_methods.append(py::str("read_instance"));
        bytes_datareader_methods.append(py::str("take_instance"));
        bytes_datareader_methods.append(py::str("read_next_instance"));
        bytes_datareader_methods.append(py::str("take_next_instance"));
        bytes_datareader_methods.append(py::str("read_next_instance_w_condition"));
        bytes_datareader_methods.append(py::str("take_next_instance_w_condition"));
        bytes_datareader_methods.append(py::str("read_w_condition"));
        bytes_datareader_methods.append(py::str("take_w_condition"));
        bytes_datareader_methods.append(py::str("return_loan"));
        bytes_datareader_methods.append(py::str("get_key_value"));
        bytes_datareader_methods.append(py::str("lookup_instance"));
        info["bytes_datareader_methods"] = bytes_datareader_methods;
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("finalize"));
        functions.append(py::str("read_data"));
        functions.append(py::str("get_api_info"));
        info["main_functions"] = functions;
        
        return info;
    });
}
