#ifndef PROCESSORMAIN_HPP
#define PROCESSORMAIN_HPP

#include "DataMessage.pb.h"
#include<vector>
#include<zmq.hpp>
#include<csignal>
#include "DataMessage.pb.h"
#include "ExampleProcessorModule.hpp"
class ProcessorMain{
    public:
        bool Initialize();
        bool Run();
        bool SendMessage();
        bool ReceiveMessage(std::string& receivedMessage);
    private:
        std::vector<std::string> mModuleList;
        std::string mInputAddress;
        std::string mInputPort;
        std::string mOutputAddress;
        std::string mOutputPort;
        DataMessage::ImageDataMessage mImageDataMessage;

        zmq::context_t mZmqContextInput;
        zmq::socket_t mInputSocket;
        zmq::context_t mZmqContextOutput;
        zmq::socket_t mOutputSocket;

        ExampleProcessorModule mExampleProcessorModule;


};

#endif // PROCESSORMAIN_HPP