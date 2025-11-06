# ==============================================================================
# MethodExample Plugin CMakeLists.txt
# 方法插件示例构建配置
# ==============================================================================

cmake_minimum_required(VERSION 3.15)

# 包含插件配置工具
include(../../cmake/plugin-config.cmake)

# ------------------------------------------------------------------------------
# MethodExample插件
# ------------------------------------------------------------------------------
# 注意：基础库（PoSDK::po_core, PoSDK::pomvg_converter, PoSDK::pomvg_common）会自动链接
# Note: Base libraries (PoSDK::po_core, PoSDK::pomvg_converter, PoSDK::pomvg_common) are automatically linked
add_posdk_plugin(method_example
    PLUGIN_TYPE methods
    SOURCES
        method_example.cpp
    HEADERS
        method_example.hpp
    COMPILE_DEFINITIONS
        PLUGIN_VERSION="1.0.0"
        $<$<CONFIG:Debug>:DEBUG_BUILD=1>
)

# ------------------------------------------------------------------------------
# 插件特定配置
# ------------------------------------------------------------------------------

# 插件信息摘要
message(STATUS "MethodExample Plugin Configuration:")
message(STATUS "  Plugin Name: method_example")
message(STATUS "  Plugin Type: methods")
message(STATUS "  Plugin File: posdk_plugin_method_example.dylib/.so/.dll")
message(STATUS "  Plugin Folder: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "  Sources: method_example.cpp")
message(STATUS "  Headers: method_example.hpp")

# 调试信息
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building MethodExample plugin in Debug mode")
endif()

# 测试支持（如果启用测试）
if(BUILD_TESTING)
    message(STATUS "MethodExample plugin: Testing enabled")
endif()

# 文档生成（如果启用文档）
if(BUILD_DOCUMENTATION)
    message(STATUS "MethodExample plugin: Documentation enabled")
endif()

