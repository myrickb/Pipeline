#include "ImageConsumerModule.hpp"
#include <iostream>

ImageConsumerModule::ImageConsumerModule()
{

}// ImageConsumerModule

bool ImageConsumerModule::Initialize() {
    bool return_success = true;

    // TODO: Read in from toml file 
    mImagePath = "../../TestData/ImageData/yoloData.jpg";

    return return_success;
}// Initialize

bool ImageConsumerModule::Run(DataMessage::ImageDataMessage& imageDataMessage){
    bool return_success = true;
    
    try{
        cv::Mat image_mat;
        image_mat = cv::imread(mImagePath);

        if(image_mat.empty() == true)
        {
            std::cerr << "ERROR::ImageConsumerModule::Run: Image is empty!" << std::endl;
            return_success = false;
        }// if
        else
        {
            // CV mat was not empty, populate protobuf message with image data
            imageDataMessage.mutable_data()->assign(image_mat.data, image_mat.data + image_mat.total() * image_mat.elemSize());
            imageDataMessage.set_width(image_mat.cols);
            imageDataMessage.set_height(image_mat.rows);
        }// else

    }// try
    catch (const cv::Exception& e)
    {
        std::cerr << "ERROR::ImageConsumerModule::Run: Opencv error occurred: " << e.what() << std::endl;
        return_success = false;
    }// catch

    return return_success;
}// Run

