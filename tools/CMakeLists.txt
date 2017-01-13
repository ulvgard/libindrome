add_subdirectory(baw EXCLUDE_FROM_ALL)
add_subdirectory(catimg EXCLUDE_FROM_ALL)
add_subdirectory(catvid EXCLUDE_FROM_ALL)
add_subdirectory(chesscalib EXCLUDE_FROM_ALL)
add_subdirectory(invk EXCLUDE_FROM_ALL)
add_subdirectory(lsvideo EXCLUDE_FROM_ALL)
if(${INDROME_ENABLE_RPC})
    add_subdirectory(poseserver EXCLUDE_FROM_ALL)
endif()
add_subdirectory(resizevid EXCLUDE_FROM_ALL)
add_subdirectory(showimg EXCLUDE_FROM_ALL)
add_subdirectory(showvid EXCLUDE_FROM_ALL)

# Optionally add RPC-tools
set(RPC_TOOLS)
if(${INDROME_ENABLE_RPC})
    set(RPC_TOOLS ${RPC_ROOLS} poseserver)
endif()

add_custom_target(tools ALL DEPENDS 
    baw
    catimg
    catvid
    chesscalib
	invk
    lsvideo
    resizevid
    ${RPC_TOOLS}
    showimg
    showvid)
