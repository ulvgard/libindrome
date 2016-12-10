set(INDROME_SRC
    src/util.cpp
    src/video.cpp
	src/algo.cpp
)

add_library(indrome 
    ${INDROME_SRC}
)
target_include_directories(indrome PUBLIC inc)
set_property(TARGET indrome PROPERTY CXX_STANDARD 14)
target_link_libraries(indrome PRIVATE
    opencv_core
    opencv_imgcodecs
    opencv_calib3d)

add_library(indrome_io src/io.cpp)
target_include_directories(indrome_io PUBLIC inc)
set_property(TARGET indrome_io PROPERTY CXX_STANDARD 14)
