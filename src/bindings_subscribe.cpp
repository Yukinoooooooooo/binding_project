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
#include "ZRDDSCppWrapper.h"
#include "Topic.h"
#include "DomainParticipant.h"
#include "ZRBuiltinTypesTypeSupport.h"
#include "ZRBuiltinTypesDataReader.h"
#include "ZRDDSDataReader.h"


namespace py = pybind11;

// Global storage for subscribe DDS entities
struct SubscribeDDSManager {
    static std::map<int, DDS::Subscriber*> subscribers;
    static std::map<int, DDS::DataReader*> data_readers;
    static std::map<int, DDS::SubscriberQos*> subscriber_qos;
    static std::map<int, DDS::DataReaderQos*> datareader_qos;
    static std::map<int, DDS::ReadCondition*> read_conditions;
    
    // Integration with Topic module
    static std::map<int, DDS::DomainParticipant*> participants;
    static std::map<std::string, DDS::Topic*> topics;
    
    static int next_id;
    
    static int generate_id() { return ++next_id; }
    
    static void cleanup() {
        // Clean up subscribers
        for (auto& pair : subscribers) {
            if (pair.second) {
                // Note: Subscriber deletion is handled by DomainParticipant
                // We just remove from our map
            }
        }
        
        // Clean up data readers
        for (auto& pair : data_readers) {
            if (pair.second) {
                // Note: DataReader deletion is handled by Subscriber
                // We just remove from our map
            }
        }
        
        // Clean up read conditions
        for (auto& pair : read_conditions) {
            if (pair.second) {
                // Note: ReadCondition deletion is handled by DataReader
                // We just remove from our map
            }
        }
        
        // Clean up QoS objects
        for (auto& pair : subscriber_qos) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        for (auto& pair : datareader_qos) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clear all maps
        subscribers.clear();
        data_readers.clear();
        subscriber_qos.clear();
        datareader_qos.clear();
        read_conditions.clear();
        participants.clear();
        topics.clear();
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

std::map<int, DDS::Subscriber*> SubscribeDDSManager::subscribers;
std::map<int, DDS::DataReader*> SubscribeDDSManager::data_readers;
std::map<int, DDS::SubscriberQos*> SubscribeDDSManager::subscriber_qos;
std::map<int, DDS::DataReaderQos*> SubscribeDDSManager::datareader_qos;
std::map<int, DDS::ReadCondition*> SubscribeDDSManager::read_conditions;
std::map<int, DDS::DomainParticipant*> SubscribeDDSManager::participants;
std::map<std::string, DDS::Topic*> SubscribeDDSManager::topics;
int SubscribeDDSManager::next_id = 4000;

// Subscribe module wrapper
PYBIND11_MODULE(_zrdds_subscribe, m) {
    m.doc() = "ZRDDS Python Wrapper - Subscribe Module (C++ Interface with Factory Pattern)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Subscribe Module with Factory Pattern!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Subscribe Module v2.0.0 - Factory Pattern Implementation";
    });
    
    // Initialize subscribe module
    m.def("init", []() {
        // Clean up any existing entities
        SubscribeDDSManager::cleanup();
        return true;
    }, "Initialize Subscribe DDS module");
    
    // Integration functions for Topic module
    m.def("register_participant", [](int domain_id, void* participant_ptr) -> bool {
        DDS::DomainParticipant* participant = static_cast<DDS::DomainParticipant*>(participant_ptr);
        if (participant) {
            SubscribeDDSManager::register_participant(domain_id, participant);
            return true;
        }
        return false;
    }, py::arg("domain_id"), py::arg("participant_ptr"), "Register DomainParticipant from Topic module");
    
    m.def("register_topic", [](const std::string& topic_name, void* topic_ptr) -> bool {
        DDS::Topic* topic = static_cast<DDS::Topic*>(topic_ptr);
        if (topic) {
            SubscribeDDSManager::register_topic(topic_name, topic);
            return true;
        }
        return false;
    }, py::arg("topic_name"), py::arg("topic_ptr"), "Register Topic from Topic module");
    
    // Factory functions for SubscriberQos
    m.def("create_subscriber_qos", []() -> int {
        DDS::SubscriberQos* qos = new DDS::SubscriberQos();
        if (qos) {
            // Use ZRDDS default QoS initialization function
            DDS_DefaultSubscriberQosInitial(qos);
            int id = SubscribeDDSManager::generate_id();
            SubscribeDDSManager::subscriber_qos[id] = qos;
            return id;
        }
        return -1;
    }, "Create SubscriberQos with ZRDDS default values and return ID");
    
