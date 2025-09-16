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
#include "PublisherQos.h"
#include "DataWriterQos.h"
#include "PublisherListener.h"
#include "DataWriterListener.h"
#include "LivelinessLostStatus.h"
#include "OfferedDeadlineMissedStatus.h"
#include "OfferedIncompatibleQosStatus.h"
#include "PublicationMatchedStatus.h"
#include "SubscriptionBuiltinTopicData.h"
#include "PublicationSendStatus.h"
#include "ZRDDSCppWrapper.h"
#include "TypeSupport.h"
#include "DomainParticipant.h"
#include "Condition.h"
#include "ShapeType.h"
#include "ShapeTypeDataWriter.h"
#include "DefaultQos.h"


namespace py = pybind11;

// Publish module wrapper
PYBIND11_MODULE(_zrdds_publish, m) {
    m.doc() = "ZRDDS Python Wrapper - Publish Module (Complete Interface)";
    
    // 暴露DDS状态掩码常量 - 明确转换为 Python int 类型
    m.attr("STATUS_MASK_NONE") = py::int_(static_cast<int>(DDS::STATUS_MASK_NONE));
    
    // 暴露DDS默认QoS常量 - 使用 py::none() 作为占位符，避免构造实例时的依赖问题
    m.attr("DOMAINPARTICIPANT_QOS_DEFAULT") = py::none();
    m.attr("TOPIC_QOS_DEFAULT") = py::none();
    m.attr("PUBLISHER_QOS_DEFAULT") = py::none();
    m.attr("DATAWRITER_QOS_DEFAULT") = py::none();
    
    // Bind Publisher class
    py::class_<DDS::Publisher, DDS::DomainEntity, std::unique_ptr<DDS::Publisher, py::nodelete>>(m, "Publisher")
        .def("create_datawriter", &DDS::Publisher::create_datawriter,
             py::arg("topic"), py::arg("qos"), py::arg("listener"), py::arg("mask"),
             "Create DataWriter")
        .def("create_datawriter_with_qos_profile", &DDS::Publisher::create_datawriter_with_qos_profile,
             py::arg("topic"), py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), 
             py::arg("listener"), py::arg("mask"), "Create DataWriter with QoS profile")
        .def("create_datawriter_with_topic_and_qos_profile", &DDS::Publisher::create_datawriter_with_topic_and_qos_profile,
             py::arg("topic_name"), py::arg("type_support"), py::arg("library_name"), py::arg("profile_name"), 
             py::arg("qos_name"), py::arg("listener"), py::arg("mask"), "Create DataWriter with topic name and QoS profile")
        .def("delete_datawriter", &DDS::Publisher::delete_datawriter,
             py::arg("writer"), "Delete DataWriter")
        .def("lookup_datawriter", &DDS::Publisher::lookup_datawriter,
             py::arg("topic_name"), "Lookup DataWriter by topic name")
        .def("suspend_publications", &DDS::Publisher::suspend_publications,
             "Suspend publications")
        .def("resume_publications", &DDS::Publisher::resume_publications,
             "Resume publications")
        .def("begin_coherent_changes", &DDS::Publisher::begin_coherent_changes,
             "Begin coherent changes")
        .def("end_coherent_changes", &DDS::Publisher::end_coherent_changes,
             "End coherent changes")
        .def("wait_for_acknowledgments", &DDS::Publisher::wait_for_acknowledgments,
             py::arg("max_wait"), "Wait for acknowledgments")
        .def("get_participant", &DDS::Publisher::get_participant,
             "Get domain participant of this publisher")
        .def("delete_contained_entities", &DDS::Publisher::delete_contained_entities,
             "Delete all DataWriters contained in Publisher")
        .def("set_default_datawriter_qos", &DDS::Publisher::set_default_datawriter_qos,
             py::arg("qos"), "Set default DataWriter QoS")
        .def("set_default_datawriter_qos_with_profile", &DDS::Publisher::set_default_datawriter_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), "Set default DataWriter QoS with profile")
        .def("get_default_datawriter_qos", [](DDS::Publisher& self) -> py::tuple {
            DDS::DataWriterQos qos;
            DDS::ReturnCode_t ret = self.get_default_datawriter_qos(qos);
            return py::make_tuple(ret, qos);
        }, "Get default DataWriter QoS")
        .def("copy_from_topic_qos", &DDS::Publisher::copy_from_topic_qos,
             py::arg("datawriter_qos"), py::arg("topic_qos"), "Copy from TopicQos to DataWriterQos")
        .def("set_qos", &DDS::Publisher::set_qos,
             py::arg("qos"), "Set publisher QoS")
        .def("set_qos_with_profile", &DDS::Publisher::set_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), "Set publisher QoS with profile")
        .def("get_qos", [](DDS::Publisher& self) -> py::tuple {
            DDS::PublisherQos qos;
            DDS::ReturnCode_t ret = self.get_qos(qos);
            return py::make_tuple(ret, qos);
        }, "Get publisher QoS")
        .def("set_listener", &DDS::Publisher::set_listener,
             py::arg("listener"), py::arg("mask"), "Set publisher listener")
        .def("get_listener", &DDS::Publisher::get_listener,
             "Get publisher listener")
        .def("__repr__", [](const DDS::Publisher& self) {
            return "<DDS.Publisher>";
        });
    
    // DataWriterQos class is bound in bindings_domain.cpp to avoid duplicate registration
    
    // Bind DataWriter class
    py::class_<DDS::DataWriter, DDS::DomainEntity, std::unique_ptr<DDS::DataWriter, py::nodelete>>(m, "DataWriter")
        .def("set_qos_with_profile", &DDS::DataWriter::set_qos_with_profile,
             py::arg("library_name"), py::arg("profile_name"), py::arg("qos_name"), "Set DataWriter QoS with profile")
        .def("get_liveliness_lost_status", [](DDS::DataWriter& self) -> py::tuple {
            DDS::LivelinessLostStatus status;
            DDS::ReturnCode_t ret = self.get_liveliness_lost_status(status);
            return py::make_tuple(ret, status);
        }, "Get LIVELINESS_LOST status associated with DataWriter")
        .def("assert_liveliness", &DDS::DataWriter::assert_liveliness,
             "Assert entity liveliness")
        .def("get_offered_deadline_missed_status", [](DDS::DataWriter& self) -> py::tuple {
            DDS::OfferedDeadlineMissedStatus status;
            DDS::ReturnCode_t ret = self.get_offered_deadline_missed_status(status);
            return py::make_tuple(ret, status);
        }, "Get OFFERED_DEADLINE_MISSED status associated with DataWriter")
        .def("get_offered_incompatible_qos_status", [](DDS::DataWriter& self) -> py::tuple {
            DDS::OfferedIncompatibleQosStatus status;
            DDS::ReturnCode_t ret = self.get_offered_incompatible_qos_status(status);
            return py::make_tuple(ret, status);
        }, "Get INCOMPATIBLE_QOS status associated with DataWriter")
        .def("get_publication_matched_status", [](DDS::DataWriter& self) -> py::tuple {
            DDS::PublicationMatchedStatus status;
            DDS::ReturnCode_t ret = self.get_publication_matched_status(status);
            return py::make_tuple(ret, status);
        }, "Get publication matched status associated with DataWriter")
        .def("get_matched_subscriptions", [](DDS::DataWriter& self) -> py::tuple {
            DDS::InstanceHandleSeq handles;
            DDS::ReturnCode_t ret = self.get_matched_subscriptions(handles);
            return py::make_tuple(ret, handles);
        }, "Get list of matched subscriber handles")
        .def("get_matched_subscription_data", [](DDS::DataWriter& self, const DDS::InstanceHandle_t& handle) -> py::tuple {
            DDS::SubscriptionBuiltinTopicData data;
            DDS::ReturnCode_t ret = self.get_matched_subscription_data(data, handle);
            return py::make_tuple(ret, data);
        }, py::arg("handle"), "Get detailed information of matched subscriber with specified handle")
        .def("wait_for_acknowledgments", &DDS::DataWriter::wait_for_acknowledgments,
             py::arg("max_wait"), "Wait for acknowledgments")
        .def("get_topic", &DDS::DataWriter::get_topic,
             "Get topic associated with this DataWriter")
        .def("get_publisher", &DDS::DataWriter::get_publisher,
             "Get Publisher of this DataWriter")
        .def("set_qos", &DDS::DataWriter::set_qos,
             py::arg("qos"), "Set DataWriter QoS")
        .def("get_qos", [](DDS::DataWriter& self) -> py::tuple {
            DDS::DataWriterQos qos;
            DDS::ReturnCode_t ret = self.get_qos(qos);
            return py::make_tuple(ret, qos);
        }, "Get current DataWriter QoS")
        .def("set_listener", &DDS::DataWriter::set_listener,
             py::arg("listener"), py::arg("mask"), "Set DataWriter listener")
        .def("get_listener", &DDS::DataWriter::get_listener,
             "Get current DataWriter listener")
        .def("get_statuscondition", &DDS::DataWriter::get_statuscondition,
             "Get status condition associated with this DataWriter")
        .def("get_status_changes", &DDS::DataWriter::get_status_changes,
             "Get status changes since last status retrieval")
        .def("enable", &DDS::DataWriter::enable,
             "Manually enable this DataWriter")
        .def("get_instance_handle", &DDS::DataWriter::get_instance_handle,
             "Get unique identifier for this DataWriter")
        .def("get_send_status", [](DDS::DataWriter& self) -> py::tuple {
            DDS::PublicationSendStatusSeq status;
            DDS::ReturnCode_t ret = self.get_send_status(status);
            return py::make_tuple(ret, status);
        }, "Get communication status list with matched subscribers")
        .def("print_send_status", &DDS::DataWriter::print_send_status,
             py::arg("status"), "Print DataWriter communication status list")
        .def("get_send_status_w_handle", [](DDS::DataWriter& self, const DDS::InstanceHandle_t* dst_guid) -> py::tuple {
            DDS::PublicationSendStatus status;
            DDS::ReturnCode_t ret = self.get_send_status_w_handle(status, dst_guid);
            return py::make_tuple(ret, status);
        }, py::arg("dst_guid"), "Get communication status with specified DataWriter")
        .def("flush", &DDS::DataWriter::flush,
             "Manually flush data sending")
        .def("__repr__", [](const DDS::DataWriter& self) {
            return "<DDS.DataWriter>";
        });
    
    // Bind ZRDDSDataWriter template class
    py::class_<DDS::ZRDDSDataWriter<DDS::Bytes>, DDS::DataWriter>(m, "ZRDDSDataWriter")
        .def("register_instance", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance) -> DDS::InstanceHandle_t {
            return self.register_instance(instance);
        }, py::arg("instance"), "Register instance")
        .def("register_instance_w_timestamp", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::Time_t& timestamp) -> DDS::InstanceHandle_t {
            return self.register_instance_w_timestamp(instance, timestamp);
        }, py::arg("instance"), py::arg("timestamp"), "Register instance with timestamp")
        .def("unregister_instance", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.unregister_instance(instance, handle);
        }, py::arg("instance"), py::arg("handle"), "Unregister instance")
        .def("unregister_instance_w_timestamp", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::InstanceHandle_t& handle, const DDS::Time_t& timestamp) -> DDS::ReturnCode_t {
            return self.unregister_instance_w_timestamp(instance, handle, timestamp);
        }, py::arg("instance"), py::arg("handle"), py::arg("timestamp"), "Unregister instance with timestamp")
        .def("get_key_value", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, DDS::Bytes& key_holder, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.get_key_value(key_holder, handle);
        }, py::arg("key_holder"), py::arg("handle"), "Get key value")
        .def("lookup_instance", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance) -> DDS::InstanceHandle_t {
            return self.lookup_instance(instance);
        }, py::arg("instance"), "Lookup instance")
        .def("write", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& data, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.write(data, handle);
        }, py::arg("data"), py::arg("handle"), "Write data")
        .def("write_w_timestamp", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& data, const DDS::InstanceHandle_t& handle, const DDS::Time_t& timestamp) -> DDS::ReturnCode_t {
            return self.write_w_timestamp(data, handle, timestamp);
        }, py::arg("data"), py::arg("handle"), py::arg("timestamp"), "Write data with timestamp")
        .def("write_w_dst", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::InstanceHandle_t& handle, const DDS::Time_t& timestamp, const DDS::InstanceHandle_t& dst_handle) -> DDS::ReturnCode_t {
            return self.write_w_dst(instance, handle, timestamp, dst_handle);
        }, py::arg("instance"), py::arg("handle"), py::arg("timestamp"), py::arg("dst_handle"), "Write data to specific destination with timestamp")
        .def("write_w_dst", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::InstanceHandle_t& handle, const DDS::InstanceHandle_t& dst_handle) -> DDS::ReturnCode_t {
            return self.write_w_dst(instance, handle, dst_handle);
        }, py::arg("instance"), py::arg("handle"), py::arg("dst_handle"), "Write data to specific destination")
        .def("dispose", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::InstanceHandle_t& handle) -> DDS::ReturnCode_t {
            return self.dispose(instance, handle);
        }, py::arg("instance"), py::arg("handle"), "Dispose instance")
        .def("dispose_w_timestamp", [](DDS::ZRDDSDataWriter<DDS::Bytes>& self, const DDS::Bytes& instance, const DDS::InstanceHandle_t& handle, const DDS::Time_t& timestamp) -> DDS::ReturnCode_t {
            return self.dispose_w_timestamp(instance, handle, timestamp);
        }, py::arg("instance"), py::arg("handle"), py::arg("timestamp"), "Dispose instance with timestamp")
        .def("__repr__", [](const DDS::ZRDDSDataWriter<DDS::Bytes>& self) {
            return "<DDS.ZRDDSDataWriter>";
    });
    
    // 模块初始化函数
    m.def("init", []() {
        return true;
    }, "Initialize Publish DDS module");
    
    m.def("finalize", []() {
        return true;
    }, "Cleanup Publish DDS module");
}
