#ifndef MASTER_HPP
#define MASTER_HPP

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<thread>
#include<atomic>
#include<csignal>
#include<functional>
#include<toml++/toml.h>
#include "TomlUtil.hpp"
#include "ConsumerMain.hpp"
#include "ProcessorMain.hpp"
#include "ProducerMain.hpp"
class Master{
    public:
        bool Initialize(const std::string& tomlConfigPath);
        bool Run();

    private:

        static constexpr const char* CONSUMER_PROCESS_NAME ="Consumer";
        static constexpr const char* PROCESSOR_PROCESS_NAME="Processor";
        static constexpr const char* PRODUCER_PROCESS_NAME ="Producer";

        std::vector<std::string> mProcessList;
        toml::v3::table mTomlTable;
};

#endif // MASTER_HPP