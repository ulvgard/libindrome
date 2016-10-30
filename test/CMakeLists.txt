add_executable(test_util test_util.cpp)
target_link_libraries(test_util indrome gtest_main)
add_test(test_util test_util)
set_property(TARGET test_util PROPERTY CXX_STANDARD 14)

add_executable(test_algo test_algo.cpp)
target_link_libraries(test_algo indrome gtest_main opencv_calib3d)
add_test(test_util test_algo)
set_property(TARGET test_algo PROPERTY CXX_STANDARD 14)
