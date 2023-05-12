#ifndef ExampleProcessorModule_HPP
#define ExampleProcessorModule_HPP

#include<iostream>
#include<vector>
#include<zmq.hpp>
#include "DataMessage.pb.h"
class ExampleProcessorModule{
    public:
        ExampleProcessorModule();
        bool Initialize();
        bool Run(DataMessage::ImageDataMessage& imageDataMessage);

        static constexpr const char* MODULE_NAME ="ImageConsumer";
        
};

#endif // ExampleProcessorModule_HPP