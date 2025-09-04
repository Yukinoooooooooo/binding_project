#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <cstring>

// 定义必要的宏以启用GuardCondition和WaitSet
#define _ZRDDS_INCLUDE_GUARD_CONDITION
#define _ZRDDS_INCLUDE_WAITSET

// ZRDDS C++ headers
#include "Entity.h"
#include "Condition.h"
#include "WaitSet.h"    
#include "DomainEntity.h"
#include "StatusKindMask.h"
#include "ReturnCode_t.h"
#include "ZRSequence.h"
#include "ZRDDSCppWrapper.h"

// 包含状态常量定义
#include "SampleStateKind.h"
#include "ViewStateKind.h"
#include "InstanceStateKind.h"
#include "SampleStateMask.h"
#include "ViewStateMask.h"
#include "InstanceStateMask.h"

namespace py = pybind11;

// Note: Basic module provides class bindings only
// Users should create and manage basic DDS entities through appropriate methods

// Basic module wrapper
PYBIND11_MODULE(_zrdds_basic, m) {
    m.doc() = "ZRDDS Python Wrapper - Basic Module (Complete Interface)";
    
    // Bind Entity class with nodelete policy (protected destructor)
    py::class_<DDS::Entity, std::unique_ptr<DDS::Entity, py::nodelete>>(m, "Entity")
        .def("get_statuscondition", &DDS::Entity::get_statuscondition,
             "Get status condition associated with this entity")
        .def("get_status_changes", &DDS::Entity::get_status_changes,
             "Get status changes since last status retrieval")
        .def("enable", &DDS::Entity::enable,
             "Manually enable this entity")
        .def("get_instance_handle", &DDS::Entity::get_instance_handle,
             "Get unique identifier for this entity")
        .def("__repr__", [](const DDS::Entity& self) {
            return "<DDS.Entity>";
        });
    
    // Bind DomainEntity class with nodelete policy (protected destructor)
    py::class_<DDS::DomainEntity, DDS::Entity, std::unique_ptr<DDS::DomainEntity, py::nodelete>>(m, "DomainEntity")
        .def("__repr__", [](const DDS::DomainEntity& self) {
            return "<DDS.DomainEntity>";
        });
    
    // Bind Condition class with nodelete policy (protected destructor)
    py::class_<DDS::Condition, std::unique_ptr<DDS::Condition, py::nodelete>>(m, "Condition")
        .def("get_trigger_value", &DDS::Condition::get_trigger_value,
             "Get current trigger status")
        .def("__repr__", [](const DDS::Condition& self) {
            return "<DDS.Condition>";
        });
    
    // Bind StatusCondition class with nodelete policy (protected destructor)
    py::class_<DDS::StatusCondition, DDS::Condition, std::unique_ptr<DDS::StatusCondition, py::nodelete>>(m, "StatusCondition")
        .def("set_enabled_statuses", &DDS::StatusCondition::set_enabled_statuses,
             py::arg("mask"), "Set user interested statuses by bit mask")
        .def("get_enabled_statuses", &DDS::StatusCondition::get_enabled_statuses,
             "Get previously set interested statuses")
        .def("get_entity", &DDS::StatusCondition::get_entity,
             "Get entity associated with status condition")
        .def("__repr__", [](const DDS::StatusCondition& self) {
            return "<DDS.StatusCondition>";
        });
    
    // Bind GuardCondition class with nodelete policy (protected destructor)
    py::class_<DDS::GuardCondition, DDS::Condition, std::unique_ptr<DDS::GuardCondition, py::nodelete>>(m, "GuardCondition")
        .def(py::init<>(), "Default constructor for non-triggered guard condition")
        .def("set_trigger_value", &DDS::GuardCondition::set_trigger_value,
             py::arg("value"), "Manually set trigger status")
        .def("get_trigger_value", &DDS::GuardCondition::get_trigger_value,
             "Implement base class abstract method")
        .def("__repr__", [](const DDS::GuardCondition& self) {
            return "<DDS.GuardCondition>";
        });
    

    
    // Bind WaitSet class with nodelete policy (protected destructor)
    py::class_<DDS::WaitSet, std::unique_ptr<DDS::WaitSet, py::nodelete>>(m, "WaitSet")
        .def(py::init<>(), "Create WaitSet")
        .def("wait", [](DDS::WaitSet& self, DDS::ConditionSeq& active_conditions, const DDS::Duration_t& timeout) -> DDS::ReturnCode_t {
            return self.wait(active_conditions, timeout);
        }, py::arg("active_conditions"), py::arg("timeout"), "Wait for conditions")
        .def("attach_condition", &DDS::WaitSet::attach_condition,
             py::arg("condition"), "Attach condition to WaitSet")
        .def("detach_condition", &DDS::WaitSet::detach_condition,
             py::arg("condition"), "Detach condition from WaitSet")
        .def("get_conditions", &DDS::WaitSet::get_conditions,
             py::arg("attached_conditions"), "Get attached conditions")
        .def("__repr__", [](const DDS::WaitSet& self) {
            return "<DDS.WaitSet>";
        });
    
    // Bind ConditionSeq class
    py::class_<DDS::ConditionSeq>(m, "ConditionSeq")
        .def(py::init<>(), "Create condition sequence")
        .def("length", [](const DDS::ConditionSeq& self) {
            return ConditionSeq_get_length(&self);
        }, "Get sequence length")
        .def("maximum", [](const DDS::ConditionSeq& self) {
            return ConditionSeq_get_maximum(&self);
        }, "Get sequence maximum length")
        .def("set_length", [](DDS::ConditionSeq& self, DDS_Long length) {
            return ConditionSeq_set_length(&self, length);
        }, py::arg("length"), "Set sequence length")
        .def("__getitem__", [](const DDS::ConditionSeq& self, DDS_Long index) {
            if (index >= 0 && index < ConditionSeq_get_length(&self)) {
                DDS::ConditionPtr* ptr = ConditionSeq_get_reference(&self, index);
                return ptr ? *ptr : nullptr;
            }
            throw py::index_error("Index out of range");
        }, py::arg("index"), "Get condition at specified index")
        .def("__setitem__", [](DDS::ConditionSeq& self, DDS_Long index, DDS::ConditionPtr condition) {
            if (index >= 0 && index < ConditionSeq_get_length(&self)) {
                DDS::ConditionPtr* ptr = ConditionSeq_get_reference(&self, index);
                if (ptr) *ptr = condition;
            } else {
                throw py::index_error("Index out of range");
            }
        }, py::arg("index"), py::arg("condition"), "Set condition at specified index")
        .def("__repr__", [](const DDS::ConditionSeq& self) {
            return "<DDS.ConditionSeq>";
        });
    
    // Constants - 暂时只定义最基本的常量
    // 注意：STATUS_MASK_NONE 和 STATUS_MASK_ALL 已在 domain 模块中定义，这里不再重复
    // m.attr("STATUS_MASK_NONE") = DDS_STATUS_MASK_NONE;
    // m.attr("STATUS_MASK_ALL") = DDS_STATUS_MASK_ALL;
    
    // 使用 py::enum_ 来绑定枚举常量 - 这是更推荐的方式
    py::enum_<DDS_ReturnCode_t>(m, "ReturnCode")
        .value("RETCODE_OK", DDS_RETCODE_OK)
        .value("RETCODE_ERROR", DDS_RETCODE_ERROR)
        .value("RETCODE_BAD_PARAMETER", DDS_RETCODE_BAD_PARAMETER)
        .value("RETCODE_PRECONDITION_NOT_MET", DDS_RETCODE_PRECONDITION_NOT_MET)
        .value("RETCODE_TIMEOUT", DDS_RETCODE_TIMEOUT)
        .value("RETCODE_NO_DATA", DDS_RETCODE_NO_DATA)
        .value("RETCODE_ALREADY_DELETED", DDS_RETCODE_ALREADY_DELETED)
        .value("RETCODE_NOT_ENABLED", DDS_RETCODE_NOT_ENABLED)
        .value("RETCODE_IMMUTABLE_POLICY", DDS_RETCODE_IMMUTABLE_POLICY)
        .value("RETCODE_INCONSISTENT", DDS_RETCODE_INCONSISTENT)
        .value("RETCODE_OUT_OF_RESOURCES", DDS_RETCODE_OUT_OF_RESOURCES)
        .value("RETCODE_UNSUPPORTED", DDS_RETCODE_UNSUPPORTED);
    
    // 为了向后兼容，也直接暴露这些常量作为模块属性
    m.attr("RETCODE_OK") = DDS_RETCODE_OK;
    m.attr("RETCODE_ERROR") = DDS_RETCODE_ERROR;
    m.attr("RETCODE_BAD_PARAMETER") = DDS_RETCODE_BAD_PARAMETER;
    
    // Duration constants
    m.attr("DURATION_INFINITE_SEC") = DDS_DURATION_INFINITE_SEC;
    m.attr("DURATION_INFINITE_NSEC") = DDS_DURATION_INFINITE_NSEC;
    m.attr("DURATION_ZERO_SEC") = DDS_DURATION_ZERO_SEC;
    m.attr("DURATION_ZERO_NSEC") = DDS_DURATION_ZERO_NSEC;
    
    // Sample state constants - 暂时注释掉，避免引用未定义的常量
    // m.attr("READ_SAMPLE_STATE") = DDS_READ_SAMPLE_STATE;
    // m.attr("NOT_READ_SAMPLE_STATE") = DDS_NOT_READ_SAMPLE_STATE;
    // m.attr("ANY_SAMPLE_STATE") = DDS_ANY_SAMPLE_STATE;
    
    // View state constants - 暂时注释掉，避免引用未定义的常量
    // m.attr("NEW_VIEW_STATE") = DDS_NEW_VIEW_STATE;
    // m.attr("NOT_NEW_VIEW_STATE") = DDS_NOT_NEW_VIEW_STATE;
    // m.attr("ANY_VIEW_STATE") = DDS_ANY_VIEW_STATE;
    
    // Instance state constants - 暂时注释掉，避免引用未定义的常量
    // m.attr("ALIVE_INSTANCE_STATE") = DDS_ALIVE_INSTANCE_STATE;
    // m.attr("NOT_ALIVE_DISPOSED_INSTANCE_STATE") = DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE;
    // m.attr("NOT_ALIVE_NO_WRITERS_INSTANCE_STATE") = DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE;
    // m.attr("ANY_INSTANCE_STATE") = DDS_ANY_INSTANCE_STATE;
    
    // Initialize basic module
    m.def("init", []() {
        return true;
    }, "Initialize Basic DDS module");
    
    // Cleanup function
    m.def("finalize", []() {
        return true;
    }, "Cleanup Basic DDS module");
    
    // API info - 恢复API信息函数
    m.def("get_api_info", []() {
        py::dict info;
        info["message"] = "ZRDDS Basic Module - Complete Interface";
        return info;
    });
}