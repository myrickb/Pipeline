#include "ExampleProcessorModule.hpp"
#include <iostream>

ExampleProcessorModule::ExampleProcessorModule()
{

}// ExampleProcessorModule

bool ExampleProcessorModule::Initialize() {
    bool return_success = true;

    return return_success;
}// Initialize

bool ExampleProcessorModule::Run(DataMessage::ImageDataMessage& imageDataMessage){
    bool return_success = true;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~THIS IS A TEST MODULE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // This module simply creates four bounding boxes that live in each corner of the image

    DataMessage::BoundingBox* box1 = imageDataMessage.add_boundingboxes();
    DataMessage::BoundingBox* box2 = imageDataMessage.add_boundingboxes();
    DataMessage::BoundingBox* box3 = imageDataMessage.add_boundingboxes();
    DataMessage::BoundingBox* box4 = imageDataMessage.add_boundingboxes();

    box1->set_x(50);
    box1->set_y(50);
    box1->set_width(100);
    box1->set_height(100);

    box2->set_x(500);
    box2->set_y(50);
    box2->set_width(100);
    box2->set_height(100);

    box3->set_x(500);
    box3->set_y(500);
    box3->set_width(100);
    box3->set_height(100);

    box4->set_x(50);
    box4->set_y(500);
    box4->set_width(100);
    box4->set_height(100);

    return return_success;
}// Run
