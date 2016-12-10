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
