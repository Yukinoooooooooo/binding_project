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
#include "Entity.h"
#include "ReturnCode_t.h"
#include "StatusKindMask.h"
#include "ZRDDSCppWrapper.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "DomainParticipant.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "Topic.h"

namespace py = pybind11;

// Simple Listener DDS Manager - like your simple DDS module
struct ListenerDDSManager {
    static DDS::DataReaderListener* datareader_listener;
    static DDS::DataWriterListener* datawriter_listener;
    static DDS::DomainParticipantListener* participant_listener;
    static DDS::PublisherListener* publisher_listener;
    static DDS::SubscriberListener* subscriber_listener;
    static DDS::TopicListener* topic_listener;
    
    static void cleanup() {
        if (datareader_listener) {
            delete datareader_listener;
            datareader_listener = nullptr;
        }
        if (datawriter_listener) {
            delete datawriter_listener;
            datawriter_listener = nullptr;
        }
        if (participant_listener) {
            delete participant_listener;
            participant_listener = nullptr;
        }
        if (publisher_listener) {
            delete publisher_listener;
            publisher_listener = nullptr;
        }
        if (subscriber_listener) {
            delete subscriber_listener;
            subscriber_listener = nullptr;
        }
        if (topic_listener) {
            delete topic_listener;
            topic_listener = nullptr;
        }
    }
};

// Initialize static members
DDS::DataReaderListener* ListenerDDSManager::datareader_listener = nullptr;
DDS::DataWriterListener* ListenerDDSManager::datawriter_listener = nullptr;
DDS::DomainParticipantListener* ListenerDDSManager::participant_listener = nullptr;
DDS::PublisherListener* ListenerDDSManager::publisher_listener = nullptr;
DDS::SubscriberListener* ListenerDDSManager::subscriber_listener = nullptr;
DDS::TopicListener* ListenerDDSManager::topic_listener = nullptr;

