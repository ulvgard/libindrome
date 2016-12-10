cmake_minimum_required(VERSION 3.4) # The only tested version 
project(indrome)

find_package( OpenCV REQUIRED )

add_subdirectory(external)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(COMPILING_WITH_CLANG TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(COMPILING_WITH_GCC TRUE)
endif()

if(COMPILING_WITH_GCC OR COMPILING_WITH_CLANG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(indrome)

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
