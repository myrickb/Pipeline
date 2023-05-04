#include "ConsumerMain.hpp"
#include <iostream>

ConsumerMain::ConsumerMain()
{

}// ConsumerMain

bool ConsumerMain::Initialize() {
    bool return_success = true;

    return return_success;
}// Initialize

bool ConsumerMain::Run(){
    bool return_success = true;

    std::cout << "reached consumer main" << std::endl;

    return return_success;
}// Run

int main(int argc, char *argv[]) {
    
    std::cout << "Reached Consumer main!" << std::endl;
    ConsumerMain consumerMain;


    return 0;
}