set(SOURCES ProducerMain.cpp)
add_executable(Producer ${SOURCES})
target_include_directories(Producer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})