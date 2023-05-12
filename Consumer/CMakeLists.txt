set(SOURCES ConsumerMain.cpp ImageConsumerModule.cpp)

add_executable(Consumer ${SOURCES})
target_include_directories(Consumer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Consumer PUBLIC ProtoLib)
target_link_libraries(Consumer PUBLIC ${Protobuf_LIBRARIES})
target_link_libraries(Consumer PUBLIC ${ZMQ_LIBRARY})

