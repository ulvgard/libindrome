add_executable(test_util test_util.cpp)
set_property(TARGET test_util PROPERTY CXX_STANDARD 14)
target_link_libraries(test_util indrome gtest_main)
add_test(test_util test_util)

add_executable(test_io test_io.cpp)
set_property(TARGET test_io PROPERTY CXX_STANDARD 14)
target_link_libraries(test_io indrome gtest_main)
add_test(test_io test_io)



