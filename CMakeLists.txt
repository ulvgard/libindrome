cmake_minimum_required(VERSION 3.4) # The only tested version 
project(indrome)

find_package( OpenCV REQUIRED )

add_subdirectory(external)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(INDROME_SRC
    src/util.cpp
    src/video.cpp
	src/algo.cpp
)

set(INDROME_INTERNAL_HEADERS
)

set(INDROME_API_HEADERS
    inc/indrome/util.h
    inc/indrome/video.h
	inc/indrome/algo.h
)

add_library(indrome 
    ${INDROME_SRC}
    ${INDROME_API_HEADERS}
    ${INDROME_INTERNAL_HEADERS}
)

set_property(TARGET indrome PROPERTY CXX_STANDARD 14)

target_include_directories(indrome PUBLIC inc
                                   PRIVATE internal_inc)

target_link_libraries(indrome PRIVATE
    opencv_core
    opencv_imgcodecs
    opencv_calib3d)

option(INDROME_ENABLE_TOOLS "Enable commandline tools" OFF)

if(INDROME_ENABLE_TOOLS)
    add_subdirectory(tools)
endif()

option(ENABLE_DEMO "Enable indrome demos" OFF)

if(ENABLE_DEMO)
    add_subdirectory(demo)
endif()

option(ENABLE_TEST "Enable indrome tests" OFF)

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