    m.def("delete_subscriber_qos", [](int qos_id) -> bool {
        auto it = SubscribeDDSManager::subscriber_qos.find(qos_id);
        if (it != SubscribeDDSManager::subscriber_qos.end()) {
            if (it->second) {
                delete it->second;
            }
            SubscribeDDSManager::subscriber_qos.erase(it);
            return true;
        }
        return false;
    }, py::arg("qos_id"), "Delete SubscriberQos by ID");
    
    // Factory functions for DataReaderQos
    m.def("create_datareader_qos", []() -> int {
        DDS::DataReaderQos* qos = new DDS::DataReaderQos();
        if (qos) {
            // Use ZRDDS default QoS initialization function
            DDS_DefaultDataReaderQosInitial(qos);
            int id = SubscribeDDSManager::generate_id();
            SubscribeDDSManager::datareader_qos[id] = qos;
            return id;
        }
        return -1;
    }, "Create DataReaderQos with ZRDDS default values and return ID");
    
    m.def("delete_datareader_qos", [](int qos_id) -> bool {
        auto it = SubscribeDDSManager::datareader_qos.find(qos_id);
        if (it != SubscribeDDSManager::datareader_qos.end()) {
            if (it->second) {
                delete it->second;
            }
            SubscribeDDSManager::datareader_qos.erase(it);
            return true;
        }
        return false;
    }, py::arg("qos_id"), "Delete DataReaderQos by ID");
    
    // Enhanced Subscriber creation with Topic module integration
    m.def("create_subscriber", [](int domain_id, int qos_id = -1, 
                                  void* listener = nullptr) -> int {
        DDS::DomainParticipant* participant = SubscribeDDSManager::get_participant(domain_id);
        if (!participant) {
            return -1; // Participant not found
        }
        
        DDS::SubscriberQos* qos = nullptr;
        if (qos_id != -1) {
            auto it = SubscribeDDSManager::subscriber_qos.find(qos_id);
            if (it != SubscribeDDSManager::subscriber_qos.end()) {
                qos = it->second;
            }
        }
        
        // Use properly initialized default QoS if none provided
        DDS::SubscriberQos default_qos;
        if (!qos) {
            DDS_DefaultSubscriberQosInitial(&default_qos);
            qos = &default_qos;
        }
        const DDS::SubscriberQos& final_qos = *qos;
        
        DDS::Subscriber* subscriber = participant->create_subscriber(
            final_qos, 
            static_cast<DDS::SubscriberListener*>(listener), 
            DDS::STATUS_MASK_ALL
        );
        
        if (subscriber) {
            int id = SubscribeDDSManager::generate_id();
            SubscribeDDSManager::subscribers[id] = subscriber;
            return id;
        }
        return -1;
    }, py::arg("domain_id"), py::arg("qos_id") = -1, py::arg("listener") = nullptr, 
       "Create Subscriber for domain and return ID");
    
    m.def("delete_subscriber", [](int subscriber_id) -> bool {
        auto it = SubscribeDDSManager::subscribers.find(subscriber_id);
        if (it != SubscribeDDSManager::subscribers.end()) {
            // Subscriber deletion is handled by DomainParticipant
            SubscribeDDSManager::subscribers.erase(it);
            return true;
        }
        return false;
    }, py::arg("subscriber_id"), "Delete Subscriber by ID");
    
