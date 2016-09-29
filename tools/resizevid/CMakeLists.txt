set(RESIZE_SRC resizevid.cpp)

add_executable(resizevid ${RESIZE_SRC})
target_link_libraries(resizevid indrome opencv_core opencv_imgproc)
