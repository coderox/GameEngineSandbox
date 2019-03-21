project(engine)

set(DEPENDENCIES
    utilities
)

#if(UWP)
    message(STATUS "Is UWP")
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
#else()
#    message(STATUS "Is not UWP")
#    list(APPEND DEPENDENCIES 
#        GLEW::GLEW
#        opengl32.lib
#    )
#    find_package(GLEW REQUIRED)
#endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
