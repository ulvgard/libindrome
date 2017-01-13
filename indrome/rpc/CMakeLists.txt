add_subdirectory(grpc indrome/grpc)

set(REMOTE_SRC
    src/service.cpp
    src/client.cpp)
add_library(indrome_rpc ${REMOTE_SRC})
set_property(TARGET indrome_rpc PROPERTY CXX_STANDARD 14)
target_link_libraries(indrome_rpc PUBLIC indrome_grpc)
target_include_directories(indrome_rpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
