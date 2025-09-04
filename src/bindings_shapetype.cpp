#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <cstring>

// ZRDDS headers
#include "ShapeType.h"
#include "ShapeTypeTypeSupport.h"
#include "ShapeTypeDataWriter.h"
#include "ShapeTypeDataReader.h"
#include "ReturnCode_t.h"
#include "DomainParticipant.h"
#include "Topic.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "DataWriter.h"
#include "DataReader.h"
#include "Duration_t.h"  // 添加这个头文件，因为Time_t是Duration_t的typedef
#include "ZRSequence.h"
#include "SampleInfo.h"

namespace py = pybind11;

// ShapeType module wrapper
PYBIND11_MODULE(_zrdds_shapetype, m) {
    m.doc() = "ZRDDS Python Wrapper - ShapeType Module";
    
    // 注意：Duration_t在basic模块中定义，这里不需要创建别名
    
    // Bind ShapeType struct
    py::class_<ShapeType>(m, "ShapeType")
        .def(py::init<>())
        .def_readwrite("x", &ShapeType::x)
        .def_readwrite("y", &ShapeType::y)
        .def_property("z", 
            [](const ShapeType& self) -> std::string {
                return self.z ? std::string(self.z) : std::string("");
            },
            [](ShapeType& self, const std::string& value) {
                // 释放旧的内存
                if (self.z) {
                    free(self.z);
                }
                // 分配新内存并复制字符串
                self.z = (DDS_Char*)malloc(value.length() + 1);
                if (self.z) {
                    strcpy(self.z, value.c_str());
                }
            })
        .def("__repr__", [](const ShapeType& self) {
            return "<ShapeType(x=" + std::to_string(self.x) + ", y=" + std::to_string(self.y) + ", z='" + (self.z ? std::string(self.z) : std::string("")) + "')>";
        });
    
    // Bind SampleInfo class
    py::class_<DDS::SampleInfo>(m, "SampleInfo")
        .def(py::init<>())
        .def_readwrite("sample_state", &DDS::SampleInfo::sample_state)
        .def_readwrite("view_state", &DDS::SampleInfo::view_state)
        .def_readwrite("instance_state", &DDS::SampleInfo::instance_state)
        .def_readwrite("valid_data", &DDS::SampleInfo::valid_data)
        .def_readwrite("source_timestamp", &DDS::SampleInfo::source_timestamp)
        .def_readwrite("instance_handle", &DDS::SampleInfo::instance_handle)
        .def_readwrite("publication_handle", &DDS::SampleInfo::publication_handle)
        .def_readwrite("disposed_generation_count", &DDS::SampleInfo::disposed_generation_count)
        .def_readwrite("no_writers_generation_count", &DDS::SampleInfo::no_writers_generation_count)
        .def_readwrite("sample_rank", &DDS::SampleInfo::sample_rank)
        .def_readwrite("generation_rank", &DDS::SampleInfo::generation_rank)
        .def_readwrite("absolute_generation_rank", &DDS::SampleInfo::absolute_generation_rank)
        .def("__repr__", [](const DDS::SampleInfo& self) {
            return "<DDS.SampleInfo(valid_data=" + std::to_string(self.valid_data) + ")>";
        });
    
    // Bind ShapeTypeTypeSupport class
    py::class_<ShapeTypeTypeSupport, std::unique_ptr<ShapeTypeTypeSupport, py::nodelete>>(m, "ShapeTypeTypeSupport")
        .def_static("get_instance", []() -> ShapeTypeTypeSupport* {
            return ShapeTypeTypeSupport::get_instance();
        })
        .def("register_type", [](ShapeTypeTypeSupport& self, DDS::DomainParticipant* participant, const char* type_name) -> DDS::ReturnCode_t {
            return self.register_type(participant, type_name);
        }, py::arg("participant"), py::arg("type_name") = nullptr)
        .def("get_type_name", &ShapeTypeTypeSupport::get_type_name)
        .def_static("finalize_instance", []() -> void {
            ShapeTypeTypeSupport::finalize_instance();
        });
    
    // Bind ShapeTypeDataWriter class
    py::class_<ShapeTypeDataWriter, DDS::DataWriter, std::unique_ptr<ShapeTypeDataWriter, py::nodelete>>(m, "ShapeTypeDataWriter")
        .def("write", [](ShapeTypeDataWriter& self, const ShapeType& data, DDS::InstanceHandle_t handle) -> DDS::ReturnCode_t {
            return self.write(data, handle);
        }, py::arg("data"), py::arg("handle") = DDS::HANDLE_NIL_NATIVE)
        .def("register_instance", [](ShapeTypeDataWriter& self, const ShapeType& data) -> DDS::InstanceHandle_t {
            return self.register_instance(data);
        }, py::arg("data"))
        .def("unregister_instance", [](ShapeTypeDataWriter& self, const ShapeType& data, DDS::InstanceHandle_t handle) -> DDS::ReturnCode_t {
            return self.unregister_instance(data, handle);
        }, py::arg("data"), py::arg("handle") = DDS::HANDLE_NIL_NATIVE)
        .def("dispose", [](ShapeTypeDataWriter& self, const ShapeType& data, DDS::InstanceHandle_t handle) -> DDS::ReturnCode_t {
            return self.dispose(data, handle);
        }, py::arg("data"), py::arg("handle") = DDS::HANDLE_NIL_NATIVE)
        .def("get_key_value", [](ShapeTypeDataWriter& self, ShapeType& data, DDS::InstanceHandle_t handle) -> DDS::ReturnCode_t {
            return self.get_key_value(data, handle);
        }, py::arg("data"), py::arg("handle"))
        .def("lookup_instance", [](ShapeTypeDataWriter& self, const ShapeType& data) -> DDS::InstanceHandle_t {
            return self.lookup_instance(data);
        }, py::arg("data"));
    
    // Bind ShapeTypeDataReader class
    py::class_<ShapeTypeDataReader, DDS::DataReader, std::unique_ptr<ShapeTypeDataReader, py::nodelete>>(m, "ShapeTypeDataReader")
        .def("read_next_sample", [](ShapeTypeDataReader& self, ShapeType& data, DDS::SampleInfo& sample_info) -> DDS::ReturnCode_t {
            return self.read_next_sample(data, sample_info);
        }, py::arg("data"), py::arg("sample_info"))
        .def("take_next_sample", [](ShapeTypeDataReader& self, ShapeType& data, DDS::SampleInfo& sample_info) -> DDS::ReturnCode_t {
            return self.take_next_sample(data, sample_info);
        }, py::arg("data"), py::arg("sample_info"))
        // Note: read() and take() methods require sequence types that are complex to bind
        // Use read_next_sample() and take_next_sample() for simpler usage
        .def("get_key_value", [](ShapeTypeDataReader& self, ShapeType& data, DDS::InstanceHandle_t handle) -> DDS::ReturnCode_t {
            return self.get_key_value(data, handle);
        }, py::arg("data"), py::arg("handle"))
        .def("lookup_instance", [](ShapeTypeDataReader& self, ShapeType& data) -> DDS::InstanceHandle_t {
            return self.lookup_instance(data);
        }, py::arg("data"));
    
    // Helper functions
    m.def("ShapeTypeInitialize", [](ShapeType& data) {
        ShapeTypeInitialize(&data);
    }, py::arg("data"), "Initialize ShapeType data");
    
    m.def("ShapeTypeFinalize", [](ShapeType& data) {
        ShapeTypeFinalize(&data);
    }, py::arg("data"), "Finalize ShapeType data");
    
    // 专门的ShapeType数据读取函数
    m.def("read_shapetype_data", [](DDS::DataReader* datareader) -> py::object {
        if (datareader == nullptr) {
            return py::none();
        }
        
        try {
            // 动态转换为ShapeTypeDataReader
            ShapeTypeDataReader* shapetype_reader = dynamic_cast<ShapeTypeDataReader*>(datareader);
            if (shapetype_reader == nullptr) {
                return py::none();
            }
            
            // 创建数据对象和样本信息
            ShapeType data;
            DDS::SampleInfo sample_info;
            
            // 尝试读取下一个样本
            DDS::ReturnCode_t ret = shapetype_reader->read_next_sample(data, sample_info);
            
            if (ret == DDS::RETCODE_OK) {
                // 检查样本是否有效
                if (sample_info.valid_data) {
                    // 返回ShapeType对象
                    return py::cast(data);
                } else {
                    return py::none(); // 样本无效
                }
            } else {
                return py::none(); // 读取失败
            }
        } catch (const std::exception& e) {
            return py::none();
        }
    }, py::arg("datareader"), "Read ShapeType data from DataReader");
    
    // Constants
    m.attr("HANDLE_NIL_NATIVE") = py::cast(DDS::HANDLE_NIL_NATIVE);
    
    // Initialize module
    m.def("init", []() {
        return true;
    }, "Initialize ShapeType DDS module");
    
    // Cleanup function
    m.def("finalize", []() {
        return true;
    }, "Finalize ShapeType DDS module");
    
    // Get API info
    m.def("get_api_info", []() {
        py::list info;
        info.append("ShapeType");
        info.append("ShapeTypeTypeSupport");
        info.append("ShapeTypeDataWriter");
        info.append("ShapeTypeDataReader");
        return info;
    }, "Get available API functions");
}
