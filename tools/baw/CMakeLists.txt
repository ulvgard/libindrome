set(BAW_SRC baw.cpp)

add_executable(baw ${BAW_SRC})
target_link_libraries(baw indrome opencv_core opencv_imgproc)
