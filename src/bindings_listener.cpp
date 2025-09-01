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

// Global storage for listener DDS entities
struct ListenerDDSManager {
    static std::map<int, DDS::Listener*> listeners;
    static std::map<int, DDS::DataReaderListener*> datareader_listeners;
    static std::map<int, DDS::DataWriterListener*> datawriter_listeners;
    static std::map<int, DDS::DomainParticipantListener*> participant_listeners;
    static std::map<int, DDS::PublisherListener*> publisher_listeners;
    static std::map<int, DDS::SubscriberListener*> subscriber_listeners;
    static std::map<int, DDS::TopicListener*> topic_listeners;
    
    static int next_id;
    
    static int generate_id() { return ++next_id; }
    
    static void cleanup() {
        // Clean up all listener types
        for (auto& pair : listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : datareader_listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : datawriter_listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : participant_listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : publisher_listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : subscriber_listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : topic_listeners) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clear all maps
        listeners.clear();
        datareader_listeners.clear();
        datawriter_listeners.clear();
        participant_listeners.clear();
        publisher_listeners.clear();
        subscriber_listeners.clear();
        topic_listeners.clear();
    }
};

std::map<int, DDS::Listener*> ListenerDDSManager::listeners;
std::map<int, DDS::DataReaderListener*> ListenerDDSManager::datareader_listeners;
std::map<int, DDS::DataWriterListener*> ListenerDDSManager::datawriter_listeners;
std::map<int, DDS::DomainParticipantListener*> ListenerDDSManager::participant_listeners;
std::map<int, DDS::PublisherListener*> ListenerDDSManager::publisher_listeners;
std::map<int, DDS::SubscriberListener*> ListenerDDSManager::subscriber_listeners;
std::map<int, DDS::TopicListener*> ListenerDDSManager::topic_listeners;
int ListenerDDSManager::next_id = 5000;

