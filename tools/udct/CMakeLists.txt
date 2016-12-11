set(UDCT_SRC
    udct.cpp)

add_executable(udct ${UDCT_SRC})
set_property(TARGET udct PROPERTY CXX_STANDARD 14)
target_link_libraries(udct cxxopts indrome_io)
