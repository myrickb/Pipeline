set(SOURCES ProducerMain.cpp)
add_library(Producer ${SOURCES})
target_include_directories(Producer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})