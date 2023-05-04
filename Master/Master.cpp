#include "Master.hpp"
#include <iostream>

Master::Master(){}

bool Master::Initialize(const std::string& tomlConfigPath) {
    bool return_success = true;

    std::cout << "One" << std::endl;
    // Confirm toml file exists
    std::ifstream file(tomlConfigPath);
    if(file.good() == false){
        std::cerr << "ERROR::Master::Initialize: Toml File Path: " << tomlConfigPath << " not found!" << std::endl;
        return_success = false;
    }// if
    else{
        // Parse toml file
        std::cout << "Type two here" << std::endl;
        if(TomlUtil::GetTomlTable(mTomlTable,tomlConfigPath) == false){
            std::cerr << "ERROR::Master::Initialize: Could not grab toml table from toml file!" << std::endl;
            return_success = false;
        }// if
        std::cout << "Type three here" << std::endl;
        // Get ProcessList
        if(TomlUtil::GetProcessList(mTomlTable, mProcessList) == false){
            std::cerr << "ERROR::Master::Initialize: Could not get process list from toml file" << std::endl;
            return_success = false;
        }// if
        
    }// else

    // Initialize ProcessHandler
    // if(mProcessHandler->Initialize() == false){
    //     std::cerr << "ERROR:Master::Initialize: Could not initialize process handler!" << std::endl;
    //     return_success = false;
    // }// if

    return return_success;
}// Initialize

bool Master::Run(){
    bool return_success = true;

    std::cout << "We have reached master!" << std::endl;


    //ProcessManager process_manager

    mProcessHandler->StartThreads(mProcessList);

    return return_success;
}// Run