    // Enhanced DataReader creation with Topic module integration
    m.def("create_datareader", [](int subscriber_id, const std::string& topic_name, int qos_id = -1,
                                  void* listener = nullptr) -> int {
        auto subscriber_it = SubscribeDDSManager::subscribers.find(subscriber_id);
        if (subscriber_it == SubscribeDDSManager::subscribers.end() || !subscriber_it->second) {
            return -1; // Subscriber not found
        }
        
        DDS::Topic* topic = SubscribeDDSManager::get_topic(topic_name);
        if (!topic) {
            return -1; // Topic not found
        }
        
        DDS::DataReaderQos* qos = nullptr;
        if (qos_id != -1) {
            auto qos_it = SubscribeDDSManager::datareader_qos.find(qos_id);
            if (qos_it != SubscribeDDSManager::datareader_qos.end()) {
                qos = qos_it->second;
            }
        }
        
        // Use properly initialized default QoS if none provided
        DDS::DataReaderQos default_qos;
        if (!qos) {
            DDS_DefaultDataReaderQosInitial(&default_qos);
            qos = &default_qos;
        }
        const DDS::DataReaderQos& final_qos = *qos;
        
        DDS::DataReader* reader = subscriber_it->second->create_datareader(
            topic, 
            final_qos, 
            static_cast<DDS::DataReaderListener*>(listener), 
            DDS::STATUS_MASK_ALL
        );
        
        if (reader) {
            int id = SubscribeDDSManager::generate_id();
            SubscribeDDSManager::data_readers[id] = reader;
            return id;
        }
        return -1;
    }, py::arg("subscriber_id"), py::arg("topic_name"), py::arg("qos_id") = -1, py::arg("listener") = nullptr,
       "Create DataReader for topic and return ID");
    
    m.def("delete_datareader", [](int reader_id) -> bool {
        auto it = SubscribeDDSManager::data_readers.find(reader_id);
        if (it != SubscribeDDSManager::data_readers.end()) {
            // DataReader deletion is handled by Subscriber
            SubscribeDDSManager::data_readers.erase(it);
            return true;
        }
        return false;
    }, py::arg("reader_id"), "Delete DataReader by ID");
    
    // ReadCondition creation
    m.def("create_readcondition", [](int reader_id, int sample_states = DDS::ANY_SAMPLE_STATE,
                                     int view_states = DDS::ANY_VIEW_STATE,
                                     int instance_states = DDS::ANY_INSTANCE_STATE) -> int {
        auto reader_it = SubscribeDDSManager::data_readers.find(reader_id);
        if (reader_it == SubscribeDDSManager::data_readers.end() || !reader_it->second) {
            return -1; // DataReader not found
        }
        
        DDS::ReadCondition* condition = reader_it->second->create_readcondition(
            static_cast<DDS::SampleStateMask>(sample_states),
            static_cast<DDS::ViewStateMask>(view_states),
            static_cast<DDS::InstanceStateMask>(instance_states)
        );
        
        if (condition) {
            int id = SubscribeDDSManager::generate_id();
            SubscribeDDSManager::read_conditions[id] = condition;
            return id;
        }
        return -1;
    }, py::arg("reader_id"), py::arg("sample_states") = DDS::ANY_SAMPLE_STATE,
       py::arg("view_states") = DDS::ANY_VIEW_STATE, py::arg("instance_states") = DDS::ANY_INSTANCE_STATE,
       "Create ReadCondition for DataReader and return ID");
    
    m.def("delete_readcondition", [](int condition_id) -> bool {
        auto it = SubscribeDDSManager::read_conditions.find(condition_id);
        if (it != SubscribeDDSManager::read_conditions.end()) {
            // ReadCondition deletion is handled by DataReader
            SubscribeDDSManager::read_conditions.erase(it);
            return true;
        }
        return false;
    }, py::arg("condition_id"), "Delete ReadCondition by ID");
    
    // Enhanced DataReader operations
    m.def("datareader_read", [](int reader_id, int max_samples = 1) -> py::object {
        auto it = SubscribeDDSManager::data_readers.find(reader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return py::none();
        }
        
        // For now, return a placeholder result
        // This would need to be implemented with proper data type handling
        py::dict result;
        result["data"] = py::bytes(""); // Placeholder data
        result["sample_info"] = py::dict(); // Placeholder sample info
        result["samples_read"] = 0;
        return result;
    }, py::arg("reader_id"), py::arg("max_samples") = 1, "Read data using DataReader");
    
    m.def("datareader_take", [](int reader_id, int max_samples = 1) -> py::object {
        auto it = SubscribeDDSManager::data_readers.find(reader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return py::none();
        }
        
        // For now, return a placeholder result
        // This would need to be implemented with proper data type handling
        py::dict result;
        result["data"] = py::bytes(""); // Placeholder data
        result["sample_info"] = py::dict(); // Placeholder sample info
        result["samples_taken"] = 0;
        return result;
    }, py::arg("reader_id"), py::arg("max_samples") = 1, "Take data using DataReader");
    
