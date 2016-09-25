set(SHOW_VID showvid.cpp)

add_executable(showvid ${SHOW_VID})
target_link_libraries(showvid 
    libindrome
    opencv_core
    opencv_highgui
)
