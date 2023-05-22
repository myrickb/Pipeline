#ifndef CONSUMERMAIN_HPP
#define CONSUMERMAIN_HPP

#include<iostream>
#include<vector>
#include<zmq.hpp>
#include<csignal>
#include <filesystem>
#include "DataMessage.pb.h"
#include "ImageConsumerModule.hpp"

class ConsumerMain{
    public:
        ConsumerMain();
        bool Initialize();
        bool Run();
        bool SendMessage();
    private:
        std::vector<std::string> mModuleList;
        std::string mOutputAddress;
        std::string mOutputPort;
        DataMessage::ImageDataMessage mImageDataMessage;

        zmq::context_t mZmqContext;
        zmq::socket_t mOutputSocket;

        ImageConsumerModule mImageConsumerModule;

};

#endif // CONSUMERMAIN_HPP
