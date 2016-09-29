set(SHOW_IMG showimg.cpp)

add_executable(showimg ${SHOW_IMG})
target_link_libraries(showimg
    libindrome
    opencv_core
    opencv_highgui
)
