#include "ProcessorMain.hpp"
#include <iostream>

// Signal interrupt needs to be global
bool gSignalInterrupt = false;

void SignalHandler(int signal){
    std::cout << "------------------------- SIGNAL CAUGHT --------------------------" << std::endl;
    std::cout << "------------------  Shutting down Processor Main... ---------------" << std::endl;
    gSignalInterrupt = true;
}// SignalHandler

bool ProcessorMain::Initialize() {
    bool return_success = true;

    // TODO: Read in output addr and port through toml config 

    // Default output address and port...
    mInputAddress = "127.0.0.1";
    mInputPort = "5555";
    mOutputAddress = "127.0.0.1";
    mOutputPort = "5556";

    try{
        mZmqContextInput = zmq::context_t(1);
        mInputSocket = zmq::socket_t(mZmqContextInput, zmq::socket_type::pull);
        mInputSocket.connect("tcp://" + mInputAddress + ":" + mInputPort);
    } catch(const zmq::error_t& exeption){  
        std::cerr << "ERROR::ProducerMain::Initialize: Could not initialize zmq context/socket/connection!" << std::endl;
        return_success = false;
    }// catch

    try{
        mZmqContextOutput = zmq::context_t(1);
        mOutputSocket = zmq::socket_t(mZmqContextOutput, zmq::socket_type::push);
        mOutputSocket.bind("tcp://" + mOutputAddress + ":" + mOutputPort);
    } catch(const zmq::error_t& exeption){  
        std::cerr << "ERROR::ConsumerMain::Initialize: Could not initialize zmq context/socket/connection!" << std::endl;
        return_success = false;
    }// catch

    return return_success;
}// Initialize

bool ProcessorMain::Run(){
    bool return_success = true;

    std::signal(SIGINT, SignalHandler);

    while(gSignalInterrupt == false){

        // Sit on receive socket, wait for zmq message
        std::string received_message;
        if(ReceiveMessage(received_message) == false){
            std::cerr << "ERROR::ProcessorMain::Run: Could not receive input zmq message!" << std::endl;
            return_success = false;
            break;
        }// if
        else{
            // Unpackage zmq message into a protobuf
            if(mImageDataMessage.ParseFromString(received_message) == false){
                std::cerr << "ERROR::ProcessorMain::Run: Could not parse protobuf message from incoming zmq message!" << std::endl;
                return_success = false;
            }// if
            else{
                // Iterate through module list
                for(const std::string& moduleName : mModuleList){
                    if(moduleName == ExampleProcessorModule::MODULE_NAME){
                        if(mExampleProcessorModule.Initialize() == false){
                            std::cerr << "ERROR::ProcessorMain::Run: Could not initialize image consumer module run function!" << std::endl;
                            return_success = false;
                        }// if
                        else
                        {
                            if(mExampleProcessorModule.Run(mImageDataMessage) == false){
                                std::cerr << "ERROR::ProcessorMain::Run: Could not run image consumer module run function!" << std::endl;
                                return_success = false;
                            }// if
                        }// else   
                    }// if
                    else{
                        std::cerr << "ERROR::ProcessorMain::Run: Module name not found for any modules! Maybe we need to add it?" << std::endl;
                        return_success = false;
                    }// else
                }// for 

                // Send zmq message to output ip/port
                if(SendMessage() == false){
                    std::cerr << "ERROR::ConsumerMain::Run: Could not send output zmq message!" << std::endl;
                    return_success = false;
                }// 
            }// else  
        }// else
    }// while  

    

    return return_success;
}// Run

bool ProcessorMain::ReceiveMessage(std::string& receivedMessage){
    bool return_success = true;

    try {
        zmq::message_t input_message;
        if (mInputSocket.recv(input_message, zmq::recv_flags::none) == false) {
            std::cerr << "ERROR::ProcessorMain::ReceiveMessage: Could not receive message from socket." << std::endl;
            return_success = false;
        } else {
            std::string receivedString(static_cast<char*>(input_message.data()), input_message.size());
            receivedMessage = receivedString;
            //receivedMessage(static_cast<char*>(input_message.data()), input_message.size());
            std::cout << "Received message: " << receivedMessage << std::endl;
        }
    } catch (const zmq::error_t& ex) {
        std::cerr << "ERROR::ProcessorMain::ReceiveMessage: Could not receive message from socket." << std::endl;
        return_success = false;
    }


    std::cout << "After receive message" << std::endl;
    return return_success;
}// ReceiveMessage

bool ProcessorMain::SendMessage(){
    bool return_success = true;

    // After running modules, package data message into zmq message
    std::string serialized_data;
    mImageDataMessage.SerializeToString(&serialized_data);
    zmq::message_t output_zmq_message(serialized_data.size());
    memcpy(output_zmq_message.data(), serialized_data.data(), serialized_data.size());

    try {
        if (mOutputSocket.send(output_zmq_message, zmq::send_flags::none) == false) {
            std::cerr << "ERROR::ProcessorMain::SendMessage: Could not send output zmq message!" << std::endl;
            return_success = false;
        }// if
        else{
            std::cout << "Message sent successfully!" << std::endl;
        }// else
    } catch (const zmq::error_t& e) {
        std::cerr << "ERROR::ProcessorMain::SendMessage: Error occurred while sending ZMQ message: " << e.what() << std::endl;
        return_success = false;
    }// catch

    return return_success;
}// SendMessage

int main(int argc, char *argv[]) {
    
    std::cout << "Reached Processor main!" << std::endl;

    ProcessorMain processor_main;
    if(processor_main.Initialize() == false){
        std::cerr << "ERROR::ProcessorMain::main: Could not initialize producer main!" << std::endl;
        return 1;
    }// if
    else{
        if(processor_main.Run() == false){
            std::cerr << "ERROR::ProcessorMain::main: Could not run producer main!" << std::endl;
            return 1;
        }// if
    }// else

    return 0;
}