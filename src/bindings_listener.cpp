#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// ZRDDS C++ headers
#include "DataReaderListener.h"
#include "DataWriterListener.h"
#include "DomainParticipantListener.h"
#include "PublisherListener.h"
#include "SubscriberListener.h"
#include "TopicListener.h"
#include "Listener.h"
#include "ReturnCode_t.h"
#include "StatusKindMask.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "DomainParticipant.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "Topic.h"
#include "SampleInfo.h"
#include "ZRDDSCppWrapper.h"

namespace py = pybind11;

// Trampoline class for DataReaderListener
class PyDataReaderListener : public DDS::DataReaderListener {
public:
    using DDS::DataReaderListener::DataReaderListener;

    void on_data_available(DDS::DataReader* reader) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_data_available,
            reader
        );
    }

    void on_requested_deadline_missed(DDS::DataReader* reader, const DDS::RequestedDeadlineMissedStatus& status) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_requested_deadline_missed,
            reader,
            status
        );
    }

    void on_sample_rejected(DDS::DataReader* reader, const DDS::SampleRejectedStatus& status) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_sample_rejected,
            reader,
            status
        );
    }

    void on_liveliness_changed(DDS::DataReader* reader, const DDS::LivelinessChangedStatus& status) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_liveliness_changed,
            reader,
            status
        );
    }

    void on_requested_incompatible_qos(DDS::DataReader* reader, const DDS::RequestedIncompatibleQosStatus& status) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_requested_incompatible_qos,
            reader,
            status
        );
    }

    void on_subscription_matched(DDS::DataReader* reader, const DDS::SubscriptionMatchedStatus& status) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_subscription_matched,
            reader,
            status
        );
    }

    void on_sample_lost(DDS::DataReader* reader, const DDS::SampleLostStatus& status) override {
        PYBIND11_OVERRIDE(
            void,
            DDS::DataReaderListener,
            on_sample_lost,
            reader,
            status
        );
    }
};

