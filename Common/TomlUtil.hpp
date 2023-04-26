#ifndef TOMLUTIL_HPP
#define TOMLUTIL_HPP

#include<toml++/toml.h>
class TomlUtil{
    public:
        static bool GetTomlTable(toml::v3::table& tomlTable, const std::string& tomlConfigPath);
        static bool GetProcessList(const toml::v3::table& tomlTable, std::vector<std::string>& processList);
        static bool GetTomlField(const toml::v3::table& tomlTable, const std::string& fieldName);
    
    private:
        static constexpr const char* TOML_CONFIG_VAR_PROCESS_LIST="process_list";
        static constexpr const char* TOML_CONFIG_VAR_INPUT_IP="input_ip";
        static constexpr const char* TOML_CONFIG_VAR_OUTPUT_IP="output_ip";
        static constexpr const char* TOML_CONFIG_VAR_INPUT_PORT="input_port";
        static constexpr const char* TOML_CONFIG_VAR_OUTPUT_PORT="output_port";
        static constexpr const char* TOML_CONFIG_VAR_MODULE_NAME="module_name";
};

#endif // TOMLUTIL_HPP