#include "ProducerMain.hpp"
#include <iostream>

// Signal interrupt needs to be global
bool gSignalInterrupt = false;

void SignalHandler(int signal){
    std::cout << "------------------------- SIGNAL CAUGHT --------------------------" << std::endl;
    std::cout << "------------------  Shutting down Producer Main... ---------------" << std::endl;
    gSignalInterrupt = true;
}// SignalHandler

bool ProducerMain::Initialize() {
    bool return_success = true;

    // TODO: Read in Input addr and port through toml config 

    // Default output address and port...
    mInputAddress = "127.0.0.1";
    mInputPort = "5555";

    mModuleList.push_back("ImageProducer");
    
    try{
        mZmqContext = zmq::context_t(1);
        mInputSocket = zmq::socket_t(mZmqContext, zmq::socket_type::pull);
        mInputSocket.connect("tcp://" + mInputAddress + ":" + mInputPort);
    } catch(const zmq::error_t& exeption){  
        std::cerr << "ERROR::ProducerMain::Initialize: Could not initialize zmq context/socket/connection!" << std::endl;
        return_success = false;
    }// catch

    return return_success;
}

bool ProducerMain::Run(){
    bool return_success = true;

    std::signal(SIGINT, SignalHandler);

    while(gSignalInterrupt == false){

        // Sit on receive socket, wait for zmq message
        std::string received_message;
        if(ReceiveMessage(received_message) == false){
            std::cerr << "ERROR::ProducerMain::Run: Could not receive input zmq message!" << std::endl;
            return_success = false;
            break;
        }// if
        else{
            // Unpackage zmq message into a protobuf
            if(mImageDataMessage.ParseFromString(received_message) == false){
                std::cerr << "ERROR::ProducerMain::Run: Could not parse protobuf message from incoming zmq message!" << std::endl;
                return_success = false;
            }// if
            else{
                // Iterate through module list
                for(const std::string& moduleName : mModuleList){
                    if(moduleName == ImageProducerModule::MODULE_NAME){
                        if(mImageProducerModule.Initialize() == false){
                            std::cerr << "ERROR::ProducerMain::Run: Could not initialize image consumer module run function!" << std::endl;
                            return_success = false;
                        }// if
                        else
                        {
                            if(mImageProducerModule.Run(mImageDataMessage) == false){
                                std::cerr << "ERROR::ProducerMain::Run: Could not run image consumer module run function!" << std::endl;
                                return_success = false;
                            }// if
                        }// else    
                    }// if
                    else{
                        std::cerr << "ERROR::ProducerMain::Run: Module name not found for any modules! Maybe we need to add it?" << std::endl;
                        return_success = false;
                    }// else
                }// for 
            }// else  
        }// else
    }// while    

    // Clean up the socket and context
    mInputSocket.close();
    mZmqContext.close();

    return return_success;
}

bool ProducerMain::ReceiveMessage(std::string& receivedMessage){
    bool return_success = true;

    try {
        zmq::message_t input_message;
        if (mInputSocket.recv(input_message, zmq::recv_flags::none) == false) {
            std::cerr << "ERROR::ProducerMain::ReceiveMessage: Could not receive message from socket." << std::endl;
            return_success = false;
        } else {
            std::string receivedString(static_cast<char*>(input_message.data()), input_message.size());
            receivedMessage = receivedString;
            //receivedMessage(static_cast<char*>(input_message.data()), input_message.size());
            std::cout << "Received message: " << receivedMessage << std::endl;
        }
    } catch (const zmq::error_t& ex) {
        std::cerr << "ERROR::ProducerMain::ReceiveMessage: Could not receive message from socket." << std::endl;
        return_success = false;
    }

    return return_success;
}// ReceiveMessage

int main(int argc, char *argv[]) {
    
    std::cout << "Reached Producer main!" << std::endl;

    ProducerMain producer_main;
    if(producer_main.Initialize() == false){
        std::cerr << "ERROR::ProducerMain::main: Could not initialize producer main!" << std::endl;
        return 1;
    }// if
    else{
        if(producer_main.Run() == false){
            std::cerr << "ERROR::ProducerMain::main: Could not run producer main!" << std::endl;
            return 1;
        }// if
    }// else

    return 0;
}