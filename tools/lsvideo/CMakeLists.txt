set(LSVIDEO_SRC lsvideo.cpp)

add_executable(lsvideo ${LSVIDEO_SRC})
target_link_libraries(lsvideo indrome opencv_videoio)
