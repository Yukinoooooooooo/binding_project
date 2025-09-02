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
#include "Duration_t.h"
#include "ZRDDSCppWrapper.h"

namespace py = pybind11;

// Global storage for domain DDS entities
struct DomainDDSManager {
    static std::map<int, DDS::DomainParticipant*> participants;
    static std::map<int, DDS::DomainParticipantQos*> participant_qos;
    static DDS::DomainParticipantFactory* factory;
    static std::map<std::string, int> module_registrations;  // Module name -> participant ID mapping
    
    static int next_id;
    
    static int generate_id() { return ++next_id; }
    
    static void cleanup() {
        // Clean up participants
        for (auto& pair : participants) {
            if (pair.second) {
                DDS::DomainParticipantFactory* factory = get_factory();
                if (factory) {
                    factory->delete_participant(pair.second);
                }
            }
        }
        
        // Clean up QoS objects
        for (auto& pair : participant_qos) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clear all maps
        participants.clear();
        participant_qos.clear();
        
        // Finalize factory instance
        if (factory) {
            DDS::DomainParticipantFactory::finalize_instance();
            factory = nullptr;
        }
    }
    
    static DDS::DomainParticipantFactory* get_factory() {
        if (!factory) {
            factory = DDS::DomainParticipantFactory::get_instance();
        }
        return factory;
    }
};

std::map<int, DDS::DomainParticipant*> DomainDDSManager::participants;
std::map<int, DDS::DomainParticipantQos*> DomainDDSManager::participant_qos;
DDS::DomainParticipantFactory* DomainDDSManager::factory = nullptr;
std::map<std::string, int> DomainDDSManager::module_registrations;
int DomainDDSManager::next_id = 6000;

