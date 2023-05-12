#include "ImageProducerModule.hpp"
#include <iostream>

bool ImageProducerModule::Initialize() {
    bool return_success = true;

    return return_success;
}

bool ImageProducerModule::Run(DataMessage::ImageDataMessage& imageDataMessage){
    bool return_success = true;

    std::cout << "reached producer main" << std::endl;

    return return_success;
}
