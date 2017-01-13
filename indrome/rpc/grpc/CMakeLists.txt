find_package(GRPC REQUIRED)
find_package(Protobuf REQUIRED)

set(SERVER_PROTO_SRC)
set(SERVER_PROTO_HDR)

file(GLOB PROTOFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
foreach(PROTO ${PROTOFILES})

    PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTOFILES})
    PROTOBUF_GENERATE_GRPC_CPP(GRPC_SRCS GRPC_HDRS ${PROTOFILES})

    list(APPEND SERVER_PROTOS ${PROTO_SRCS} ${PROTO_HDRS})
    list(APPEND SERVER_GRPCS ${GRPC_SRCS} ${GRPC_HDRS})

endforeach()
set_source_files_properties(${SERVER_PROTOS} PROPERTIES GENERATED TRUE)
set_source_files_properties(${SERVER_GRPCS} PROPERTIES GENERATED TRUE)

add_library(indrome_grpc ${SERVER_PROTOS} ${SERVER_GRPCS})
target_link_libraries(indrome_grpc PRIVATE grpc++ protobuf)
target_include_directories(indrome_grpc PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
