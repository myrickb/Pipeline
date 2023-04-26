cmake_minimum_required(VERSION 3.5)

project(MainProcess VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(3rdParty)
add_subdirectory(Common)
add_subdirectory(Master)
add_subdirectory(Consumer)
add_subdirectory(Processor)
add_subdirectory(Producer)

add_executable(MainProcess main.cpp)
target_include_directories(MainProcess PRIVATE ${CMAKE_SOURCE_DIR}/Master)
target_link_libraries(MainProcess Master Common)

