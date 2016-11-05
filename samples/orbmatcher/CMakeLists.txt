set(ORB_MATCHER_SRC orbmatcher.cpp)

add_executable(orbmatcher ${ORB_MATCHER_SRC})
target_link_libraries(orbmatcher indrome opencv_core opencv_features2d)

