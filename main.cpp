#include "Master.hpp"
#include "iostream"

int main(int argc, char *argv[]) {
    
    if(argc != 2){
        std::cerr << "Incorrect number of arguments!" << std::endl;
        std::cerr << "Expected -> ./MainProcess nameOfToml.toml" << std::endl;
        return 1;
    }// if
    
    Master master;
    if(master.Initialize(argv[1]) == false){
        std::cerr << "ERROR::Master::Initialize: Failed to initialize Master!" << std::endl;
    }// if
    else{
        if(master.Run() == false){
            std::cerr << "ERROR::Master::Run: Run error Master!" << std::endl;
        }// if
    }// else
    

    return 0;
}