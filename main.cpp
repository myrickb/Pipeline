#include "Master.hpp"
#include "iostream"

int main() {
    Master master;

    if(master.Initialize() == false){
        std::cerr << "[ERROR]:Master::Initialize: Failed to initialize Master!" << std::endl;
    }

    if(master.Run() == false){
        std::cerr << "[ERROR]:Master::Run: Run error Master!" << std::endl;
    }

    return 0;
}