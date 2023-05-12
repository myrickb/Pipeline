#ifndef PRODUCERMAIN_HPP
#define PRODUCERMAIN_HPP

#include<iostream>
#include<zmq.hpp>
#include <csignal>
#include "DataMessage.pb.h"
#include "ImageProducerModule.hpp"

class ProducerMain{
    public:
        //static void SignalHandler(const int& signal);
        bool Initialize();
        bool Run();
        bool ReceiveMessage(std::string& receivedMessage);
    private:
        std::vector<std::string> mModuleList;
        std::string mInputAddress;
        std::string mInputPort;
        DataMessage::ImageDataMessage mImageDataMessage;
        zmq::context_t mZmqContext;
        zmq::socket_t mInputSocket;

        ImageProducerModule mImageProducerModule;
};

#endif // PRODUCERMAIN_HPP