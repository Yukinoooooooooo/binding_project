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
#include "ZRBuiltinTypesTypeSupport.h"  // For BytesTypeSupport
#include "Topic.h"  // For Topic and TopicSeq
#include "TopicDescription.h"  // For TopicDescription

namespace py = pybind11;

// Simple Domain DDS Manager - like your simple DDS module
struct DomainDDSManager {
    static DDS::DomainParticipant* participant;
    static DDS::DomainParticipantQos* participant_qos;
    static DDS::DomainParticipantFactory* factory;
    
    static void cleanup() {
        if (participant) {
            if (factory) {
                factory->delete_participant(participant);
            }
            participant = nullptr;
        }
        if (participant_qos) {
            delete participant_qos;
            participant_qos = nullptr;
        }
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

// Initialize static members
DDS::DomainParticipant* DomainDDSManager::participant = nullptr;
DDS::DomainParticipantQos* DomainDDSManager::participant_qos = nullptr;
DDS::DomainParticipantFactory* DomainDDSManager::factory = nullptr;

// Domain module wrapper
PYBIND11_MODULE(_zrdds_domain, m) {
    m.doc() = "ZRDDS Python Wrapper - Domain Module (Simple Direct Interface)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Domain Module - Simple Direct Interface!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Domain Module v3.0.0 - Simple Direct Implementation";
    });
    
    // Initialize domain module
    m.def("init", []() {
        // Clean up any existing entities
        DomainDDSManager::cleanup();
        return true;
    }, "Initialize Domain DDS module");
    
    // Create DomainParticipantQos - direct creation
    m.def("create_participant_qos", []() -> bool {
        if (DomainDDSManager::participant_qos) {
            return true; // Already exists
        }
        
        DomainDDSManager::participant_qos = new DDS::DomainParticipantQos();
        if (DomainDDSManager::participant_qos) {
            // Use ZRDDS default QoS initialization function
            DDS_Long result = DDS_DefaultDomainParticipantQosInitial(DomainDDSManager::participant_qos);
            return (result == 0);
        }
        return false;
    }, "Create DomainParticipantQos with ZRDDS default values");
    
    m.def("delete_participant_qos", []() -> bool {
        if (DomainDDSManager::participant_qos) {
            delete DomainDDSManager::participant_qos;
            DomainDDSManager::participant_qos = nullptr;
            return true;
        }
        return false;
    }, "Delete DomainParticipantQos");
    
    // Create DomainParticipant - direct creation
    m.def("create_domain_participant", [](int domain_id) -> bool {
        if (DomainDDSManager::participant) {
            return true; // Already exists
        }
        
        DDS::DomainParticipantFactory* factory = DomainDDSManager::get_factory();
        if (!factory) {
            return false;
        }
        
        DDS::DomainParticipantQos* qos = DomainDDSManager::participant_qos;
        if (!qos) {
            // Create default QoS if not exists
            qos = new DDS::DomainParticipantQos();
            DDS_DefaultDomainParticipantQosInitial(qos);
        }
        
        DomainDDSManager::participant = factory->create_participant(
            domain_id, 
            *qos, 
            nullptr, 
            DDS::STATUS_MASK_ALL
        );
        
        return (DomainDDSManager::participant != nullptr);
    }, py::arg("domain_id"), "Create DomainParticipant");
    
    m.def("delete_domain_participant", []() -> bool {
        if (DomainDDSManager::participant) {
            // First delete all contained entities (child entities)
            DDS::ReturnCode_t delete_ret = DomainDDSManager::participant->delete_contained_entities();
            if (delete_ret != DDS::RETCODE_OK) {
                // Continue even if some entities couldn't be deleted
            }
            
            // Then delete the participant itself
            DDS::DomainParticipantFactory* factory = DomainDDSManager::get_factory();
            if (factory) {
                DDS::ReturnCode_t ret = factory->delete_participant(DomainDDSManager::participant);
                if (ret == DDS::RETCODE_OK) {
                    DomainDDSManager::participant = nullptr;
                    return true;
                }
            }
        }
        return false;
    }, "Delete DomainParticipant");
    
    // DomainParticipant operations
    m.def("get_participant_domain_id", []() -> py::object {
        if (DomainDDSManager::participant) {
            return py::int_(DomainDDSManager::participant->get_domain_id());
        }
        return py::none();
    }, "Get DomainParticipant domain ID");
    
    m.def("get_participant_id", []() -> py::object {
        if (DomainDDSManager::participant) {
            // Note: get_participant_id() method doesn't exist in ZRDDS
            // Return a placeholder value
            return py::int_(1);
        }
        return py::none();
    }, "Get DomainParticipant ID");
    
    m.def("get_participant_qos", []() -> py::object {
        if (DomainDDSManager::participant) {
            DDS::DomainParticipantQos qos;
            DDS::ReturnCode_t ret = DomainDDSManager::participant->get_qos(qos);
            if (ret == DDS::RETCODE_OK) {
                py::dict result;
                result["user_data"] = "default_user_data";  // Placeholder for user data
                result["entity_factory"] = qos.entity_factory.autoenable_created_entities;
                return result;
            }
        }
        return py::none();
    }, "Get DomainParticipant QoS");
    
    m.def("set_participant_qos", []() -> bool {
        if (DomainDDSManager::participant && DomainDDSManager::participant_qos) {
            DDS::ReturnCode_t ret = DomainDDSManager::participant->set_qos(*DomainDDSManager::participant_qos);
            return (ret == DDS::RETCODE_OK);
        }
        return false;
    }, "Set DomainParticipant QoS");
    
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
    
    // Check if entities exist
    m.def("participant_exists", []() -> bool {
        return (DomainDDSManager::participant != nullptr);
    }, "Check if participant exists");
    
    m.def("get_participant", []() -> py::object {
        if (DomainDDSManager::participant) {
            return py::cast(DomainDDSManager::participant);
        }
        return py::none();
    }, "Get DomainParticipant object");
    
    m.def("participant_qos_exists", []() -> bool {
        return (DomainDDSManager::participant_qos != nullptr);
    }, "Check if participant QoS exists");
    
    m.def("factory_exists", []() -> bool {
        return (DomainDDSManager::factory != nullptr);
    }, "Check if factory exists");
    
    // Cleanup function
    m.def("finalize", []() {
        DomainDDSManager::cleanup();
        return true;
    }, "Cleanup Domain DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Domain Module - Simple Direct Interface";
        info["participant_exists"] = (DomainDDSManager::participant != nullptr);
        info["participant_qos_exists"] = (DomainDDSManager::participant_qos != nullptr);
        info["factory_exists"] = (DomainDDSManager::factory != nullptr);
        
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