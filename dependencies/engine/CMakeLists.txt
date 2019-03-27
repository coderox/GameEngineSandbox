project(engine)

set(DEPENDENCIES
    utilities
)

if(MSVC)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
