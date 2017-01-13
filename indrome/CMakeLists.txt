###
# Target: indrome_core 
# The indrome target must be built in this directory to successfully add 
# dependencies like indrome_rpc
###
set(CORE_SRC
    core/src/io.cpp
    core/src/util.cpp
    core/src/video.cpp
	core/src/algo.cpp
)
add_library(indrome 
    ${CORE_SRC}
)
target_include_directories(indrome PUBLIC core/inc)
set_property(TARGET indrome PROPERTY CXX_STANDARD 14)
target_link_libraries(indrome PRIVATE
    opencv_core
    opencv_imgcodecs
    opencv_calib3d)

###
# RPC module
# Target: indrome_rpc 
###
option(INDROME_ENABLE_RPC "Enable RPC client/server" OFF)
if(${INDROME_ENABLE_RPC})
    add_subdirectory(rpc)
    target_link_libraries(indrome PUBLIC indrome_rpc)
endif()

###
# Pose module
# Target: indrome_pose
###
add_subdirectory(pose)
