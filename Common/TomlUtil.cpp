#include "TomlUtil.hpp"
#include <iostream>

bool TomlUtil::GetTomlTable(toml::v3::table& tomlTable, const std::string& tomlConfigPath){
    bool return_success = true;

    try{
        tomlTable = toml::parse_file(tomlConfigPath);
    }// try
    catch (const toml::parse_error& err) {
        std::cerr << "ERROR::TomlUtil::GetTomlTable: Error parsing TOML file: " << err.what() << std::endl;
        return_success = false;
    }// catch

    return return_success;
}// GetTomlTable

bool TomlUtil::GetProcessList(const toml::v3::table& tomlTable, std::vector<std::string>& processList){
    bool return_success = true;

    // Grab Process List
    if (!tomlTable.contains("General")){
        std::cerr << "ERROR::TomlUtil::GetProcessList: TOML file does not contain section 'General'" << std::endl;
        return_success = false;
    }// if
    else{
        auto generalTable = tomlTable["General"].as_table();
        if(generalTable->contains(TOML_CONFIG_VAR_PROCESS_LIST) == false) {
            std::cerr << "ERROR::TomlUtil::GetProcessList: TOML file does not contain section 'ProcessList'" << std::endl;
            return_success = false;
        }// if
        else {
            auto processListValue = generalTable->get(TOML_CONFIG_VAR_PROCESS_LIST);
            if(processListValue && processListValue->is_array()) {
                auto processListArray = processListValue->as_array();
                for (const auto& item : *processListArray) {
                    if (item.is_string()) {
                        processList.push_back(item.as_string()->get());
                    }// if
                }// for
            }// if
            else{
                std::cerr << "ERROR::TomlUtil:GetProcessList: Process List field from toml is not a list!" << std::endl;
                return_success = false;
            }// else
        }// else
    }// else

    return return_success;
}// GetProcessList

bool TomlUtil::GetTomlField(const toml::v3::table& tomlTable, const std::string& fieldName){
    bool return_success = true;

    return return_success;
}// GetTomlField