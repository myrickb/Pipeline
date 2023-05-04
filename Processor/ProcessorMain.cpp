#include "ProcessorMain.hpp"
#include <iostream>

bool ProcessorMain::Initialize() {
    bool return_success = true;

    return return_success;
}// Initialize

bool ProcessorMain::Run(){
    bool return_success = true;

    std::cout << "reached processor main" << std::endl;

    return return_success;
}// Run

int main(int argc, char *argv[]) {
    
    std::cout << "Reached Processor main!" << std::endl;

    return 0;
}