// Listener module wrapper
PYBIND11_MODULE(_zrdds_listener, m) {
    m.doc() = "ZRDDS Python Wrapper - Listener Module (Complete Interface)";
    
    // Bind Listener base class
    py::class_<DDS::Listener>(m, "Listener")
        .def("__repr__", [](const DDS::Listener& self) {
            return "<DDS.Listener>";
        });
    
    // Bind DataReaderListener class with trampoline
    py::class_<DDS::DataReaderListener, PyDataReaderListener, DDS::Listener>(m, "DataReaderListener")
        .def(py::init<>())
        .def("on_requested_deadline_missed", [](DDS::DataReaderListener& self, DDS::DataReader* reader, const DDS::RequestedDeadlineMissedStatus& status) {
            self.on_requested_deadline_missed(reader, status);
        }, py::arg("reader"), py::arg("status"), "Callback interface for DDS_REQUESTED_DEADLINE_MISSED_STATUS")
        .def("on_data_available", [](DDS::DataReaderListener& self, DDS::DataReader* reader) {
            self.on_data_available(reader);
        }, py::arg("reader"), "Callback when new samples are stored in the data reader")
        .def("on_data_arrived", [](DDS::DataReaderListener& self, DDS::DataReader* reader, void* sample, const DDS::SampleInfo& info) {
            self.on_data_arrived(reader, sample, info);
        }, py::arg("reader"), py::arg("sample"), py::arg("info"), "Direct notification of data arrival, suitable for best-effort scenarios that don't require data reader caching")
        .def("on_sample_rejected", [](DDS::DataReaderListener& self, DDS::DataReader* reader, const DDS::SampleRejectedStatus& status) {
            self.on_sample_rejected(reader, status);
        }, py::arg("reader"), py::arg("status"), "Callback interface for DDS_SAMPLE_REJECTED_STATUS")
        .def("on_liveliness_changed", [](DDS::DataReaderListener& self, DDS::DataReader* reader, const DDS::LivelinessChangedStatus& status) {
            self.on_liveliness_changed(reader, status);
        }, py::arg("reader"), py::arg("status"), "Callback interface for DDS_LIVELINESS_LOST_STATUS")
        .def("on_requested_incompatible_qos", [](DDS::DataReaderListener& self, DDS::DataReader* reader, const DDS::RequestedIncompatibleQosStatus& status) {
            self.on_requested_incompatible_qos(reader, status);
        }, py::arg("reader"), py::arg("status"), "Callback interface for DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS")
        .def("on_subscription_matched", [](DDS::DataReaderListener& self, DDS::DataReader* reader, const DDS::SubscriptionMatchedStatus& status) {
            self.on_subscription_matched(reader, status);
        }, py::arg("reader"), py::arg("status"), "Callback interface for DDS_SUBSCRIPTION_MATCHED_STATUS")
        .def("on_sample_lost", [](DDS::DataReaderListener& self, DDS::DataReader* reader, const DDS::SampleLostStatus& status) {
            self.on_sample_lost(reader, status);
        }, py::arg("reader"), py::arg("status"), "Callback interface for DDS_SAMPLE_LOST_STATUS")
        .def("__repr__", [](const DDS::DataReaderListener& self) {
            return "<DDS.DataReaderListener>";
        });
    
    // Bind DataWriterListener class
    py::class_<DDS::DataWriterListener, DDS::Listener>(m, "DataWriterListener")
        .def(py::init<>())
        .def("on_liveliness_lost", [](DDS::DataWriterListener& self, DDS::DataWriter* writer, const DDS::LivelinessLostStatus& status) {
            self.on_liveliness_lost(writer, status);
        }, py::arg("writer"), py::arg("status"), "Callback interface for DDS_LIVELINESS_LOST_STATUS")
        .def("on_offered_deadline_missed", [](DDS::DataWriterListener& self, DDS::DataWriter* writer, const DDS::OfferedDeadlineMissedStatus& status) {
            self.on_offered_deadline_missed(writer, status);
        }, py::arg("writer"), py::arg("status"), "Callback interface for DDS_OFFERED_DEADLINE_MISSED_STATUS")
        .def("on_offered_incompatible_qos", [](DDS::DataWriterListener& self, DDS::DataWriter* writer, const DDS::OfferedIncompatibleQosStatus& status) {
            self.on_offered_incompatible_qos(writer, status);
        }, py::arg("writer"), py::arg("status"), "Callback interface for DDS_OFFERED_INCOMPATIBLE_QOS_STATUS")
        .def("on_publication_matched", [](DDS::DataWriterListener& self, DDS::DataWriter* writer, const DDS::PublicationMatchedStatus& status) {
            self.on_publication_matched(writer, status);
        }, py::arg("writer"), py::arg("status"), "Callback interface for DDS_PUBLICATION_MATCHED_STATUS")
        .def("__repr__", [](const DDS::DataWriterListener& self) {
            return "<DDS.DataWriterListener>";
        });
    
    // Bind DomainParticipantListener class
    py::class_<DDS::DomainParticipantListener>(m, "DomainParticipantListener")
        .def(py::init<>())
        .def("on_domain_received", [](DDS::DomainParticipantListener& self, DDS::ULong domainId) {
            self.on_domain_received(domainId);
        }, py::arg("domainId"), "Callback for RTPX protocol processing, see DDS_DomainParticipantQos::domain_destination_addresses")
        .def("__repr__", [](const DDS::DomainParticipantListener& self) {
            return "<DDS.DomainParticipantListener>";
        });
    
    // Bind PublisherListener class
    py::class_<DDS::PublisherListener, DDS::Listener>(m, "PublisherListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::PublisherListener& self) {
            return "<DDS.PublisherListener>";
        });
    
    // Bind SubscriberListener class
    py::class_<DDS::SubscriberListener, DDS::Listener>(m, "SubscriberListener")
        .def(py::init<>())
        .def("on_data_on_readers", [](DDS::SubscriberListener& self, DDS::Subscriber* subscriber) {
            self.on_data_on_readers(subscriber);
        }, py::arg("subscriber"), "Callback for DDS_DATA_ON_READERS_STATUS")
        .def("__repr__", [](const DDS::SubscriberListener& self) {
            return "<DDS.SubscriberListener>";
        });
    
    // Bind TopicListener class
    py::class_<DDS::TopicListener, DDS::Listener>(m, "TopicListener")
        .def(py::init<>())
        .def("on_inconsistent_topic", [](DDS::TopicListener& self, DDS::Topic* topic, const DDS::InconsistentTopicStatus& status) {
            self.on_inconsistent_topic(topic, status);
        }, py::arg("topic"), py::arg("status"), "Callback interface for DDS_INCONSISTENT_TOPIC_STATUS")
        .def("__repr__", [](const DDS::TopicListener& self) {
            return "<DDS.TopicListener>";
        });
    
    // Initialize listener module
    m.def("init", []() {
        return true;
    }, "Initialize Listener DDS module");
    
    // Note: Listener module provides class bindings only
    // Users should create and manage listeners through entity methods
    
    // Cleanup function
    m.def("finalize", []() {
        return true;
    }, "Cleanup Listener DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Listener Module - Complete Interface";
        
        py::list classes;
        classes.append(py::str("Listener"));
        classes.append(py::str("DataReaderListener"));
        classes.append(py::str("DataWriterListener"));
        classes.append(py::str("DomainParticipantListener"));
        classes.append(py::str("PublisherListener"));
        classes.append(py::str("SubscriberListener"));
        classes.append(py::str("TopicListener"));
        info["classes"] = classes;
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        
        py::dict methods;
        
        py::list dataReaderMethods;
        dataReaderMethods.append(py::str("on_requested_deadline_missed"));
        dataReaderMethods.append(py::str("on_data_available"));
        dataReaderMethods.append(py::str("on_data_arrived"));
        dataReaderMethods.append(py::str("on_sample_rejected"));
        dataReaderMethods.append(py::str("on_liveliness_changed"));
        dataReaderMethods.append(py::str("on_requested_incompatible_qos"));
        dataReaderMethods.append(py::str("on_subscription_matched"));
        dataReaderMethods.append(py::str("on_sample_lost"));
        methods["DataReaderListener"] = dataReaderMethods;
        
        py::list dataWriterMethods;
        dataWriterMethods.append(py::str("on_liveliness_lost"));
        dataWriterMethods.append(py::str("on_offered_deadline_missed"));
        dataWriterMethods.append(py::str("on_offered_incompatible_qos"));
        dataWriterMethods.append(py::str("on_publication_matched"));
        methods["DataWriterListener"] = dataWriterMethods;
        
        py::list domainParticipantMethods;
        domainParticipantMethods.append(py::str("on_domain_received"));
        methods["DomainParticipantListener"] = domainParticipantMethods;
        
        py::list subscriberMethods;
        subscriberMethods.append(py::str("on_data_on_readers"));
        methods["SubscriberListener"] = subscriberMethods;
        
        py::list topicMethods;
        topicMethods.append(py::str("on_inconsistent_topic"));
        methods["TopicListener"] = topicMethods;
        info["listener_methods"] = methods;
        
        return info;
    });
}
