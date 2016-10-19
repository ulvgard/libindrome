add_subdirectory(baw)
add_subdirectory(catimg)
add_subdirectory(catvid)
add_subdirectory(chesscalib)
add_subdirectory(invk)
add_subdirectory(lsvideo)
add_subdirectory(resizevid)
add_subdirectory(showimg)
add_subdirectory(showvid)

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
