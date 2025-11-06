/**
 * @file method_example.cpp
 * @brief Method Example Plugin Implementation | 方法插件示例实现
 */

#include "method_example.hpp"
#include <po_core/po_logger.hpp>
#include <po_core/ProfilerManager.hpp> // Profiler system | 性能分析系统
#include <sstream>

namespace PluginMethods
{

    MethodExample::MethodExample()
    {
        // 定义需要的输入数据类型 | Define required input data types
        // 设置为nullptr表示需要这种类型的输入，但尚未提供
        // Setting to nullptr indicates this type is required but not yet provided
        required_package_["data_tracks"] = nullptr;

        // 加载默认配置文件 (如果存在) | Load default config file (if exists)
        InitializeDefaultConfigPath();
    }

    DataPtr MethodExample::Run()
    {
        try
        {
            LOG_INFO_ZH << "[MethodExample] === 开始示例处理 ===";
            LOG_INFO_EN << "[MethodExample] === Starting example processing ===";
            DisplayConfigInfo();

            // 1. 获取输入数据 (MethodPreset已处理检查)
            // Get input data (MethodPreset has handled validation)
            // 推荐使用GetRequiredDataPtr简化访问 | Recommended: use GetRequiredDataPtr for simplified access
            auto tracks = GetRequiredDataPtr<Tracks>("data_tracks");

            // 检查数据有效性 | Validate data
            if (!tracks)
            {
                LOG_ERROR_ZH << "[MethodExample] 错误：缺少必需的输入数据";
                LOG_ERROR_EN << "[MethodExample] Error: Missing required input data";
                return nullptr;
            }

            LOG_INFO_ZH << "[MethodExample] 获取到轨迹数据，包含 " << tracks->size() << " 条轨迹";
            LOG_INFO_EN << "[MethodExample] Retrieved tracks data with " << tracks->size() << " tracks";

            // 2. 获取配置参数 | Get configuration parameters
            // 正确：在这里通过函数参数提供默认值
            // Correct: Provide default values via function parameters here
            std::string output_folder = GetOptionAsPath("output_folder", "", "output/method_example");
            bool enable_processing = GetOptionAsBool("enable_processing", true);
            bool enable_profiling = GetOptionAsBool("enable_profiling", true);
            int max_iterations = GetOptionAsIndexT("max_iterations", 10);
            double threshold = GetOptionAsDouble("threshold", 0.5);

            LOG_INFO_ZH << "[MethodExample] 配置参数:";
            LOG_INFO_ZH << "  输出文件夹: " << output_folder;
            LOG_INFO_ZH << "  启用处理: " << (enable_processing ? "是" : "否");
            LOG_INFO_ZH << "  启用性能分析: " << (enable_profiling ? "是" : "否");
            LOG_INFO_ZH << "  最大迭代次数: " << max_iterations;
            LOG_INFO_ZH << "  阈值: " << threshold;
            LOG_INFO_EN << "[MethodExample] Configuration parameters:";
            LOG_INFO_EN << "  Output folder: " << output_folder;
            LOG_INFO_EN << "  Enable processing: " << (enable_processing ? "Yes" : "No");
            LOG_INFO_EN << "  Enable profiling: " << (enable_profiling ? "Yes" : "No");
            LOG_INFO_EN << "  Max iterations: " << max_iterations;
            LOG_INFO_EN << "  Threshold: " << threshold;

            if (!enable_processing)
            {
                LOG_WARNING_ZH << "[MethodExample] 处理已禁用，跳过算法执行";
                LOG_WARNING_EN << "[MethodExample] Processing disabled, skipping algorithm execution";
                return nullptr;
            }

            // 性能分析：开始会话（自动使用方法标签，默认只统计时间）
            // Performance analysis: Start session (automatically uses method labels, defaults to TIME only)
            POSDK_START(enable_profiling);

            // 3. 创建输出目录 | Create output directory
            PROFILER_STAGE("initialization"); // 标记初始化阶段 | Mark initialization stage
            if (!output_folder.empty())
            {
                std::filesystem::path output_path(output_folder);
                std::filesystem::create_directories(output_path);
                LOG_INFO_ZH << "[MethodExample] 已创建输出目录: " << output_folder;
                LOG_INFO_EN << "[MethodExample] Created output directory: " << output_folder;
            }

            // 4. 实现核心算法逻辑... | Implement core algorithm logic...
            PROFILER_STAGE("data_processing"); // 标记数据处理阶段 | Mark data processing stage
            LOG_INFO_ZH << "[MethodExample] 开始处理数据...";
            LOG_INFO_EN << "[MethodExample] Starting data processing...";

            // 示例：简单的数据处理
            // Example: Simple data processing
            size_t processed_count = 0;
            for (size_t iter = 0; iter < static_cast<size_t>(max_iterations); ++iter)
            {
                // 模拟处理过程 | Simulate processing
                if (iter % 5 == 0)
                {
                    LOG_DEBUG_ZH << "[MethodExample] 迭代 " << iter << "/" << max_iterations;
                    LOG_DEBUG_EN << "[MethodExample] Iteration " << iter << "/" << max_iterations;
                }
                processed_count++;
            }

            LOG_INFO_ZH << "[MethodExample] 处理完成，共处理 " << processed_count << " 次迭代";
            LOG_INFO_EN << "[MethodExample] Processing completed, processed " << processed_count << " iterations";

            // 性能分析：结束会话（自动提交数据）
            // Performance analysis: End session (automatically submits data)
            PROFILER_END();

            // 5. 创建并返回结果数据
            // Create and return result data
            // 注意：如果不希望修改输入数据，可以先深拷贝DataPtr
            // Note: If you don't want to modify input data, deep copy DataPtr first
            // 或者创建新的数据对象返回 | Or create and return new data object
            auto result_data = std::make_shared<DataMap<std::string>>("处理完成", "data_map_string");

            // 性能分析：打印当前会话统计（可选）
            // Performance analysis: Print current session statistics (optional)
            PROFILER_PRINT_STATS(enable_profiling);

            LOG_INFO_ZH << "[MethodExample] === 示例处理完成 ===";
            LOG_INFO_EN << "[MethodExample] === Example processing completed ===";

            return result_data;
        }
        catch (const std::exception &e)
        {
            LOG_ERROR_ZH << "[MethodExample] 错误: " << e.what();
            LOG_ERROR_EN << "[MethodExample] Error: " << e.what();
            return nullptr;
        }
    }

    std::string MethodExample::ProcessData(const std::string &input_data) const
    {
        // 示例处理函数 | Example processing function
        std::ostringstream oss;
        oss << "Processed: " << input_data;
        return oss.str();
    }

} // namespace PluginMethods

// 插件注册 - 自动从CMake读取PLUGIN_NAME
// Plugin registration - automatically reads PLUGIN_NAME from CMake
// 插件类型："method_example"（来自CMake）
// Plugin type: "method_example" (from CMake)
// 文件名：posdk_plugin_method_example.{so|dylib|dll}
// File name: posdk_plugin_method_example.{so|dylib|dll}
REGISTRATION_PLUGIN(PluginMethods::MethodExample)
