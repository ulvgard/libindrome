set(CHESSCALIB_SRC chesscalib.cpp)

add_executable(chesscalib ${CHESSCALIB_SRC})
target_link_libraries(chesscalib indrome opencv_core opencv_calib3d)

