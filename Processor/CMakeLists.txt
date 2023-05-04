set(SOURCES ProcessorMain.cpp)
add_executable(Processor ${SOURCES})
target_include_directories(Processor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