// Listener module wrapper
PYBIND11_MODULE(_zrdds_listener, m) {
    m.doc() = "ZRDDS Python Wrapper - Listener Module (Simple Direct Interface)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Listener Module - Simple Direct Interface!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Listener Module v3.0.0 - Simple Direct Implementation";
    });
    
    // Initialize listener module
    m.def("init", []() {
        ListenerDDSManager::cleanup();
        return true;
    }, "Initialize Listener DDS module");
    
    // Create DataReaderListener - direct creation
    m.def("create_datareader_listener", []() -> bool {
        if (ListenerDDSManager::datareader_listener) {
            return true; // Already exists
        }
        
        // Create a simple DataReaderListener
        ListenerDDSManager::datareader_listener = new DDS::DataReaderListener();
        return (ListenerDDSManager::datareader_listener != nullptr);
    }, "Create DataReaderListener");
    
    m.def("delete_datareader_listener", []() -> bool {
        if (ListenerDDSManager::datareader_listener) {
            delete ListenerDDSManager::datareader_listener;
            ListenerDDSManager::datareader_listener = nullptr;
            return true;
        }
        return false;
    }, "Delete DataReaderListener");
    
    // Create DataWriterListener - direct creation
    m.def("create_datawriter_listener", []() -> bool {
        if (ListenerDDSManager::datawriter_listener) {
            return true; // Already exists
        }
        
        // Create a simple DataWriterListener
        ListenerDDSManager::datawriter_listener = new DDS::DataWriterListener();
        return (ListenerDDSManager::datawriter_listener != nullptr);
    }, "Create DataWriterListener");
    
    m.def("delete_datawriter_listener", []() -> bool {
        if (ListenerDDSManager::datawriter_listener) {
            delete ListenerDDSManager::datawriter_listener;
            ListenerDDSManager::datawriter_listener = nullptr;
            return true;
        }
        return false;
    }, "Delete DataWriterListener");
    
    // Create DomainParticipantListener - direct creation
    m.def("create_participant_listener", []() -> bool {
        if (ListenerDDSManager::participant_listener) {
            return true; // Already exists
        }
        
        // Create a simple DomainParticipantListener
        ListenerDDSManager::participant_listener = new DDS::DomainParticipantListener();
        return (ListenerDDSManager::participant_listener != nullptr);
    }, "Create DomainParticipantListener");
    
    m.def("delete_participant_listener", []() -> bool {
        if (ListenerDDSManager::participant_listener) {
            delete ListenerDDSManager::participant_listener;
            ListenerDDSManager::participant_listener = nullptr;
            return true;
        }
        return false;
    }, "Delete DomainParticipantListener");
    
    // Create PublisherListener - direct creation
    m.def("create_publisher_listener", []() -> bool {
        if (ListenerDDSManager::publisher_listener) {
            return true; // Already exists
        }
        
        // Create a simple PublisherListener
        ListenerDDSManager::publisher_listener = new DDS::PublisherListener();
        return (ListenerDDSManager::publisher_listener != nullptr);
    }, "Create PublisherListener");
    
    m.def("delete_publisher_listener", []() -> bool {
        if (ListenerDDSManager::publisher_listener) {
            delete ListenerDDSManager::publisher_listener;
            ListenerDDSManager::publisher_listener = nullptr;
            return true;
        }
        return false;
    }, "Delete PublisherListener");
    
    // Create SubscriberListener - direct creation
    m.def("create_subscriber_listener", []() -> bool {
        if (ListenerDDSManager::subscriber_listener) {
            return true; // Already exists
        }
        
        // Create a simple SubscriberListener
        ListenerDDSManager::subscriber_listener = new DDS::SubscriberListener();
        return (ListenerDDSManager::subscriber_listener != nullptr);
    }, "Create SubscriberListener");
    
    m.def("delete_subscriber_listener", []() -> bool {
        if (ListenerDDSManager::subscriber_listener) {
            delete ListenerDDSManager::subscriber_listener;
            ListenerDDSManager::subscriber_listener = nullptr;
            return true;
        }
        return false;
    }, "Delete SubscriberListener");
    
    // Create TopicListener - direct creation
    m.def("create_topic_listener", []() -> bool {
        if (ListenerDDSManager::topic_listener) {
            return true; // Already exists
        }
        
        // Create a simple TopicListener
        ListenerDDSManager::topic_listener = new DDS::TopicListener();
        return (ListenerDDSManager::topic_listener != nullptr);
    }, "Create TopicListener");
    
    m.def("delete_topic_listener", []() -> bool {
        if (ListenerDDSManager::topic_listener) {
            delete ListenerDDSManager::topic_listener;
            ListenerDDSManager::topic_listener = nullptr;
            return true;
        }
        return false;
    }, "Delete TopicListener");
    
    // Check if entities exist
    m.def("datareader_listener_exists", []() -> bool {
        return (ListenerDDSManager::datareader_listener != nullptr);
    }, "Check if datareader listener exists");
    
    m.def("datawriter_listener_exists", []() -> bool {
        return (ListenerDDSManager::datawriter_listener != nullptr);
    }, "Check if datawriter listener exists");
    
    m.def("participant_listener_exists", []() -> bool {
        return (ListenerDDSManager::participant_listener != nullptr);
    }, "Check if participant listener exists");
    
    m.def("publisher_listener_exists", []() -> bool {
        return (ListenerDDSManager::publisher_listener != nullptr);
    }, "Check if publisher listener exists");
    
    m.def("subscriber_listener_exists", []() -> bool {
        return (ListenerDDSManager::subscriber_listener != nullptr);
    }, "Check if subscriber listener exists");
    
    m.def("topic_listener_exists", []() -> bool {
        return (ListenerDDSManager::topic_listener != nullptr);
    }, "Check if topic listener exists");
    
    // Cleanup function
    m.def("finalize", []() {
        ListenerDDSManager::cleanup();
        return true;
    }, "Cleanup Listener DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Listener Module - Simple Direct Interface";
        info["datareader_listener_exists"] = (ListenerDDSManager::datareader_listener != nullptr);
        info["datawriter_listener_exists"] = (ListenerDDSManager::datawriter_listener != nullptr);
        info["participant_listener_exists"] = (ListenerDDSManager::participant_listener != nullptr);
        info["publisher_listener_exists"] = (ListenerDDSManager::publisher_listener != nullptr);
        info["subscriber_listener_exists"] = (ListenerDDSManager::subscriber_listener != nullptr);
        info["topic_listener_exists"] = (ListenerDDSManager::topic_listener != nullptr);
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_datareader_listener"));
        functions.append(py::str("delete_datareader_listener"));
        functions.append(py::str("create_datawriter_listener"));
        functions.append(py::str("delete_datawriter_listener"));
        functions.append(py::str("create_participant_listener"));
        functions.append(py::str("delete_participant_listener"));
        functions.append(py::str("create_publisher_listener"));
        functions.append(py::str("delete_publisher_listener"));
        functions.append(py::str("create_subscriber_listener"));
        functions.append(py::str("delete_subscriber_listener"));
        functions.append(py::str("create_topic_listener"));
        functions.append(py::str("delete_topic_listener"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
