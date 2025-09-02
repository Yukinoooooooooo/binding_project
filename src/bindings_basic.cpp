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

// Simple DDS Manager - like your simple DDS module
struct BasicDDSManager {
    static DDS::GuardCondition* guard_condition;
    static DDS::WaitSet* waitset;
    static DDS::ConditionSeq* condition_seq;
    
    static void cleanup() {
        if (condition_seq) {
            delete condition_seq;
            condition_seq = nullptr;
        }
        if (waitset) {
            delete waitset;
            waitset = nullptr;
        }
        if (guard_condition) {
            delete guard_condition;
            guard_condition = nullptr;
        }
    }
};

// Initialize static members
DDS::GuardCondition* BasicDDSManager::guard_condition = nullptr;
DDS::WaitSet* BasicDDSManager::waitset = nullptr;
DDS::ConditionSeq* BasicDDSManager::condition_seq = nullptr;

// Basic module wrapper
PYBIND11_MODULE(_zrdds_basic, m) {
    m.doc() = "ZRDDS Python Wrapper - Basic Module (Simple Direct Interface)";
    
    // Basic functions
    m.def("hello", []() {
        return "Hello from ZRDDS Basic Module - Simple Direct Interface!";
    });
    
    m.def("get_version", []() {
        return "ZRDDS Basic Module v3.0.0 - Simple Direct Implementation";
    });
    
    // Initialize basic module
    m.def("init", []() {
        // Clean up any existing entities
        BasicDDSManager::cleanup();
        return true;
    }, "Initialize Basic DDS module");
    
    // Create GuardCondition - direct creation
    m.def("create_guard_condition", []() -> bool {
        if (BasicDDSManager::guard_condition) {
            return true; // Already exists
        }
        
        BasicDDSManager::guard_condition = new DDS::GuardCondition();
        return (BasicDDSManager::guard_condition != nullptr);
    }, "Create GuardCondition");
    
    m.def("delete_guard_condition", []() -> bool {
        if (BasicDDSManager::guard_condition) {
            delete BasicDDSManager::guard_condition;
            BasicDDSManager::guard_condition = nullptr;
            return true;
        }
        return false;
    }, "Delete GuardCondition");
    
    m.def("set_guard_condition_trigger", [](bool value) -> bool {
        if (BasicDDSManager::guard_condition) {
            DDS::ReturnCode_t ret = BasicDDSManager::guard_condition->set_trigger_value(value);
            return (ret == DDS_RETCODE_OK);
        }
        return false;
    }, py::arg("value"), "Set GuardCondition trigger value");
    
    m.def("get_guard_condition_trigger", []() -> py::object {
        if (BasicDDSManager::guard_condition) {
            return py::bool_(BasicDDSManager::guard_condition->get_trigger_value());
        }
        return py::none();
    }, "Get GuardCondition trigger value");
    
    // Create WaitSet - direct creation
    m.def("create_waitset", []() -> bool {
        if (BasicDDSManager::waitset) {
            return true; // Already exists
        }
        
        BasicDDSManager::waitset = new DDS::WaitSet();
        return (BasicDDSManager::waitset != nullptr);
    }, "Create WaitSet");
    
    m.def("delete_waitset", []() -> bool {
        if (BasicDDSManager::waitset) {
            delete BasicDDSManager::waitset;
            BasicDDSManager::waitset = nullptr;
            return true;
        }
        return false;
    }, "Delete WaitSet");
    
    m.def("attach_condition", []() -> bool {
        if (BasicDDSManager::waitset && BasicDDSManager::guard_condition) {
            DDS::ReturnCode_t ret = BasicDDSManager::waitset->attach_condition(BasicDDSManager::guard_condition);
            return (ret == DDS_RETCODE_OK);
        }
        return false;
    }, "Attach guard condition to WaitSet");
    
    m.def("detach_condition", []() -> bool {
        if (BasicDDSManager::waitset && BasicDDSManager::guard_condition) {
            DDS::ReturnCode_t ret = BasicDDSManager::waitset->detach_condition(BasicDDSManager::guard_condition);
            return (ret == DDS_RETCODE_OK);
        }
        return false;
    }, "Detach guard condition from WaitSet");
    
    m.def("wait_for_conditions", [](int timeout_seconds, int timeout_nanoseconds) -> py::object {
        if (!BasicDDSManager::waitset) {
            return py::none();
        }
        
        // Create duration
        DDS::Duration_t timeout;
        timeout.sec = timeout_seconds;
        timeout.nanosec = timeout_nanoseconds;
        
        // Create condition sequence
        DDS::ConditionSeq active_conditions;
        
        // Wait
        DDS::ReturnCode_t ret = BasicDDSManager::waitset->wait(active_conditions, timeout);
        
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
                // Check if it's our guard condition
                if (*ptr == BasicDDSManager::guard_condition) {
                    result.append(py::int_(1)); // Guard condition ID
                }
            }
        }
        
        return result;
    }, py::arg("timeout_seconds") = 1, py::arg("timeout_nanoseconds") = 0, "Wait for conditions");
    
    // Create ConditionSeq - direct creation
    m.def("create_condition_seq", []() -> bool {
        if (BasicDDSManager::condition_seq) {
            return true; // Already exists
        }
        
        BasicDDSManager::condition_seq = new DDS::ConditionSeq();
        return (BasicDDSManager::condition_seq != nullptr);
    }, "Create ConditionSeq");
    
    m.def("delete_condition_seq", []() -> bool {
        if (BasicDDSManager::condition_seq) {
            delete BasicDDSManager::condition_seq;
            BasicDDSManager::condition_seq = nullptr;
            return true;
        }
        return false;
    }, "Delete ConditionSeq");
    
    m.def("condition_seq_get_length", []() -> py::object {
        if (BasicDDSManager::condition_seq) {
            return py::int_(ConditionSeq_get_length(BasicDDSManager::condition_seq));
        }
        return py::none();
    }, "Get ConditionSeq length");
    
    m.def("condition_seq_set_length", [](DDS_Long length) -> bool {
        if (BasicDDSManager::condition_seq) {
            return ConditionSeq_set_length(BasicDDSManager::condition_seq, length);
        }
        return false;
    }, py::arg("length"), "Set ConditionSeq length");
    
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
    
    // Check if entities exist
    m.def("guard_condition_exists", []() -> bool {
        return (BasicDDSManager::guard_condition != nullptr);
    }, "Check if guard condition exists");
    
    m.def("waitset_exists", []() -> bool {
        return (BasicDDSManager::waitset != nullptr);
    }, "Check if waitset exists");
    
    m.def("condition_seq_exists", []() -> bool {
        return (BasicDDSManager::condition_seq != nullptr);
    }, "Check if condition sequence exists");
    
    // Cleanup function
    m.def("finalize", []() {
        BasicDDSManager::cleanup();
        return true;
    }, "Cleanup Basic DDS module");
    
    // API info
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Basic Module - Simple Direct Interface";
        info["guard_condition_exists"] = (BasicDDSManager::guard_condition != nullptr);
        info["waitset_exists"] = (BasicDDSManager::waitset != nullptr);
        info["condition_seq_exists"] = (BasicDDSManager::condition_seq != nullptr);
        
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