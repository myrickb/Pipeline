#ifndef PRODUCERMAIN_HPP
#define PRODUCERMAIN_HPP

#include "DataMessage.pb.h"
class ProducerMain{
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

#endif // PRODUCERMAIN_HPP