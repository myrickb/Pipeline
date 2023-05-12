#ifndef IMAGEPRODUCERMODULE_HPP
#define IMAGEPRODUCERMODULE_HPP

#include "DataMessage.pb.h"
class ImageProducerModule{
    public:
        bool Initialize();
        bool Run(DataMessage::ImageDataMessage& imageDataMessage);
    
        static constexpr const char* MODULE_NAME ="ImageProducer";
};

#endif // IMAGEPRODUCERMODULE_HPP