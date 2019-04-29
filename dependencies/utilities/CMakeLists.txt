project(utilities)

if(WINDOWS_STORE)
    find_package(unofficial-angle CONFIG REQUIRED)
    list(APPEND DEPENDENCIES 
        unofficial::angle::libEGL
        unofficial::angle::libGLESv2
    )
else()
    find_package(GLEW REQUIRED)
    find_package(PNG REQUIRED)
    list(APPEND DEPENDENCIES 
        GLEW::GLEW
        PNG::PNG
    )
    if(WIN32)
        list(APPEND DEPENDENCIES
            opengl32.lib
        )
    endif()
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")