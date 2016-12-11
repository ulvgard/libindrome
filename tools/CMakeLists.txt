add_subdirectory(baw EXCLUDE_FROM_ALL)
add_subdirectory(catimg EXCLUDE_FROM_ALL)
add_subdirectory(catvid EXCLUDE_FROM_ALL)
add_subdirectory(chesscalib EXCLUDE_FROM_ALL)
add_subdirectory(invk EXCLUDE_FROM_ALL)
add_subdirectory(lsvideo EXCLUDE_FROM_ALL)
add_subdirectory(resizevid EXCLUDE_FROM_ALL)
add_subdirectory(showimg EXCLUDE_FROM_ALL)
add_subdirectory(showvid EXCLUDE_FROM_ALL)


add_custom_target(tools ALL DEPENDS 
    baw
    catimg
    catvid
    chesscalib
	invk
    lsvideo
    resizevid
    showimg
    showvid)

add_subdirectory(udct EXCLUDE_FROM_ALL)
