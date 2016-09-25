project(libindrome)

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

add_library(libindrome STATIC
    ${INDROME_SRC}
    ${INDROME_API_HEADERS}
    ${INDROME_INTERNAL_HEADERS}
)

set_property(TARGET libindrome PROPERTY CXX_STANDARD 14)
set_property(TARGET libindrome PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(libindrome PUBLIC inc
                                      PRIVATE internal_inc)

target_link_libraries(libindrome
    opencv_core
    opencv_imgcodecs)

add_subdirectory(tools)
