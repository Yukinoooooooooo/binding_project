cmake_minimum_required(VERSION 3.15)
project(zrdds_python_bindings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(ZRDDS_INCLUDE_DIR "$ENV{ZRDDS_HOME}/include")
set(ZRDDS_LIB_DIR "$ENV{ZRDDS_HOME}/lib")
set(pybind11_DIR ".venv/Lib/site-packages/pybind11/share/cmake/pybind11") 

# 开启全程序优化（CMake 会在 MSVC 下自动使用 /GL）
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# 设置要编译的模块类型
# 可选值: basic, topic, domain, waitset, subscribe, publish, listener, main
# 默认编译 basic 模块
if(NOT DEFINED MODULE_TYPE)
    set(MODULE_TYPE "basic")
endif()

# 根据模块类型设置源文件和模块名称
if(MODULE_TYPE STREQUAL "basic")
    set(SOURCE_FILE "src/bindings_basic.cpp")
    set(MODULE_NAME "_zrdds_basic")
    set(MODULE_DESCRIPTION "ZRDDS Basic Module (GuardCondition, WaitSet, ConditionSeq)")
elseif(MODULE_TYPE STREQUAL "topic")
    set(SOURCE_FILE "src/bindings_topic.cpp")
    set(MODULE_NAME "_zrdds_topic")
    set(MODULE_DESCRIPTION "ZRDDS Topic Module (DomainParticipant, Topic - Pure Topic functionality)")
elseif(MODULE_TYPE STREQUAL "domain")
    set(SOURCE_FILE "src/bindings_domain.cpp")
    set(MODULE_NAME "_zrdds_domain")
    set(MODULE_DESCRIPTION "ZRDDS Domain Module (DomainParticipant, DomainParticipantFactory)")
elseif(MODULE_TYPE STREQUAL "waitset")
    set(SOURCE_FILE "src/bindings_waitset.cpp")
    set(MODULE_NAME "_zrdds_waitset")
    set(MODULE_DESCRIPTION "ZRDDS WaitSet Module (WaitSet, Condition)")
elseif(MODULE_TYPE STREQUAL "subscribe")
    set(SOURCE_FILE "src/bindings_subscribe.cpp")
    set(MODULE_NAME "_zrdds_subscribe")
    set(MODULE_DESCRIPTION "ZRDDS Subscribe Module (DataReader, Subscriber, ReadCondition)")
elseif(MODULE_TYPE STREQUAL "publish")
    set(SOURCE_FILE "src/bindings_publish.cpp")
    set(MODULE_NAME "_zrdds_publish")
    set(MODULE_DESCRIPTION "ZRDDS Publish Module (DataWriter, Publisher)")
elseif(MODULE_TYPE STREQUAL "listener")
    set(SOURCE_FILE "src/bindings_listener.cpp")
    set(MODULE_NAME "_zrdds_listener")
    set(MODULE_DESCRIPTION "ZRDDS Listener Module (Listeners)")
elseif(MODULE_TYPE STREQUAL "activator")
    set(SOURCE_FILE "src/bindings_activator.cpp")
    set(MODULE_NAME "_zrdds_activator")
    set(MODULE_DESCRIPTION "ZRDDS Activation System (Unified Module Management)")

# elseif(MODULE_TYPE STREQUAL "main")
#     set(SOURCE_FILE "src/bindings_main.cpp")
#     set(MODULE_NAME "zrdds_python"
#     set(MODULE_DESCRIPTION "ZRDDS Main Module (Main functionality)"
else()
    message(FATAL_ERROR "Unknown MODULE_TYPE: ${MODULE_TYPE}. Supported types: basic, topic, domain, waitset, subscribe, publish, listener, activator, main")
endif()

# 显示当前编译的模块信息
message(STATUS "Building ZRDDS module: ${MODULE_NAME}")
message(STATUS "Source file: ${SOURCE_FILE}")
message(STATUS "Description: ${MODULE_DESCRIPTION}")

# 创建 pybind11 模块
pybind11_add_module(
    ${MODULE_NAME}
    MODULE
    ${SOURCE_FILE}
)

# 链接 ZRDDS 库
target_link_libraries(${MODULE_NAME} PRIVATE ${ZRDDS_LIB_DIR}/ZRDDSCppz_VS2019.lib) 

# 包含头文件目录
target_include_directories(${MODULE_NAME} PRIVATE ${ZRDDS_INCLUDE_DIR}/CPlusPlusInterface)
target_include_directories(${MODULE_NAME} PRIVATE ${ZRDDS_INCLUDE_DIR}/ZRDDSSecurityInterface)
target_include_directories(${MODULE_NAME} PRIVATE ${ZRDDS_INCLUDE_DIR}/ZRDDSCoreInterface)

# 复制编译后的文件到目标目录
add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying ${MODULE_NAME} .pyd to target folder..."
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${MODULE_NAME}> ${PROJECT_SOURCE_DIR}/zrpy/
    COMMENT "Copy ${MODULE_NAME} .pyd to source folder"
)

# 添加一个自定义目标来显示帮助信息
add_custom_target(show_help
    COMMAND ${CMAKE_COMMAND} -E echo "ZRDDS Python Bindings Build System"
    COMMAND ${CMAKE_COMMAND} -E echo "=================================="
    COMMAND ${CMAKE_COMMAND} -E echo "Usage:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=basic ..     # Build basic module (_zrdds_basic)"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=topic ..     # Build topic module (_zrdds_topic)"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=domain ..    # Build domain module (_zrdds_domain)"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=waitset ..   # Build waitset module (_zrdds_waitset)"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=subscribe .. # Build subscribe module (_zrdds_subscribe)"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=publish ..   # Build publish module (_zrdds_publish)"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=listener ..  # Build listener module (_zrdds_listener)"

    COMMAND ${CMAKE_COMMAND} -E echo "  cmake -DMODULE_TYPE=main ..      # Build main module (zrdds_python)"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Build commands:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build build --config Release"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build build --config Debug"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Current module: ${MODULE_NAME}"
    COMMAND ${CMAKE_COMMAND} -E echo "Source file: ${SOURCE_FILE}"
    COMMAND ${CMAKE_COMMAND} -E echo "Description: ${MODULE_DESCRIPTION}"
    COMMENT "Show build help information"
)