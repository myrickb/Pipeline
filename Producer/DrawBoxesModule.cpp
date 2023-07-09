#include "DrawBoxesModule.hpp"
#include <iostream>

bool DrawBoxesModule::Initialize() {
    bool return_success = true;

    return return_success;
}

bool DrawBoxesModule::Run(DataMessage::ImageDataMessage& imageDataMessage){
    bool return_success = true;

    // Construct cv mat from protobuf
    cv::Mat image;
    std::vector<uint8_t> imageDataVector(imageDataMessage.data().begin(), imageDataMessage.data().end());
    image = cv::imdecode(imageDataVector, cv::IMREAD_COLOR);

    // Draw all bounding boxes from protobuf
    for (const auto& boundingBox : imageDataMessage.boundingboxes()) {
        int x = boundingBox.x();
        int y = boundingBox.y();
        int width = boundingBox.width();
        int height = boundingBox.height();

        cv::Rect rect(x, y, width, height);
        cv::rectangle(image, rect, cv::Scalar(0, 255, 0), 2);
    }

    return return_success;
}
