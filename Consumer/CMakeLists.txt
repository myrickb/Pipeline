set(SOURCES ConsumerMain.cpp)
add_library(Consumer STATIC ${SOURCES})
target_include_directories(Consumer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


