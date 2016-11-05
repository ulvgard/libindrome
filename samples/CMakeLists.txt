add_subdirectory(orbmatcher)

add_custom_target(samples ALL DEPENDS 
    orbmatcher 
    )
