#include "ConsumerMain.hpp"
#include <iostream>

ConsumerMain::ConsumerMain()
{

}// ConsumerMain

bool ConsumerMain::Initialize() {
    bool return_success = true;

    // TODO: Read in output addr and port through toml config 

    // Default output address and port...
    mOutputAddress = "127.0.0.1";
    mOutputPort = "5555";

    // Set the field values (TODO: Find ways to make these default in proto)
    mImageDataMessage.set_width(800);
    mImageDataMessage.set_height(600);
    mImageDataMessage.set_data("Hello World!");

    try{
        mZmqContext = zmq::context_t(1);
        mOutputSocket = zmq::socket_t(mZmqContext, zmq::socket_type::push);
        mOutputSocket.bind("tcp://" + mOutputAddress + ":" + mOutputPort);
    } catch(const zmq::error_t& exeption){  
        std::cerr << "ERROR::ConsumerMain::Initialize: Could not initialize zmq context/socket/connection!" << std::endl;
        return_success = false;
    }// catch

    return return_success;
}// Initialize

bool ConsumerMain::Run(){
    bool return_success = true;

    // Iterate through module list
    for(const std::string& moduleName : mModuleList){
        if(moduleName == ImageConsumerModule::MODULE_NAME){
            if(mImageConsumerModule.Run(mImageDataMessage) == false){
                std::cerr << "ERROR::ConsumerMain::Run: Could not run image consumer module run function!" << std::endl;
                return_success = false;
            }// if
        }// if
        else{
            std::cerr << "ERROR::ConsumerMain::Run: Module name not found for any modules! Maybe we need to add it?" << std::endl;
            return_success = false;
        }// else
    }// for 

    // Send zmq message to processor 
    if(SendMessage() == false){
        std::cerr << "ERROR::ConsumerMain::Run: Could not send output zmq message!" << std::endl;
        return_success = false;
    }// 

    return return_success;
}// Run

bool ConsumerMain::SendMessage(){
    bool return_success = true;

    // After running modules, package data message into zmq message
    std::string serialized_data;
    mImageDataMessage.SerializeToString(&serialized_data);
    zmq::message_t output_zmq_message(serialized_data.size());
    memcpy(output_zmq_message.data(), serialized_data.data(), serialized_data.size());

    try {
        if (mOutputSocket.send(output_zmq_message, zmq::send_flags::none) == false) {
            std::cerr << "ERROR::ConsumerMain::SendMessage: Could not send output zmq message!" << std::endl;
            return_success = false;
        }// if
        else{
            std::cout << "Message sent successfully!" << std::endl;
        }// else
    } catch (const zmq::error_t& e) {
        std::cerr << "ERROR::ConsumerMain::SendMessage: Error occurred while sending ZMQ message: " << e.what() << std::endl;
        return_success = false;
    }// catch

    return return_success;
}// SendMessage

int main(int argc, char *argv[]) {
    
    std::cout << "Reached Consumer main!" << std::endl;
    ConsumerMain consumerMain;

    ConsumerMain consumer_main;
    if(consumer_main.Initialize() == false){
        std::cerr << "ERROR::ConsumerMain::main: Could not initialize producer main!" << std::endl;
        return 1;
    }// if
    else{
        if(consumer_main.Run() == false){
            std::cerr << "ERROR::ConsumerMain::main: Could not run producer main!" << std::endl;
            return 1;
        }// if
    }// else

    return 0;
}