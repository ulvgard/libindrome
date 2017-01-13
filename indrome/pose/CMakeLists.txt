###
# Pose is a module for camera pose tracking
###
set(POSE_SRC
    src/simple_velocity.cpp
)

add_library(indrome_pose
    ${POSE_SRC}
)
target_include_directories(indrome_pose PUBLIC inc)
set_property(TARGET indrome_pose PROPERTY CXX_STANDARD 14)
target_link_libraries(indrome_pose PRIVATE
    opencv_core
    opencv_imgcodecs
    opencv_calib3d)
