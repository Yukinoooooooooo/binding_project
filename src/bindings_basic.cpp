#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// ZRDDS C++ headers
#include "Entity.h"
#include "Condition.h"
#include "WaitSet.h"
#include "DomainEntity.h"
#include "StatusKindMask.h"
#include "SampleStateKind.h"
#include "ViewStateKind.h"
#include "InstanceStateKind.h"
#include "InstanceHandle_t.h"
#include "Duration_t.h"
#include "ReturnCode_t.h"
#include "ZRDDSCppWrapper.h"

namespace py = pybind11;

// Global storage for basic DDS entities
struct BasicDDSManager {
    static std::map<int, DDS::GuardCondition*> guard_conditions;
    static std::map<int, DDS::WaitSet*> wait_sets;
    static std::map<int, DDS::ConditionSeq*> condition_seqs;
    
    static int next_id;
    
    static int generate_id() { return ++next_id; }
    
    static void cleanup() {
        // Clean up guard conditions
        for (auto& pair : guard_conditions) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clean up wait sets
        for (auto& pair : wait_sets) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clean up condition sequences
        for (auto& pair : condition_seqs) {
            if (pair.second) {
                delete pair.second;
            }
        }
        
        // Clear all maps
        guard_conditions.clear();
        wait_sets.clear();
        condition_seqs.clear();
    }
};

std::map<int, DDS::GuardCondition*> BasicDDSManager::guard_conditions;
std::map<int, DDS::WaitSet*> BasicDDSManager::wait_sets;
std::map<int, DDS::ConditionSeq*> BasicDDSManager::condition_seqs;
int BasicDDSManager::next_id = 2000;