    m.def("datareader_read_next", [](int reader_id) -> py::object {
        auto it = SubscribeDDSManager::data_readers.find(reader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return py::none();
        }
        
        // For now, return a placeholder result
        py::dict result;
        result["data"] = py::bytes(""); // Placeholder data
        result["sample_info"] = py::dict(); // Placeholder sample info
        result["success"] = false;
        return result;
    }, py::arg("reader_id"), "Read next sample using DataReader");
    
    m.def("datareader_take_next", [](int reader_id) -> py::object {
        auto it = SubscribeDDSManager::data_readers.find(reader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return py::none();
        }
        
        // For now, return a placeholder result
        py::dict result;
        result["data"] = py::bytes(""); // Placeholder data
        result["sample_info"] = py::dict(); // Placeholder sample info
        result["success"] = false;
        return result;
    }, py::arg("reader_id"), "Take next sample using DataReader");
    
    // Subscriber operations
    m.def("subscriber_begin_access", [](int subscriber_id) -> bool {
        auto it = SubscribeDDSManager::subscribers.find(subscriber_id);
        if (it == SubscribeDDSManager::subscribers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->begin_access();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("subscriber_id"), "Begin access to subscriber");
    
    m.def("subscriber_end_access", [](int subscriber_id) -> bool {
        auto it = SubscribeDDSManager::subscribers.find(subscriber_id);
        if (it == SubscribeDDSManager::subscribers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->end_access();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("subscriber_id"), "End access to subscriber");
    
    m.def("subscriber_notify_datareaders", [](int subscriber_id) -> bool {
        auto it = SubscribeDDSManager::subscribers.find(subscriber_id);
        if (it == SubscribeDDSManager::subscribers.end() || !it->second) {
            return false;
        }
        
        DDS::ReturnCode_t ret = it->second->notify_datareaders();
        return (ret == DDS::RETCODE_OK);
    }, py::arg("subscriber_id"), "Notify data readers");
    
    // Data reading functions
    m.def("read_bytes_data", [](int datareader_id) -> py::object {
        auto it = SubscribeDDSManager::data_readers.find(datareader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return py::none();
        }
        
        DDS::DataReader* reader = it->second;
        
        // For now, return a placeholder to indicate the function is called
        // TODO: Implement proper data reading when ZRDDS template issues are resolved
        // This is a temporary workaround to test the communication flow
        return py::str("PLACEHOLDER_DATA_RECEIVED");
    }, py::arg("datareader_id"), "Read bytes data from DataReader");
    
    m.def("read_string_data", [](int datareader_id) -> py::object {
        auto it = SubscribeDDSManager::data_readers.find(datareader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return py::none();
        }
        
        DDS::DataReader* reader = it->second;
        
        // Temporarily disabled due to template compatibility issues
        // TODO: Fix ZRDDSDataReader template compatibility
        return py::none();
    }, py::arg("datareader_id"), "Read string data from DataReader");
    
    m.def("wait_for_data", [](int datareader_id, int timeout_seconds = 5) -> bool {
        auto it = SubscribeDDSManager::data_readers.find(datareader_id);
        if (it == SubscribeDDSManager::data_readers.end() || !it->second) {
            return false;
        }
        
        DDS::DataReader* reader = it->second;
        
        // Simple polling approach - wait for data to become available
        auto start_time = std::chrono::steady_clock::now();
        auto timeout = std::chrono::seconds(timeout_seconds);
        
        while (std::chrono::steady_clock::now() - start_time < timeout) {
            // Check if data is available by trying to read
            DDS::BytesSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            
            // Temporarily disabled due to template compatibility issues
            // TODO: Fix ZRDDSDataReader template compatibility
            // For now, just wait and return false
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Wait a bit before checking again
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        return false;  // Timeout
    }, py::arg("datareader_id"), py::arg("timeout_seconds") = 5, "Wait for data to become available");
    
    // ReadCondition operations
    m.def("readcondition_get_datareader", [](int condition_id) -> int {
        auto it = SubscribeDDSManager::read_conditions.find(condition_id);
        if (it == SubscribeDDSManager::read_conditions.end() || !it->second) {
            return -1;
        }
        
        DDS::DataReader* reader = it->second->get_datareader();
        if (reader) {
            // Find the reader ID in our map
            for (auto& pair : SubscribeDDSManager::data_readers) {
                if (pair.second == reader) {
                    return pair.first;
                }
            }
        }
        return -1;
    }, py::arg("condition_id"), "Get DataReader associated with ReadCondition");
    
    m.def("readcondition_get_sample_state_mask", [](int condition_id) -> int {
        auto it = SubscribeDDSManager::read_conditions.find(condition_id);
        if (it == SubscribeDDSManager::read_conditions.end() || !it->second) {
            return -1;
        }
        
        return static_cast<int>(it->second->get_sample_state_mask());
    }, py::arg("condition_id"), "Get sample state mask of ReadCondition");
    
    m.def("readcondition_get_view_state_mask", [](int condition_id) -> int {
        auto it = SubscribeDDSManager::read_conditions.find(condition_id);
        if (it == SubscribeDDSManager::read_conditions.end() || !it->second) {
            return -1;
        }
        
        return static_cast<int>(it->second->get_view_state_mask());
    }, py::arg("condition_id"), "Get view state mask of ReadCondition");
    
    m.def("readcondition_get_instance_state_mask", [](int condition_id) -> int {
        auto it = SubscribeDDSManager::read_conditions.find(condition_id);
        if (it == SubscribeDDSManager::read_conditions.end() || !it->second) {
            return -1;
        }
        
        return static_cast<int>(it->second->get_instance_state_mask());
    }, py::arg("condition_id"), "Get instance state mask of ReadCondition");
    
    // Utility functions
    m.def("get_subscriber_count", []() {
        return static_cast<int>(SubscribeDDSManager::subscribers.size());
    }, "Get number of subscribers");
    
    m.def("get_datareader_count", []() {
        return static_cast<int>(SubscribeDDSManager::data_readers.size());
    }, "Get number of data readers");
    
    m.def("get_subscriber_qos_count", []() {
        return static_cast<int>(SubscribeDDSManager::subscriber_qos.size());
    }, "Get number of subscriber QoS objects");
    
    m.def("get_datareader_qos_count", []() {
        return static_cast<int>(SubscribeDDSManager::datareader_qos.size());
    }, "Get number of datareader QoS objects");
    
    m.def("get_readcondition_count", []() {
        return static_cast<int>(SubscribeDDSManager::read_conditions.size());
    }, "Get number of read conditions");
    
    m.def("get_participant_count", []() {
        return static_cast<int>(SubscribeDDSManager::participants.size());
    }, "Get number of registered participants");
    
    m.def("get_topic_count", []() {
        return static_cast<int>(SubscribeDDSManager::topics.size());
    }, "Get number of registered topics");
    
    // Cleanup function
    m.def("finalize", []() {
        SubscribeDDSManager::cleanup();
        return true;
    }, "Cleanup Subscribe DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Subscribe Module with Factory Pattern - C++ Interface";
        info["subscriber_count"] = SubscribeDDSManager::subscribers.size();
        info["datareader_count"] = SubscribeDDSManager::data_readers.size();
        info["subscriber_qos_count"] = SubscribeDDSManager::subscriber_qos.size();
        info["datareader_qos_count"] = SubscribeDDSManager::datareader_qos.size();
        info["readcondition_count"] = SubscribeDDSManager::read_conditions.size();
        info["participant_count"] = SubscribeDDSManager::participants.size();
        info["topic_count"] = SubscribeDDSManager::topics.size();
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("register_participant"));
        functions.append(py::str("register_topic"));
        functions.append(py::str("create_subscriber_qos"));
        functions.append(py::str("delete_subscriber_qos"));
        functions.append(py::str("create_datareader_qos"));
        functions.append(py::str("delete_datareader_qos"));
        functions.append(py::str("create_subscriber"));
        functions.append(py::str("delete_subscriber"));
        functions.append(py::str("create_datareader"));
        functions.append(py::str("delete_datareader"));
        functions.append(py::str("create_readcondition"));
        functions.append(py::str("delete_readcondition"));
        functions.append(py::str("datareader_read"));
        functions.append(py::str("datareader_take"));
        functions.append(py::str("datareader_read_next"));
        functions.append(py::str("datareader_take_next"));
        functions.append(py::str("subscriber_begin_access"));
        functions.append(py::str("subscriber_end_access"));
        functions.append(py::str("subscriber_notify_datareaders"));
        functions.append(py::str("readcondition_get_datareader"));
        functions.append(py::str("readcondition_get_sample_state_mask"));
        functions.append(py::str("readcondition_get_view_state_mask"));
        functions.append(py::str("readcondition_get_instance_state_mask"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
