set(CATIMG_SRC catimg.cpp)

add_executable(catimg ${CATIMG_SRC})
target_link_libraries(catimg indrome opencv_core)