// Domain module wrapper
PYBIND11_MODULE(_zrdds_domain, m) {
    m.doc() = "ZRDDS Python Wrapper - Domain Module (C++ Interface with Factory Pattern)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Domain Module with Factory Pattern!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Domain Module v2.0.0 - Factory Pattern Implementation";
    });
    
    // Initialize domain module
    m.def("init", []() {
        // Clean up any existing entities
        DomainDDSManager::cleanup();
        return true;
    }, "Initialize Domain DDS module");
    
    // Factory functions for DomainParticipantQos
    m.def("create_participant_qos", []() -> int {
        DDS::DomainParticipantQos* qos = new DDS::DomainParticipantQos();
        if (qos) {
            // Use ZRDDS default QoS initialization function
            DDS_Long result = DDS_DefaultDomainParticipantQosInitial(qos);
            if (result != 0) {
                delete qos;
                return -1;
            }
            
            int id = DomainDDSManager::generate_id();
            DomainDDSManager::participant_qos[id] = qos;
            return id;
        }
        return -1;
    }, "Create DomainParticipantQos with ZRDDS default values and return ID");
    
    m.def("delete_participant_qos", [](int qos_id) -> bool {
        auto it = DomainDDSManager::participant_qos.find(qos_id);
        if (it != DomainDDSManager::participant_qos.end()) {
            if (it->second) {
                delete it->second;
            }
            DomainDDSManager::participant_qos.erase(it);
            return true;
        }
        return false;
    }, py::arg("qos_id"), "Delete DomainParticipantQos by ID");
    
    // Factory functions for DomainParticipant
    m.def("create_domain_participant", [](int domain_id, int qos_id = -1) -> int {
        DDS::DomainParticipantFactory* factory = DomainDDSManager::get_factory();
        if (!factory) {
            return -1;
        }
        
        DDS::DomainParticipantQos* qos = nullptr;
        if (qos_id != -1) {
            auto qos_it = DomainDDSManager::participant_qos.find(qos_id);
            if (qos_it != DomainDDSManager::participant_qos.end()) {
                qos = qos_it->second;
            }
        }
        
        DDS::DomainParticipant* participant = factory->create_participant(domain_id, qos ? *qos : DDS::DomainParticipantQos(), nullptr, DDS::STATUS_MASK_ALL);
        if (participant) {
            int id = DomainDDSManager::generate_id();
            DomainDDSManager::participants[id] = participant;
            return id;
        }
        return -1;
    }, py::arg("domain_id"), py::arg("qos_id") = -1, "Create DomainParticipant and return ID");
    
    m.def("delete_domain_participant", [](int participant_id) -> bool {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end()) {
            if (it->second) {
                // First delete all contained entities (child entities)
                DDS::ReturnCode_t delete_ret = it->second->delete_contained_entities();
                if (delete_ret != DDS::RETCODE_OK) {
                    // Continue even if some entities couldn't be deleted
                }
                
                // Then delete the participant itself
                DDS::DomainParticipantFactory* factory = DomainDDSManager::get_factory();
                if (factory) {
                    DDS::ReturnCode_t ret = factory->delete_participant(it->second);
                    if (ret == DDS::RETCODE_OK) {
                        DomainDDSManager::participants.erase(it);
                        return true;
                    }
                }
            }
        }
        return false;
    }, py::arg("participant_id"), "Delete DomainParticipant by ID");
    
    // DomainParticipant operations
    m.def("get_participant_domain_id", [](int participant_id) -> py::object {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end() && it->second) {
            return py::int_(it->second->get_domain_id());
        }
        return py::none();
    }, py::arg("participant_id"), "Get DomainParticipant domain ID");
    
    m.def("get_participant_id", [](int participant_id) -> py::object {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end() && it->second) {
            // Note: get_participant_id() method doesn't exist in ZRDDS
            // Return a placeholder value
            return py::int_(participant_id);
        }
        return py::none();
    }, py::arg("participant_id"), "Get DomainParticipant ID");
    
    m.def("get_participant_qos", [](int participant_id) -> py::object {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end() && it->second) {
            DDS::DomainParticipantQos qos;
            DDS::ReturnCode_t ret = it->second->get_qos(qos);
            if (ret == DDS::RETCODE_OK) {
                py::dict result;
                result["user_data"] = "default_user_data";  // Placeholder for user data
                result["entity_factory"] = qos.entity_factory.autoenable_created_entities;
                return result;
            }
        }
        return py::none();
    }, py::arg("participant_id"), "Get DomainParticipant QoS");
    
    m.def("set_participant_qos", [](int participant_id, int qos_id) -> bool {
        auto participant_it = DomainDDSManager::participants.find(participant_id);
        auto qos_it = DomainDDSManager::participant_qos.find(qos_id);
        
        if (participant_it != DomainDDSManager::participants.end() && 
            qos_it != DomainDDSManager::participant_qos.end() &&
            participant_it->second && qos_it->second) {
            
            DDS::ReturnCode_t ret = participant_it->second->set_qos(*qos_it->second);
            return (ret == DDS::RETCODE_OK);
        }
        return false;
    }, py::arg("participant_id"), py::arg("qos_id"), "Set DomainParticipant QoS");
    
    // Cross-module access functions for pure ID-based communication
    m.def("get_participant_by_id", [](int participant_id) -> py::object {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end() && it->second) {
            // Return participant ID for cross-module communication
            return py::cast(participant_id);
        }
        return py::none();
    }, py::arg("participant_id"), "Get participant by ID for cross-module communication");
    
    m.def("register_participant_for_module", [](int participant_id, const std::string& module_name) -> bool {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end() && it->second) {
            // Store module registration info
            DomainDDSManager::module_registrations[module_name] = participant_id;
            return true;
        }
        return false;
    }, py::arg("participant_id"), py::arg("module_name"), "Register participant for specific module");
    
    m.def("get_registered_participant_id", [](const std::string& module_name) -> int {
        auto it = DomainDDSManager::module_registrations.find(module_name);
        if (it != DomainDDSManager::module_registrations.end()) {
            return it->second;
        }
        return -1;
    }, py::arg("module_name"), "Get registered participant ID for module");
    
    // Factory operations
    m.def("get_factory_instance", []() -> bool {
        DDS::DomainParticipantFactory* factory = DomainDDSManager::get_factory();
        return (factory != nullptr);
    }, "Get DomainParticipantFactory instance");
    
    m.def("finalize_factory_instance", []() -> bool {
        DDS::ReturnCode_t ret = DDS::DomainParticipantFactory::finalize_instance();
        if (ret == DDS::RETCODE_OK) {
            DomainDDSManager::factory = nullptr;
            return true;
        }
        return false;
    }, "Finalize DomainParticipantFactory instance");
    
    // Time and Duration utilities
    m.def("create_time", [](DDS_LongLong seconds, DDS_ULong nanoseconds) -> py::dict {
        py::dict time;
        time["sec"] = seconds;
        time["nanosec"] = nanoseconds;
        return time;
    }, py::arg("seconds"), py::arg("nanoseconds"), "Create Time dictionary");
    
    m.def("create_duration", [](DDS_LongLong seconds, DDS_ULong nanoseconds) -> py::dict {
        py::dict duration;
        duration["sec"] = seconds;
        duration["nanosec"] = nanoseconds;
        return duration;
    }, py::arg("seconds"), py::arg("nanoseconds"), "Create Duration dictionary");
    
    m.def("create_infinite_duration", []() -> py::dict {
        py::dict duration;
        duration["sec"] = DDS_DURATION_INFINITE_SEC;
        duration["nanosec"] = DDS_DURATION_INFINITE_NSEC;
        return duration;
    }, "Create infinite Duration dictionary");
    
    m.def("create_zero_duration", []() -> py::dict {
        py::dict duration;
        duration["sec"] = 0;
        duration["nanosec"] = 0;
        return duration;
    }, "Create zero Duration dictionary");
    
    // Utility functions
    m.def("get_participant_count", []() {
        return static_cast<int>(DomainDDSManager::participants.size());
    }, "Get number of domain participants");
    
    m.def("get_participant_qos_count", []() {
        return static_cast<int>(DomainDDSManager::participant_qos.size());
    }, "Get number of participant QoS objects");
    
    // Check if participant exists (ID-based only, no pointer passing)
    m.def("participant_exists", [](int participant_id) -> bool {
        auto it = DomainDDSManager::participants.find(participant_id);
        return (it != DomainDDSManager::participants.end() && it->second != nullptr);
    }, py::arg("participant_id"), "Check if participant exists by ID");
    
    // Domain isolation management: provide participant access for other modules (internal use)
    m.def("get_participant_for_module", [](int participant_id, const std::string& module_name) -> py::object {
        auto it = DomainDDSManager::participants.find(participant_id);
        if (it != DomainDDSManager::participants.end() && it->second) {
            // Verify module is registered
            auto reg_it = DomainDDSManager::module_registrations.find(module_name);
            if (reg_it != DomainDDSManager::module_registrations.end() && reg_it->second == participant_id) {
                return py::cast(static_cast<void*>(it->second));
            }
        }
        return py::none();
    }, py::arg("participant_id"), py::arg("module_name"), "Get participant pointer for registered module (domain isolation)");
    
    // Cleanup function
    m.def("finalize", []() {
        DomainDDSManager::cleanup();
        return true;
    }, "Cleanup Domain DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Domain Module with Factory Pattern - C++ Interface";
        info["participant_count"] = DomainDDSManager::participants.size();
        info["participant_qos_count"] = DomainDDSManager::participant_qos.size();
        info["factory_available"] = (DomainDDSManager::factory != nullptr);
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_participant_qos"));
        functions.append(py::str("delete_participant_qos"));
        functions.append(py::str("create_domain_participant"));
        functions.append(py::str("delete_domain_participant"));
        functions.append(py::str("get_participant_domain_id"));
        functions.append(py::str("get_participant_id"));
        functions.append(py::str("get_participant_qos"));
        functions.append(py::str("set_participant_qos"));
        functions.append(py::str("get_factory_instance"));
        functions.append(py::str("finalize_factory_instance"));
        functions.append(py::str("create_time"));
        functions.append(py::str("create_duration"));
        functions.append(py::str("create_infinite_duration"));
        functions.append(py::str("create_zero_duration"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
