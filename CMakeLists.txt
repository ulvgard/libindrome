project(libindrome)

add_subdirectory(external)

set(INDROME_SRC
    src/video.cpp
)

set(INDROME_INTERNAL_HEADERS
)

set(INDROME_API_HEADERS
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

add_subdirectory(tools)
