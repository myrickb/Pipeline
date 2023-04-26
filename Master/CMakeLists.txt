set(SOURCES Master.cpp)
add_library(Master STATIC ${SOURCES})
target_link_libraries(Master PRIVATE Common)
