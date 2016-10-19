set(INVK_SRC invk.cpp)

add_executable(invk ${INVK_SRC})
target_link_libraries(invk indrome opencv_core opencv_calib3d)

