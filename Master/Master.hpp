#ifndef MASTER_HPP
#define MASTER_HPP

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<toml++/toml.h>
#include "TomlUtil.hpp"
class Master{
    public:
        bool Initialize(const std::string& tomlConfigPath);
        bool Run();

    private:
        std::vector<std::string> mProcessList;
        toml::v3::table mTomlTable;
};

#endif // MASTER_HPP