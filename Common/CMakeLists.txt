set(SOURCES TomlUtil.cpp)
add_library(Common STATIC ${SOURCES})
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})