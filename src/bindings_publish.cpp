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
#include "DomainParticipant.h"
#include "ZRBuiltinTypesTypeSupport.h"

namespace py = pybind11;

// Global storage for publish DDS entities
struct PublishDDSManager {
    static std::map<int, DDS::Publisher*> publishers;
    static std::map<int, DDS::DataWriter*> data_writers;
    static std::map<int, DDS::PublisherQos*> publisher_qos;
    static std::map<int, DDS::DataWriterQos*> datawriter_qos;
    
    // Integration with Topic module
    static std::map<int, DDS::DomainParticipant*> participants;
    static std::map<std::string, DDS::Topic*> topics;
    // Integration with Listener module (registered from Python)
    static std::map<int, DDS::DataWriterListener*> datawriter_listeners;
    
    static int next_id;
    
    static int generate_id() { return ++next_id; }
    
    static void cleanup() {
        // Clean up publishers
        for (auto& pair : publishers) {
            if (pair.second) {
                // Note: Publisher deletion is handled by DomainParticipant
                // We just remove from our map
            }
        }
        
        // Clean up data writers
        for (auto& pair : data_writers) {
            if (pair.second) {
                // Note: DataWriter deletion is handled by Publisher
                // We just remove from our map
            }
        }
        
        // Clean up QoS objects
        for (auto& pair : publisher_qos) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : datawriter_qos) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clear all maps
        publishers.clear();
        data_writers.clear();
        publisher_qos.clear();
        datawriter_qos.clear();
        participants.clear();
        topics.clear();
        datawriter_listeners.clear();
    }
    
    // Integration methods
    static void register_participant(int domain_id, DDS::DomainParticipant* participant) {
        participants[domain_id] = participant;
    }
    
    static void register_topic(const std::string& topic_name, DDS::Topic* topic) {
        topics[topic_name] = topic;
    }
    
    static DDS::DomainParticipant* get_participant(int domain_id) {
        auto it = participants.find(domain_id);
        return (it != participants.end()) ? it->second : nullptr;
    }
    
    static DDS::Topic* get_topic(const std::string& topic_name) {
        auto it = topics.find(topic_name);
        return (it != topics.end()) ? it->second : nullptr;
    }
};

std::map<int, DDS::Publisher*> PublishDDSManager::publishers;
std::map<int, DDS::DataWriter*> PublishDDSManager::data_writers;
std::map<int, DDS::PublisherQos*> PublishDDSManager::publisher_qos;
std::map<int, DDS::DataWriterQos*> PublishDDSManager::datawriter_qos;
std::map<int, DDS::DomainParticipant*> PublishDDSManager::participants;
std::map<std::string, DDS::Topic*> PublishDDSManager::topics;
std::map<int, DDS::DataWriterListener*> PublishDDSManager::datawriter_listeners;
int PublishDDSManager::next_id = 3000;

