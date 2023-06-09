#include "ImageProducerModule.hpp"
#include <iostream>

bool ImageProducerModule::Initialize() {
    bool return_success = true;

    return return_success;
}

bool ImageProducerModule::Run(DataMessage::ImageDataMessage& imageDataMessage){
    bool return_success = true;

    if(imageDataMessage.data().empty() == true)
    {
        std::cerr << "ERROR::ImageProducerModule::Run: Incoming image data message is missing data!" << std::endl;
        return_success = false;
    }// if
    else
    {
        cv::Mat output_image;
        output_image.create(imageDataMessage.height(), imageDataMessage.width(), CV_8UC3);

        if(output_image.data == nullptr)
        {
            std::cerr << "ERROR::ImageProducerModule::Run: Failed to create output image!" << std::endl;
            return_success = false;
        }// if
        else
        {
            if(output_image.total() * output_image.elemSize() != imageDataMessage.data().size())
            {
                std::cerr << "ERROR::ImageProducerModule::Run: Invalid data size!" << std::endl;
                return_success = false;
            }// if
            else
            {
                std::memcpy(output_image.data, imageDataMessage.data().data(), imageDataMessage.data().size());

                // Once we have our output image, draw any existing bounding boxes
                std::vector<cv::Rect> bounding_boxes;
                for(const auto& boundingBox : imageDataMessage.boundingboxes())
                {
                    bounding_boxes.push_back(cv::Rect(boundingBox.x(), boundingBox.y(),
                                                      boundingBox.width(), boundingBox.height()));
                }// for 

                for(const auto& box : bounding_boxes)
                {
                    cv::rectangle(output_image, box, cv::Scalar(0,255,0), 2); // Green box color
                }

                std::cout << "About to save off image..." << std::endl;
                if(cv::imwrite("outputImage.jpg", output_image) == false)
                {
                    std::cerr << "ERROR::ImageProducerModule::Run: Could not save off output image!" << std::endl;
                    return_success = false;
                }// if
            }// else
        } // else
    }// else 

    return return_success;
}
