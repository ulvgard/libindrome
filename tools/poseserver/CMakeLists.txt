set(POSE_SRC
    poseserver.cpp)

add_executable(poseserver ${POSE_SRC})
set_property(TARGET poseserver PROPERTY CXX_STANDARD 14)
target_link_libraries(poseserver 
    cxxopts 
    indrome 
    indrome_grpc 
    indrome_pose
    opencv_viz 
    pthread 
    grpc)