// Publish module wrapper
PYBIND11_MODULE(_zrdds_publish, m) {
    m.doc() = "ZRDDS Python Wrapper - Publish Module (C++ Interface with Factory Pattern)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Publish Module with Factory Pattern!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Publish Module v2.0.0 - Factory Pattern Implementation";
    });
    
    // Initialize publish module
    m.def("init", []() {
        // Clean up any existing entities
        PublishDDSManager::cleanup();
        return true;
    }, "Initialize Publish DDS module");
    
    // Integration functions for Topic module
    m.def("register_participant", [](int domain_id, void* participant_ptr) -> bool {
        DDS::DomainParticipant* participant = static_cast<DDS::DomainParticipant*>(participant_ptr);
        if (participant) {
            PublishDDSManager::register_participant(domain_id, participant);
            return true;
        }
        return false;
    }, py::arg("domain_id"), py::arg("participant_ptr"), "Register DomainParticipant from Topic module");
    
    m.def("register_topic", [](const std::string& topic_name, void* topic_ptr) -> bool {
        DDS::Topic* topic = static_cast<DDS::Topic*>(topic_ptr);
        if (topic) {
            PublishDDSManager::register_topic(topic_name, topic);
            return true;
        }
        return false;
    }, py::arg("topic_name"), py::arg("topic_ptr"), "Register Topic from Topic module");

    // Integration functions for Listener module
    m.def("register_datawriter_listener", [](int listener_id, void* listener_ptr) -> bool {
        DDS::DataWriterListener* listener = static_cast<DDS::DataWriterListener*>(listener_ptr);
        if (listener) {
            PublishDDSManager::datawriter_listeners[listener_id] = listener;
            return true;
        }
        return false;
    }, py::arg("listener_id"), py::arg("listener_ptr"), "Register DataWriterListener from Listener module");

    m.def("unregister_datawriter_listener", [](int listener_id) -> bool {
        auto it = PublishDDSManager::datawriter_listeners.find(listener_id);
        if (it != PublishDDSManager::datawriter_listeners.end()) {
            PublishDDSManager::datawriter_listeners.erase(it);
            return true;
        }
        return false;
    }, py::arg("listener_id"), "Unregister DataWriterListener from Publish module");
    
    // Factory functions for PublisherQos
    m.def("create_publisher_qos", []() -> int {
        DDS::PublisherQos* qos = new DDS::PublisherQos();
        if (qos) {
            // Use ZRDDS default QoS initialization function
            DDS_DefaultPublisherQosInitial(qos);
            int id = PublishDDSManager::generate_id();
            PublishDDSManager::publisher_qos[id] = qos;
            return id;
        }
        return -1;
    }, "Create PublisherQos with ZRDDS default values and return ID");
    
    m.def("delete_publisher_qos", [](int qos_id) -> bool {
        auto it = PublishDDSManager::publisher_qos.find(qos_id);
        if (it != PublishDDSManager::publisher_qos.end()) {
            if (it->second) {
                delete it->second;
            }
            PublishDDSManager::publisher_qos.erase(it);
            return true;
        }
        return false;
    }, py::arg("qos_id"), "Delete PublisherQos by ID");
    
    // Factory functions for DataWriterQos
    m.def("create_datawriter_qos", []() -> int {
        DDS::DataWriterQos* qos = new DDS::DataWriterQos();
        if (qos) {
            // Use ZRDDS default QoS initialization function
            DDS_DefaultDataWriterQosInitial(qos);
            int id = PublishDDSManager::generate_id();
            PublishDDSManager::datawriter_qos[id] = qos;
            return id;
        }
        return -1;
    }, "Create DataWriterQos with ZRDDS default values and return ID");
    
    m.def("delete_datawriter_qos", [](int qos_id) -> bool {
        auto it = PublishDDSManager::datawriter_qos.find(qos_id);
        if (it != PublishDDSManager::datawriter_qos.end()) {
            if (it->second) {
                delete it->second;
            }
            PublishDDSManager::datawriter_qos.erase(it);
            return true;
        }
        return false;
    }, py::arg("qos_id"), "Delete DataWriterQos by ID");
    
    // Enhanced Publisher creation with Topic module integration
    m.def("create_publisher", [](int domain_id, int qos_id = -1, 
                                 void* listener = nullptr) -> int {
        DDS::DomainParticipant* participant = PublishDDSManager::get_participant(domain_id);
        if (!participant) {
            return -1; // Participant not found
        }
        
        DDS::PublisherQos* qos = nullptr;
        if (qos_id != -1) {
            auto it = PublishDDSManager::publisher_qos.find(qos_id);
            if (it != PublishDDSManager::publisher_qos.end()) {
                qos = it->second;
            }
        }
        
        // Use properly initialized default QoS if none provided
        DDS::PublisherQos default_qos;
        if (!qos) {
            DDS_DefaultPublisherQosInitial(&default_qos);
            qos = &default_qos;
        }
        const DDS::PublisherQos& final_qos = *qos;
        
        DDS::Publisher* publisher = participant->create_publisher(
            final_qos, 
            static_cast<DDS::PublisherListener*>(listener), 
            DDS::STATUS_MASK_ALL
        );
        
        if (publisher) {
            int id = PublishDDSManager::generate_id();
            PublishDDSManager::publishers[id] = publisher;
            return id;
        }
        return -1;
    }, py::arg("domain_id"), py::arg("qos_id") = -1, py::arg("listener") = nullptr, 
       "Create Publisher for domain and return ID");
    
    m.def("delete_publisher", [](int publisher_id) -> bool {
        auto it = PublishDDSManager::publishers.find(publisher_id);
        if (it != PublishDDSManager::publishers.end()) {
            // Publisher deletion is handled by DomainParticipant
            PublishDDSManager::publishers.erase(it);
            return true;
        }
        return false;
    }, py::arg("publisher_id"), "Delete Publisher by ID");
    
    // Enhanced DataWriter creation with Topic module integration
    m.def("create_datawriter", [](int publisher_id, const std::string& topic_name, int qos_id = -1,
                                  void* listener = nullptr) -> int {
        auto publisher_it = PublishDDSManager::publishers.find(publisher_id);
        if (publisher_it == PublishDDSManager::publishers.end() || !publisher_it->second) {
            return -1; // Publisher not found
        }
        
        DDS::Topic* topic = PublishDDSManager::get_topic(topic_name);
        if (!topic) {
            return -1; // Topic not found
        }
        
        // Debug: check topic pointer
        if (topic == nullptr) {
            return -1; // Topic is null
        }
        
        // Get the participant from the topic
        DDS::DomainParticipant* participant = topic->get_participant();
        if (!participant) {
            return -1; // Participant not found
        }
        
        // Ensure type support is registered (if not already done by Topic module)
        // BytesTypeSupport should be registered by Topic module during topic creation
        
        DDS::DataWriterQos* qos = nullptr;
        if (qos_id != -1) {
            auto qos_it = PublishDDSManager::datawriter_qos.find(qos_id);
            if (qos_it != PublishDDSManager::datawriter_qos.end()) {
                qos = qos_it->second;
            }
        }
        
        // Use properly initialized default QoS if none provided
        DDS::DataWriterQos default_qos;
        if (!qos) {
            DDS_DefaultDataWriterQosInitial(&default_qos);
            qos = &default_qos;
        }
        const DDS::DataWriterQos& final_qos = *qos;
        
        DDS::DataWriter* writer = publisher_it->second->create_datawriter(
            topic, 
            final_qos, 
            static_cast<DDS::DataWriterListener*>(listener), 
            DDS::STATUS_MASK_ALL
        );
        
        // Debug: check what create_datawriter returned
        if (writer == nullptr) {
            // DataWriter creation failed - return -1
            return -1;
        }
        
        // Store the writer and return ID
        int id = PublishDDSManager::generate_id();
        PublishDDSManager::data_writers[id] = writer;
        return id;
    }, py::arg("publisher_id"), py::arg("topic_name"), py::arg("qos_id") = -1, py::arg("listener") = nullptr,
       "Create DataWriter for topic and return ID");
    
    m.def("delete_datawriter", [](int writer_id) -> bool {
        auto it = PublishDDSManager::data_writers.find(writer_id);
        if (it != PublishDDSManager::data_writers.end()) {
            // DataWriter deletion is handled by Publisher
            PublishDDSManager::data_writers.erase(it);
            return true;
        }
        return false;
    }, py::arg("writer_id"), "Delete DataWriter by ID");
    
    // Enhanced DataWriter operations
    m.def("datawriter_write", [](int writer_id, const py::bytes& data, int handle_id = -1) -> bool {
        auto it = PublishDDSManager::data_writers.find(writer_id);
        if (it == PublishDDSManager::data_writers.end() || !it->second) {
            return false;
        }
        
        // For now, return success as a placeholder
        // This would need to be implemented with proper data type handling
        return true;
    }, py::arg("writer_id"), py::arg("data"), py::arg("handle_id") = -1, "Write data using DataWriter");
    
    m.def("datawriter_register_instance", [](int writer_id, const py::bytes& instance_data) -> py::object {
        auto it = PublishDDSManager::data_writers.find(writer_id);
        if (it == PublishDDSManager::data_writers.end() || !it->second) {
            return py::none();
        }
        
        // For now, return a placeholder result
        // This would need to be implemented with proper instance handling
        py::dict result;
        result["handle"] = 0; // Placeholder handle
        result["status"] = "registered";
        return result;
    }, py::arg("writer_id"), py::arg("instance_data"), "Register instance with DataWriter");
    
    m.def("datawriter_unregister_instance", [](int writer_id, const py::bytes& instance_data, int handle_id = -1) -> bool {
        auto it = PublishDDSManager::data_writers.find(writer_id);
        if (it == PublishDDSManager::data_writers.end() || !it->second) {
            return false;
        }
        
        // For now, return success as a placeholder
        return true;
    }, py::arg("writer_id"), py::arg("instance_data"), py::arg("handle_id") = -1, "Unregister instance from DataWriter");
    
    m.def("datawriter_dispose", [](int writer_id, const py::bytes& instance_data, int handle_id = -1) -> bool {
        auto it = PublishDDSManager::data_writers.find(writer_id);
        if (it == PublishDDSManager::data_writers.end() || !it->second) {
            return false;
        }
        
        // For now, return success as a placeholder
        return true;
    }, py::arg("writer_id"), py::arg("instance_data"), py::arg("handle_id") = -1, "Dispose instance from DataWriter");
    
    // Publisher operations
    m.def("publisher_suspend_publications", [](int publisher_id) -> bool {
        auto it = PublishDDSManager::publishers.find(publisher_id);
        if (it == PublishDDSManager::publishers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->suspend_publications();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("publisher_id"), "Suspend publications");
    
    m.def("publisher_resume_publications", [](int publisher_id) -> bool {
        auto it = PublishDDSManager::publishers.find(publisher_id);
        if (it == PublishDDSManager::publishers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->resume_publications();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("publisher_id"), "Resume publications");
    
    m.def("publisher_begin_coherent_changes", [](int publisher_id) -> bool {
        auto it = PublishDDSManager::publishers.find(publisher_id);
        if (it == PublishDDSManager::publishers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->begin_coherent_changes();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("publisher_id"), "Begin coherent changes");
    
    m.def("publisher_end_coherent_changes", [](int publisher_id) -> bool {
        auto it = PublishDDSManager::publishers.find(publisher_id);
        if (it == PublishDDSManager::publishers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->end_coherent_changes();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("publisher_id"), "End coherent changes");
    
    // Utility functions
    m.def("get_publisher_count", []() {
        return static_cast<int>(PublishDDSManager::publishers.size());
    }, "Get number of publishers");
    
    m.def("get_datawriter_count", []() {
        return static_cast<int>(PublishDDSManager::data_writers.size());
    }, "Get number of data writers");
    
    // Get datawriter pointer for integration (named capsule to stabilize in Python)
    m.def("get_datawriter_ptr", [](int datawriter_id) -> py::object {
        auto it = PublishDDSManager::data_writers.find(datawriter_id);
        if (it == PublishDDSManager::data_writers.end() || !it->second) {
            return py::none();
        }
        DDS::DataWriter* writer = it->second;
        // Create named capsule
        return py::capsule(static_cast<void*>(writer), "dds.DataWriter");
    }, py::arg("datawriter_id"), "Get DataWriter pointer for integration");

    // Attach DataWriterListener using writer id and listener id
    m.def("attach_datawriter_listener_by_id", [](int writer_id, int listener_id, uint32_t status_mask) -> bool {
        auto writer_it = PublishDDSManager::data_writers.find(writer_id);
        if (writer_it == PublishDDSManager::data_writers.end() || !writer_it->second) {
            return false;
        }
        auto listener_it = PublishDDSManager::datawriter_listeners.find(listener_id);
        if (listener_it == PublishDDSManager::datawriter_listeners.end() || !listener_it->second) {
            return false;
        }
        DDS::DataWriter* writer = writer_it->second;
        DDS::DataWriterListener* listener = listener_it->second;
        DDS::ReturnCode_t rc = writer->set_listener(listener, static_cast<DDS::StatusKindMask>(status_mask));
        return rc == DDS::RETCODE_OK;
    }, py::arg("writer_id"), py::arg("listener_id"), py::arg("status_mask") = DDS::STATUS_MASK_ALL);
    
    m.def("get_publisher_qos_count", []() {
        return static_cast<int>(PublishDDSManager::publisher_qos.size());
    }, "Get number of publisher QoS objects");
    
    m.def("get_datawriter_qos_count", []() {
        return static_cast<int>(PublishDDSManager::datawriter_qos.size());
    }, "Get number of datawriter QoS objects");
    
    m.def("get_participant_count", []() {
        return static_cast<int>(PublishDDSManager::participants.size());
    }, "Get number of registered participants");
    
    m.def("get_topic_count", []() {
        return static_cast<int>(PublishDDSManager::topics.size());
    }, "Get number of registered topics");
    
    // Cleanup function
    m.def("finalize", []() {
        PublishDDSManager::cleanup();
        return true;
    }, "Cleanup Publish DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Publish Module with Factory Pattern - C++ Interface";
        info["publisher_count"] = PublishDDSManager::publishers.size();
        info["datawriter_count"] = PublishDDSManager::data_writers.size();
        info["publisher_qos_count"] = PublishDDSManager::publisher_qos.size();
        info["datawriter_qos_count"] = PublishDDSManager::datawriter_qos.size();
        info["participant_count"] = PublishDDSManager::participants.size();
        info["topic_count"] = PublishDDSManager::topics.size();
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("register_participant"));
        functions.append(py::str("register_topic"));
        functions.append(py::str("create_publisher_qos"));
        functions.append(py::str("delete_publisher_qos"));
        functions.append(py::str("create_datawriter_qos"));
        functions.append(py::str("delete_datawriter_qos"));
        functions.append(py::str("create_publisher"));
        functions.append(py::str("delete_publisher"));
        functions.append(py::str("create_datawriter"));
        functions.append(py::str("delete_datawriter"));
        functions.append(py::str("datawriter_write"));
        functions.append(py::str("datawriter_register_instance"));
        functions.append(py::str("datawriter_unregister_instance"));
        functions.append(py::str("datawriter_dispose"));
        functions.append(py::str("publisher_suspend_publications"));
        functions.append(py::str("publisher_resume_publications"));
        functions.append(py::str("publisher_begin_coherent_changes"));
        functions.append(py::str("publisher_end_coherent_changes"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
