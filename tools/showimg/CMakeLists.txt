set(SHOW_IMG showimg.cpp)

add_executable(showimg ${SHOW_IMG})
target_link_libraries(showimg
    indrome
    opencv_core
    opencv_highgui
)