// Basic module wrapper
PYBIND11_MODULE(_zrdds_basic, m) {
    m.doc() = "ZRDDS Python Wrapper - Basic Module (C++ Interface with Factory Pattern)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Basic Module with Factory Pattern!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Basic Module v2.0.0 - Factory Pattern Implementation";
    });
    
    // Initialize basic module
    m.def("init", []() {
        // Clean up any existing entities
        BasicDDSManager::cleanup();
        return true;
    }, "Initialize Basic DDS module");
    
    // Factory functions for GuardCondition
    m.def("create_guard_condition", []() -> int {
        DDS::GuardCondition* condition = new DDS::GuardCondition();
        if (condition) {
            int id = BasicDDSManager::generate_id();
            BasicDDSManager::guard_conditions[id] = condition;
            return id;
        }
        return -1;
    }, "Create GuardCondition and return ID");
    
    m.def("delete_guard_condition", [](int condition_id) -> bool {
        auto it = BasicDDSManager::guard_conditions.find(condition_id);
        if (it != BasicDDSManager::guard_conditions.end()) {
            if (it->second) {
                delete it->second;
            }
            BasicDDSManager::guard_conditions.erase(it);
            return true;
        }
        return false;
    }, py::arg("condition_id"), "Delete GuardCondition by ID");
    
    m.def("set_guard_condition_trigger", [](int condition_id, bool value) -> bool {
        auto it = BasicDDSManager::guard_conditions.find(condition_id);
        if (it != BasicDDSManager::guard_conditions.end() && it->second) {
            DDS::ReturnCode_t ret = it->second->set_trigger_value(value);
            return (ret == DDS_RETCODE_OK);
        }
        return false;
    }, py::arg("condition_id"), py::arg("value"), "Set GuardCondition trigger value");
    
    m.def("get_guard_condition_trigger", [](int condition_id) -> py::object {
        auto it = BasicDDSManager::guard_conditions.find(condition_id);
        if (it != BasicDDSManager::guard_conditions.end() && it->second) {
            return py::bool_(it->second->get_trigger_value());
        }
        return py::none();
    }, py::arg("condition_id"), "Get GuardCondition trigger value");
    
    // Factory functions for WaitSet
    m.def("create_waitset", []() -> int {
        DDS::WaitSet* waitset = new DDS::WaitSet();
        if (waitset) {
            int id = BasicDDSManager::generate_id();
            BasicDDSManager::wait_sets[id] = waitset;
            return id;
        }
        return -1;
    }, "Create WaitSet and return ID");
    
    m.def("delete_waitset", [](int waitset_id) -> bool {
        auto it = BasicDDSManager::wait_sets.find(waitset_id);
        if (it != BasicDDSManager::wait_sets.end()) {
            if (it->second) {
                delete it->second;
            }
            BasicDDSManager::wait_sets.erase(it);
            return true;
        }
        return false;
    }, py::arg("waitset_id"), "Delete WaitSet by ID");
    
    m.def("attach_condition", [](int waitset_id, int condition_id) -> bool {
        auto waitset_it = BasicDDSManager::wait_sets.find(waitset_id);
        auto condition_it = BasicDDSManager::guard_conditions.find(condition_id);
        
        if (waitset_it != BasicDDSManager::wait_sets.end() && 
            condition_it != BasicDDSManager::guard_conditions.end() &&
            waitset_it->second && condition_it->second) {
            
            DDS::ReturnCode_t ret = waitset_it->second->attach_condition(condition_it->second);
            return (ret == DDS_RETCODE_OK);
        }
        return false;
    }, py::arg("waitset_id"), py::arg("condition_id"), "Attach condition to WaitSet");
    
    m.def("detach_condition", [](int waitset_id, int condition_id) -> bool {
        auto waitset_it = BasicDDSManager::wait_sets.find(waitset_id);
        auto condition_it = BasicDDSManager::guard_conditions.find(condition_id);
        
        if (waitset_it != BasicDDSManager::wait_sets.end() && 
            condition_it != BasicDDSManager::guard_conditions.end() &&
            waitset_it->second && condition_it->second) {
            
            DDS::ReturnCode_t ret = waitset_it->second->detach_condition(condition_it->second);
            return (ret == DDS_RETCODE_OK);
        }
        return false;
    }, py::arg("waitset_id"), py::arg("condition_id"), "Detach condition from WaitSet");
    
    m.def("wait_for_conditions", [](int waitset_id, int timeout_seconds, int timeout_nanoseconds) -> py::object {
        auto waitset_it = BasicDDSManager::wait_sets.find(waitset_id);
        if (waitset_it == BasicDDSManager::wait_sets.end() || !waitset_it->second) {
            return py::none();
        }
        
        // Create duration
        DDS::Duration_t timeout;
        timeout.sec = timeout_seconds;
        timeout.nanosec = timeout_nanoseconds;
        
        // Create condition sequence
        DDS::ConditionSeq active_conditions;
        
        // Wait
        DDS::ReturnCode_t ret = waitset_it->second->wait(active_conditions, timeout);
        
        if (ret == DDS::RETCODE_TIMEOUT) {
            return py::bool_(false);
        } else if (ret != DDS_RETCODE_OK) {
            return py::none();
        }
        
        // Return list of active condition IDs
        py::list result;
        DDS::Long length = ConditionSeq_get_length(&active_conditions);
        for (DDS::Long i = 0; i < length; ++i) {
            DDS::ConditionPtr* ptr = ConditionSeq_get_reference(&active_conditions, i);
            if (ptr && *ptr) {
                // Find the condition ID
                for (const auto& pair : BasicDDSManager::guard_conditions) {
                    if (pair.second == *ptr) {
                        result.append(py::int_(pair.first));
                        break;
                    }
                }
            }
        }
        
        return result;
    }, py::arg("waitset_id"), py::arg("timeout_seconds") = 1, py::arg("timeout_nanoseconds") = 0, "Wait for conditions");
    
    // Factory functions for ConditionSeq
    m.def("create_condition_seq", []() -> int {
        DDS::ConditionSeq* seq = new DDS::ConditionSeq();
        if (seq) {
            int id = BasicDDSManager::generate_id();
            BasicDDSManager::condition_seqs[id] = seq;
            return id;
        }
        return -1;
    }, "Create ConditionSeq and return ID");
    
    m.def("delete_condition_seq", [](int seq_id) -> bool {
        auto it = BasicDDSManager::condition_seqs.find(seq_id);
        if (it != BasicDDSManager::condition_seqs.end()) {
            if (it->second) {
                delete it->second;
            }
            BasicDDSManager::condition_seqs.erase(it);
            return true;
        }
        return false;
    }, py::arg("seq_id"), "Delete ConditionSeq by ID");
    
    m.def("condition_seq_get_length", [](int seq_id) -> py::object {
        auto it = BasicDDSManager::condition_seqs.find(seq_id);
        if (it != BasicDDSManager::condition_seqs.end() && it->second) {
            return py::int_(ConditionSeq_get_length(it->second));
        }
        return py::none();
    }, py::arg("seq_id"), "Get ConditionSeq length");
    
    m.def("condition_seq_set_length", [](int seq_id, DDS_Long length) -> bool {
        auto it = BasicDDSManager::condition_seqs.find(seq_id);
        if (it != BasicDDSManager::condition_seqs.end() && it->second) {
            return ConditionSeq_set_length(it->second, length);
        }
        return false;
    }, py::arg("seq_id"), py::arg("length"), "Set ConditionSeq length");
    
    // Duration utility functions
    m.def("create_duration", [](DDS_Long seconds, DDS_ULong nanoseconds) -> py::dict {
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
    
    // Status check functions
    m.def("check_return_code", [](DDS_ReturnCode_t ret, const std::string& operation) -> bool {
        if (ret != DDS_RETCODE_OK) {
            PyErr_SetString(PyExc_RuntimeError, 
                ("ZRDDS operation failed: " + operation + " (error code: " + std::to_string(ret) + ")").c_str());
            return false;
        }
        return true;
    }, py::arg("ret"), py::arg("operation"), "Check DDS return code");
    
    m.def("throw_zrdds_exception", [](DDS_ReturnCode_t ret, const std::string& operation) {
        std::string error_msg = "ZRDDS operation failed: " + operation + " (error code: " + std::to_string(ret) + ")";
        PyErr_SetString(PyExc_RuntimeError, error_msg.c_str());
        throw py::error_already_set();
    }, py::arg("ret"), py::arg("operation"), "Throw ZRDDS exception");
    
    // StatusKindMask constants
    m.attr("STATUS_MASK_NONE") = DDS_STATUS_MASK_NONE;
    m.attr("STATUS_MASK_ALL") = DDS_STATUS_MASK_ALL;
    
    // ReturnCode constants (commented out to avoid initialization issues)
    // m.attr("RETCODE_OK") = DDS_RETCODE_OK;
    // m.attr("RETCODE_ERROR") = DDS_RETCODE_ERROR;
    // m.attr("RETCODE_UNSUPPORTED") = DDS_RETCODE_UNSUPPORTED;
    // m.attr("RETCODE_BAD_PARAMETER") = DDS_RETCODE_BAD_PARAMETER;
    // m.attr("RETCODE_PRECONDITION_NOT_MET") = DDS_RETCODE_PRECONDITION_NOT_MET;
    // m.attr("RETCODE_OUT_OF_RESOURCES") = DDS_RETCODE_OUT_OF_RESOURCES;
    // m.attr("RETCODE_NOT_ENABLED") = DDS_RETCODE_NOT_ENABLED;
    // m.attr("RETCODE_IMMUTABLE_POLICY") = DDS_RETCODE_IMMUTABLE_POLICY;
    // m.attr("RETCODE_ALREADY_DELETED") = DDS_RETCODE_ALREADY_DELETED;
    // m.attr("RETCODE_TIMEOUT") = DDS_RETCODE_TIMEOUT;
    // m.attr("RETCODE_NO_DATA") = DDS_RETCODE_NO_DATA;
    // m.attr("RETCODE_ILLEGAL_OPERATION") = DDS_RETCODE_ILLEGAL_OPERATION;
    
    // Utility functions
    m.def("get_guard_condition_count", []() {
        return static_cast<int>(BasicDDSManager::guard_conditions.size());
    }, "Get number of guard conditions");
    
    m.def("get_waitset_count", []() {
        return static_cast<int>(BasicDDSManager::wait_sets.size());
    }, "Get number of wait sets");
    
    m.def("get_condition_seq_count", []() {
        return static_cast<int>(BasicDDSManager::condition_seqs.size());
    }, "Get number of condition sequences");
    
    // Cleanup function
    m.def("finalize", []() {
        BasicDDSManager::cleanup();
        return true;
    }, "Cleanup Basic DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Basic Module with Factory Pattern - C++ Interface";
        info["guard_condition_count"] = BasicDDSManager::guard_conditions.size();
        info["waitset_count"] = BasicDDSManager::wait_sets.size();
        info["condition_seq_count"] = BasicDDSManager::condition_seqs.size();
        
        py::list functions;
        functions.append(py::str("init"));
        functions.append(py::str("create_guard_condition"));
        functions.append(py::str("delete_guard_condition"));
        functions.append(py::str("set_guard_condition_trigger"));
        functions.append(py::str("get_guard_condition_trigger"));
        functions.append(py::str("create_waitset"));
        functions.append(py::str("delete_waitset"));
        functions.append(py::str("attach_condition"));
        functions.append(py::str("detach_condition"));
        functions.append(py::str("wait_for_conditions"));
        functions.append(py::str("create_condition_seq"));
        functions.append(py::str("delete_condition_seq"));
        functions.append(py::str("condition_seq_get_length"));
        functions.append(py::str("condition_seq_set_length"));
        functions.append(py::str("create_duration"));
        functions.append(py::str("create_infinite_duration"));
        functions.append(py::str("create_zero_duration"));
        functions.append(py::str("finalize"));
        info["main_functions"] = functions;
        return info;
    });
}
