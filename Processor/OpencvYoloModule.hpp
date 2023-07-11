#ifndef OPENCVYOLOMODULE_HPP
#define OPENCVYOLOMODULE_HPP

#include<iostream>
#include<vector>
#include<zmq.hpp>
#include "DataMessage.pb.h"
#include <opencv2/opencv.hpp>
class OpencvYoloModule{
    public:
        OpencvYoloModule();
        bool Initialize();
        bool Run(DataMessage::ImageDataMessage& imageDataMessage);

        static constexpr const char* MODULE_NAME ="ExampleProcessor";
        
};

#endif // OPENCVYOLOMODULE_HPP
