#ifndef PROCESSORMAIN_HPP
#define PROCESSORMAIN_HPP

#include "DataMessage.pb.h"
class ProcessorMain{
    public:
        bool Initialize();
        bool Run();
    private:
        std::vector<std::string> mModuleList;
        std::string mInputAddress;
        std::string mInputPort;
        std::string mOutputAddress;
        std::string mOutputPort;
        DataMessage::ImageDataMessage mImageDataMessage;
};

#endif // PROCESSORMAIN_HPP