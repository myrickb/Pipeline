#ifndef MASTER_HPP
#define MASTER_HPP

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<thread>
#include<functional>
#include<toml++/toml.h>
#include<unistd.h>
#include <sys/wait.h>
#include <map>
#include <csignal>
#include <atomic>
#include "TomlUtil.hpp"
#include "ProcessHandler.hpp"

class Master{
    public:
        Master();
        bool Initialize(const std::string& tomlConfigPath);
        bool Run();

    private:

        static constexpr const char* CONSUMER_PROCESS_NAME ="Consumer";
        static constexpr const char* PROCESSOR_PROCESS_NAME="Processor";
        static constexpr const char* PRODUCER_PROCESS_NAME ="Producer";

        std::vector<std::string> mProcessList;
        toml::v3::table mTomlTable;

        ProcessHandler* mProcessHandler;
};

#endif // MASTER_HPP