set(CATVID_SRC catvid.cpp)

add_executable(catvid ${CATVID_SRC})
target_link_libraries(catvid indrome opencv_core opencv_videoio)
