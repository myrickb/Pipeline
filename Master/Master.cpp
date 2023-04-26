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


    std::vector<std::thread> threads;

    std::vector<std::function<void()>> functions;

    for (const auto &process_name : mProcessList) {
        if (process_name == Master::PRODUCER_PROCESS_NAME) {
            ProducerMain *producer = new ProducerMain();
            functions.emplace_back(std::bind(&ProducerMain::Run, producer));
        } else if (process_name == Master::CONSUMER_PROCESS_NAME) {
            ConsumerMain *consumer = new ConsumerMain();
            functions.emplace_back(std::bind(&ConsumerMain::Run, consumer));
        } else if (process_name == Master::PROCESSOR_PROCESS_NAME) {
            ProcessorMain *processor = new ProcessorMain();
            functions.emplace_back(std::bind(&ProcessorMain::Run, processor));
        } else {
            std::cerr << "Unknown process: " << process_name << std::endl;
        }
    }

    for (auto &function : functions) {
        threads.emplace_back(function);
    }

    // Wait for all threads to finish
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }




    return return_success;
}// Run
