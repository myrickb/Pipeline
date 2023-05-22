#ifndef IMAGECONSUMERMODULE_HPP
#define IMAGECONSUMERMODULE_HPP

#include<iostream>
#include<vector>
#include<zmq.hpp>
#include "DataMessage.pb.h"
#include <opencv2/opencv.hpp>
class ImageConsumerModule{
    public:
        ImageConsumerModule();
        bool Initialize();
        bool Run(DataMessage::ImageDataMessage& imageDataMessage);

        static constexpr const char* MODULE_NAME ="ImageConsumer";
    private:
        std::string mImagePath{""};
        
};

#endif // IMAGECONSUMERMODULE_HPP