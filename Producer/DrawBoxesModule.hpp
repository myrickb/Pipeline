#ifndef DRAWBOXESMODULE_HPP
#define DRAWBOXESMODULE_HPP

#include "DataMessage.pb.h"
#include <opencv2/opencv.hpp>
class DrawBoxesModule{
    public:
        bool Initialize();
        bool Run(DataMessage::ImageDataMessage& imageDataMessage);
    
        static constexpr const char* MODULE_NAME ="DrawBoxes";
};

#endif // DRAWBOXESMODULE_HPP
