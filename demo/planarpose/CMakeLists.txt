set(PLANARPOSE_SRC planarpose.cpp)

add_executable(planarpose ${PLANARPOSE_SRC})
target_link_libraries(planarpose indrome opencv_core opencv_calib3d)

set_property(TARGET planarpose PROPERTY CXX_STANDARD 14)
