# MethodExample Plugin

This is a simple PoSDK method plugin example demonstrating how to develop method plugins using the plugin directory structure.

## Directory Structure

```
MethodExample/
├── CMakeLists.txt          # Plugin build configuration
├── method_example.hpp      # Plugin header file
├── method_example.cpp      # Plugin implementation file
├── method_example.ini      # Plugin configuration file
└── README.md               # Documentation
```

## Features

- Uses latest single-parameter plugin registration
- Inherits from `MethodPresetProfiler` base class
- Supports configuration files
- Supports performance profiling
- Complete error handling
- Bilingual logging support

## Building

The plugin will be automatically discovered and built, no additional configuration needed.

## Usage

```cpp
// Create plugin instance
auto method = FactoryMethod::Create("method_example");

// Set input data
auto tracks_data = FactoryData::Create("data_tracks");
// ... populate tracks_data ...
method->SetRequiredPackage("data_tracks", tracks_data);

// Set configuration parameters (optional)
method->SetMethodOption("output_folder", "my_output");
method->SetMethodOption("max_iterations", "20");

// Execute algorithm
auto result = method->Build();
```

## Configuration File Example

See `method_example.ini` file.

## Key Points

1. **Plugin Registration**: Use single-parameter `REGISTRATION_PLUGIN(PluginMethods::MethodExample)`, plugin name is automatically defined by CMake

2. **CMakeLists.txt**: Use `add_posdk_plugin()` function, base libraries are automatically linked

3. **Input Data**: Define `required_package_["data_type"] = nullptr` in constructor

4. **Get Data**: Recommended to use `GetRequiredDataPtr<T>("data_type")` for simplified access

5. **Configuration**: Use `GetOptionAsString()`, `GetOptionAsBool()` etc. to get configuration

6. **Performance Profiling**: Use `POSDK_START()`, `PROFILER_STAGE()`, `PROFILER_END()` macros for performance profiling
   - `POSDK_START(enable_profiling)`: Start profiling session, automatically uses method labels, defaults to TIME only
   - `PROFILER_STAGE("stage_name")`: Add stage checkpoint, automatically calculates interval performance metrics
   - `PROFILER_END()`: End session and automatically submit data to ProfilerManager
   - `PROFILER_PRINT_STATS(enable_profiling)`: Print current session statistics (optional)

7. **Return Result**: Create new data object to return, e.g., `std::make_shared<DataMap<std::string>>(...)`

## Performance Profiling Macro Usage Example

```cpp
DataPtr MethodExample::Run()
{
    // Get profiling configuration
    bool enable_profiling = GetOptionAsBool("enable_profiling", true);
    
    // Start profiling session
    POSDK_START(enable_profiling);
    
    // Add stage checkpoint
    PROFILER_STAGE("initialization");
    // ... initialization code ...
    
    PROFILER_STAGE("data_processing");
    // ... data processing code ...
    
    // End profiling session
    PROFILER_END();
    
    // Print statistics (optional)
    PROFILER_PRINT_STATS(enable_profiling);
    
    return result_data;
}
```

For more information about performance profiling macros, see `ProfilerManager.hpp` and `ProfilerInfo.hpp`.
