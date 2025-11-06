/**
 * @file method_example.hpp
 * @brief Method Example Plugin | 方法插件示例
 * @details 这是一个简单的示例插件，展示如何开发PoSDK方法插件
 *          This is a simple example plugin demonstrating how to develop PoSDK method plugins
 * @copyright Copyright (c) 2024 Qi Cai
 * Licensed under the Mozilla Public License Version 2.0
 */

#pragma once

#include <po_core.hpp>
#include <po_core/po_logger.hpp>
#include <filesystem>

namespace PluginMethods
{
    using namespace PoSDK;
    using namespace Interface;
    using namespace types;

    /**
     * @brief Method Example Plugin | 方法插件示例
     *
     * 这是一个简单的示例插件，展示如何：
     * This is a simple example plugin demonstrating how to:
     * - 继承 MethodPresetProfiler 基类
     *   Inherit from MethodPresetProfiler base class
     * - 定义必需的输入数据类型
     *   Define required input data types
     * - 实现 Run() 方法
     *   Implement Run() method
     * - 使用配置参数
     *   Use configuration parameters
     * - 使用性能分析宏
     *   Use performance profiling macros
     * - 返回结果数据
     *   Return result data
     */
    class MethodExample : public MethodPresetProfiler
    {
    public:
        MethodExample();
        ~MethodExample() override = default;

        /**
         * @brief 运行示例算法 | Run example algorithm
         * @return 处理完成的数据指针 | Data pointer after processing
         */
        DataPtr Run() override;

        // GetType() is automatically implemented by REGISTRATION_PLUGIN macro
        // GetType() 由 REGISTRATION_PLUGIN 宏自动实现
        const std::string &GetType() const override;

    private:
        /**
         * @brief 示例处理函数 | Example processing function
         * @param input_data 输入数据 | Input data
         * @return 处理结果 | Processing result
         */
        std::string ProcessData(const std::string &input_data) const;
    };

} // namespace PluginMethods