// Listener module wrapper
PYBIND11_MODULE(_zrdds_listener, m) {
    m.doc() = "ZRDDS Python Wrapper - Listener Module (C++ Interface with Factory Pattern)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Listener Module with Factory Pattern!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Listener Module v2.0.0 - Factory Pattern Implementation";
    });
    
    // Initialize listener module
    m.def("init", []() {
        // Clean up any existing entities
        ListenerDDSManager::cleanup();
        return true;
    }, "Initialize Listener DDS module");
    
    // Factory functions for base Listener
    m.def("create_listener", []() -> int {
        DDS::Listener* listener = new DDS::Listener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create base Listener and return ID");
    
    m.def("delete_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::listeners.find(listener_id);
        if (it != ListenerDDSManager::listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete base Listener by ID");
    
    // Factory functions for DataReaderListener
    m.def("create_datareader_listener", []() -> int {
        DDS::DataReaderListener* listener = new DDS::DataReaderListener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::datareader_listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create DataReaderListener and return ID");
    
    m.def("delete_datareader_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::datareader_listeners.find(listener_id);
        if (it != ListenerDDSManager::datareader_listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::datareader_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete DataReaderListener by ID");
    
    // Factory functions for DataWriterListener
    m.def("create_datawriter_listener", []() -> int {
        DDS::DataWriterListener* listener = new DDS::DataWriterListener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::datawriter_listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create DataWriterListener and return ID");

    // Get raw DataWriterListener pointer by id for integration
    m.def("get_datawriter_listener_ptr", [](int listener_id) -> py::object {
        auto it = ListenerDDSManager::datawriter_listeners.find(listener_id);
        if (it == ListenerDDSManager::datawriter_listeners.end() || !it->second) {
            return py::none();
        }
        return py::cast(static_cast<void*>(it->second));
    }, py::arg("listener_id"), "Get DataWriterListener raw pointer for integration");
    
    m.def("delete_datawriter_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::datawriter_listeners.find(listener_id);
        if (it != ListenerDDSManager::datawriter_listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::datawriter_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete DataWriterListener by ID");
    
    // Factory functions for DomainParticipantListener
    m.def("create_participant_listener", []() -> int {
        DDS::DomainParticipantListener* listener = new DDS::DomainParticipantListener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::participant_listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create DomainParticipantListener and return ID");
    
    m.def("delete_participant_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::participant_listeners.find(listener_id);
        if (it != ListenerDDSManager::participant_listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::participant_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete DomainParticipantListener by ID");
    
    // Factory functions for PublisherListener
    m.def("create_publisher_listener", []() -> int {
        DDS::PublisherListener* listener = new DDS::PublisherListener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::publisher_listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create PublisherListener and return ID");
    
    m.def("delete_publisher_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::publisher_listeners.find(listener_id);
        if (it != ListenerDDSManager::publisher_listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::publisher_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete PublisherListener by ID");
    
    // Factory functions for SubscriberListener
    m.def("create_subscriber_listener", []() -> int {
        DDS::SubscriberListener* listener = new DDS::SubscriberListener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::subscriber_listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create SubscriberListener and return ID");
    
    m.def("delete_subscriber_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::subscriber_listeners.find(listener_id);
        if (it != ListenerDDSManager::subscriber_listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::subscriber_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete SubscriberListener by ID");
    
    // Factory functions for TopicListener
    m.def("create_topic_listener", []() -> int {
        DDS::TopicListener* listener = new DDS::TopicListener();
        if (listener) {
            int id = ListenerDDSManager::generate_id();
            ListenerDDSManager::topic_listeners[id] = listener;
            return id;
        }
        return -1;
    }, "Create TopicListener and return ID");
    
    m.def("delete_topic_listener", [](int listener_id) -> bool {
        auto it = ListenerDDSManager::topic_listeners.find(listener_id);
        if (it != ListenerDDSManager::topic_listeners.end()) {
            if (it->second) {
                delete it->second;
            }
            ListenerDDSManager::topic_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Delete TopicListener by ID");
    
    // Listener callback functions (placeholders for now)
    m.def("set_datareader_listener_callback", [](int listener_id, const std::string& callback_type, py::function callback) -> bool {
        auto it = ListenerDDSManager::datareader_listeners.find(listener_id);
        if (it != ListenerDDSManager::datareader_listeners.end() && it->second) {
            // For now, return success as placeholder
            // This would need to be implemented with proper callback registration
            return true;
        }
        return false;
    }, py::arg("listener_id"), py::arg("callback_type"), py::arg("callback"), "Set DataReaderListener callback");
    
    m.def("set_datawriter_listener_callback", [](int listener_id, const std::string& callback_type, py::function callback) -> bool {
        auto it = ListenerDDSManager::datawriter_listeners.find(listener_id);
        if (it != ListenerDDSManager::datawriter_listeners.end() && it->second) {
            // For now, return success as placeholder
            return true;
        }
        return false;
    }, py::arg("listener_id"), py::arg("callback_type"), py::arg("callback"), "Set DataWriterListener callback");
    
    // Listener attachment functions
    m.def("attach_datareader_listener", [](int listener_id, py::object datareader_obj, int status_mask = DDS::STATUS_MASK_ALL) -> bool {
        auto it = ListenerDDSManager::datareader_listeners.find(listener_id);
        if (it != ListenerDDSManager::datareader_listeners.end() && it->second) {
            DDS::DataReader* reader = static_cast<DDS::DataReader*>(datareader_obj.cast<void*>());
            if (reader) {
                DDS::ReturnCode_t ret = reader->set_listener(it->second, static_cast<DDS::StatusKindMask>(status_mask));
                return (ret == DDS::RETCODE_OK);
            }
        }
        return false;
    }, py::arg("listener_id"), py::arg("datareader_ptr"), py::arg("status_mask") = DDS::STATUS_MASK_ALL, "Attach DataReaderListener to DataReader");
    
    m.def("attach_datawriter_listener", [](int listener_id, py::object datawriter_obj, int status_mask = DDS::STATUS_MASK_ALL) -> bool {
        auto it = ListenerDDSManager::datawriter_listeners.find(listener_id);
        if (it != ListenerDDSManager::datawriter_listeners.end() && it->second) {
            DDS::DataWriter* writer = static_cast<DDS::DataWriter*>(datawriter_obj.cast<void*>());
            if (writer) {
                DDS::ReturnCode_t ret = writer->set_listener(it->second, static_cast<DDS::StatusKindMask>(status_mask));
                return (ret == DDS::RETCODE_OK);
            }
        }
        return false;
    }, py::arg("listener_id"), py::arg("datawriter_ptr"), py::arg("status_mask") = DDS::STATUS_MASK_ALL, "Attach DataWriterListener to DataWriter");
    
    m.def("attach_participant_listener", [](int listener_id, py::object participant_obj, int status_mask = DDS::STATUS_MASK_ALL) -> bool {
        auto it = ListenerDDSManager::participant_listeners.find(listener_id);
        if (it != ListenerDDSManager::participant_listeners.end() && it->second) {
            DDS::DomainParticipant* participant = static_cast<DDS::DomainParticipant*>(participant_obj.cast<void*>());
            if (participant) {
                DDS::ReturnCode_t ret = participant->set_listener(it->second, static_cast<DDS::StatusKindMask>(status_mask));
                return (ret == DDS::RETCODE_OK);
            }
        }
        return false;
    }, py::arg("listener_id"), py::arg("participant_ptr"), py::arg("status_mask") = DDS::STATUS_MASK_ALL, "Attach DomainParticipantListener to DomainParticipant");
    
    m.def("attach_publisher_listener", [](int listener_id, py::object publisher_obj, int status_mask = DDS::STATUS_MASK_ALL) -> bool {
        auto it = ListenerDDSManager::publisher_listeners.find(listener_id);
        if (it != ListenerDDSManager::publisher_listeners.end() && it->second) {
            DDS::Publisher* publisher = static_cast<DDS::Publisher*>(publisher_obj.cast<void*>());
            if (publisher) {
                DDS::ReturnCode_t ret = publisher->set_listener(it->second, static_cast<DDS::StatusKindMask>(status_mask));
                return (ret == DDS::RETCODE_OK);
            }
        }
        return false;
    }, py::arg("listener_id"), py::arg("publisher_ptr"), py::arg("status_mask") = DDS::STATUS_MASK_ALL, "Attach PublisherListener to Publisher");
    
    m.def("attach_subscriber_listener", [](int listener_id, py::object subscriber_obj, int status_mask = DDS::STATUS_MASK_ALL) -> bool {
        auto it = ListenerDDSManager::subscriber_listeners.find(listener_id);
        if (it != ListenerDDSManager::subscriber_listeners.end() && it->second) {
            DDS::Subscriber* subscriber = static_cast<DDS::Subscriber*>(subscriber_obj.cast<void*>());
            if (subscriber) {
                DDS::ReturnCode_t ret = subscriber->set_listener(it->second, static_cast<DDS::StatusKindMask>(status_mask));
                return (ret == DDS::RETCODE_OK);
            }
        }
        return false;
    }, py::arg("listener_id"), py::arg("subscriber_ptr"), py::arg("status_mask") = DDS::STATUS_MASK_ALL, "Attach SubscriberListener to Subscriber");
    
    m.def("attach_topic_listener", [](int listener_id, py::object topic_obj, int status_mask = DDS::STATUS_MASK_ALL) -> bool {
        auto it = ListenerDDSManager::topic_listeners.find(listener_id);
        if (it != ListenerDDSManager::topic_listeners.end() && it->second) {
            DDS::Topic* topic = static_cast<DDS::Topic*>(topic_obj.cast<void*>());
            if (topic) {
                DDS::ReturnCode_t ret = topic->set_listener(it->second, static_cast<DDS::StatusKindMask>(status_mask));
                return (ret == DDS::RETCODE_OK);
            }
        }
        return false;
    }, py::arg("listener_id"), py::arg("topic_ptr"), py::arg("status_mask") = DDS::STATUS_MASK_ALL, "Attach TopicListener to Topic");
    
    // Status mask constants
    m.attr("STATUS_MASK_NONE") = DDS::STATUS_MASK_NONE;
    m.attr("STATUS_MASK_ALL") = DDS::STATUS_MASK_ALL;
    // Note: Individual status masks are not directly available as constants
    // They are typically used as bit flags in StatusMask values
    
    // Utility functions
    m.def("get_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::listeners.size());
    }, "Get number of base listeners");
    
    m.def("get_datareader_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::datareader_listeners.size());
    }, "Get number of DataReader listeners");
    
    m.def("get_datawriter_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::datawriter_listeners.size());
    }, "Get number of DataWriter listeners");
    
    m.def("get_participant_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::participant_listeners.size());
    }, "Get number of DomainParticipant listeners");
    
    m.def("get_publisher_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::publisher_listeners.size());
    }, "Get number of Publisher listeners");
    
    m.def("get_subscriber_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::subscriber_listeners.size());
    }, "Get number of Subscriber listeners");
    
    m.def("get_topic_listener_count", []() {
        return static_cast<int>(ListenerDDSManager::topic_listeners.size());
    }, "Get number of Topic listeners");
    
    // Cleanup function
    m.def("finalize", []() {
        ListenerDDSManager::cleanup();
        return true;
    }, "Cleanup Listener DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Listener Module with Factory Pattern - C++ Interface";
        info["listener_count"] = ListenerDDSManager::listeners.size();
        info["datareader_listener_count"] = ListenerDDSManager::datareader_listeners.size();
        info["datawriter_listener_count"] = ListenerDDSManager::datawriter_listeners.size();
        info["participant_listener_count"] = ListenerDDSManager::participant_listeners.size();
        info["publisher_listener_count"] = ListenerDDSManager::publisher_listeners.size();
        info["subscriber_listener_count"] = ListenerDDSManager::subscriber_listeners.size();
        info["topic_listener_count"] = ListenerDDSManager::topic_listeners.size();
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_listener"));
        functions.append(py::str("delete_listener"));
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
        functions.append(py::str("set_datareader_listener_callback"));
        functions.append(py::str("set_datawriter_listener_callback"));
        functions.append(py::str("attach_datareader_listener"));
        functions.append(py::str("attach_datawriter_listener"));
        functions.append(py::str("attach_participant_listener"));
        functions.append(py::str("attach_publisher_listener"));
        functions.append(py::str("attach_subscriber_listener"));
        functions.append(py::str("attach_topic_listener"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
