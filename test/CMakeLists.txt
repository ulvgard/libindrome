add_executable(test_util test_util.cpp)
target_link_libraries(test_util indrome gtest_main)
add_test(test_util test_util)
set_property(TARGET test_util PROPERTY CXX_STANDARD 14)

