#include "Master.hpp"
#include <iostream>

bool Master::Initialize(const std::string& tomlConfigPath) {
    bool return_success = true;

    // Confirm toml file exists
    std::ifstream file(tomlConfigPath);
    if(file.good() == false){
        std::cerr << "ERROR::Master::Initialize: Toml File Path: " << tomlConfigPath << " not found!" << std::endl;
        return_success = false;
    }// if
    else{
        // Parse toml file
        if(TomlUtil::GetTomlTable(mTomlTable,tomlConfigPath) == false){
            std::cerr << "ERROR::Master::Initialize: Could not grab toml table from toml file!" << std::endl;
            return_success = false;
        }// if

        // Get ProcessList
        if(TomlUtil::GetProcessList(mTomlTable, mProcessList) == false){
            std::cerr << "ERROR::Master::Initialize: Could not get process list from toml file" << std::endl;
            return_success = false;
        }// if
        
    }// else

    return return_success;
}// Initialize

bool Master::Run(){
    bool return_success = true;

    std::cout << "We have reached master!" << std::endl;




    return return_success;
}// Run
