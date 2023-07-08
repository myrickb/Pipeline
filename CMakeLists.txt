cmake_minimum_required(VERSION 3.5)

project(MainProcess VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenCV 4 REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

# Add the include directories
include_directories(${ZMQ_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

set(ZMQ_LIBRARY ${ZMQ_LIBRARIES})

add_subdirectory(3rdParty)
add_subdirectory(Proto)

add_subdirectory(Common)
add_subdirectory(Master)
add_subdirectory(Consumer)
add_subdirectory(Processor)
add_subdirectory(Producer)

add_executable(MainProcess main.cpp)
target_include_directories(MainProcess PUBLIC ${CMAKE_SOURCE_DIR}/Master)
target_link_libraries(MainProcess Master Common)

