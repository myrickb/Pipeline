#ifndef CONSUMERMAIN_HPP
#define CONSUMERMAIN_HPP

#include<iostream>
#include<vector>
#include<zmq.h>
#include "DataMessage.pb.h"
class ConsumerMain{
    public:
        ConsumerMain();
        bool Initialize();
        bool Run();
    private:
        std::vector<std::string> mModuleList;
        std::string mOutputAddress;
        std::string mOutputPort;
        DataMessage::ImageDataMessage mImageDataMessage;

};

#endif // CONSUMERMAIN_HPP
