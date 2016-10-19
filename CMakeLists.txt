cmake_minimum_required(VERSION 3.6) # The only tested version 
project(indrome)

find_package( OpenCV REQUIRED )

add_subdirectory(external)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(INDROME_SRC
    src/util.cpp
    src/video.cpp
)

set(INDROME_INTERNAL_HEADERS
)

set(INDROME_API_HEADERS
    inc/indrome/util.h
    inc/indrome/video.h
)

add_library(indrome STATIC
    ${INDROME_SRC}
    ${INDROME_API_HEADERS}
    ${INDROME_INTERNAL_HEADERS}
)

set_property(TARGET indrome PROPERTY CXX_STANDARD 14)
set_property(TARGET indrome PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(indrome PUBLIC inc
                                   PRIVATE internal_inc)

target_link_libraries(indrome
    opencv_core
    opencv_imgcodecs)

add_subdirectory(tools)

option(ENABLE_TEST "Enable indrome tests" OFF)

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
