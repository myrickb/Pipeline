find_package(Protobuf REQUIRED)

set(PROTO_FILE DataMessage.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})
add_library(ProtoLib ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(ProtoLib INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
