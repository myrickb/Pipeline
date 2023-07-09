set(SOURCES ProducerMain.cpp ImageProducerModule.cpp DrawBoxesModule.cpp)
add_executable(Producer ${SOURCES})
target_include_directories(Producer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Producer PUBLIC ProtoLib)
target_link_libraries(Producer PUBLIC ${Protobuf_LIBRARIES})
target_link_libraries(Producer PUBLIC ${ZMQ_LIBRARY})
target_link_libraries(Producer PUBLIC ${OpenCV_LIBS})
