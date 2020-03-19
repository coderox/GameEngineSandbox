if(WINDOWS_STORE)
    add_subdirectory(angle ${CMAKE_CURRENT_BINARY_DIR}/angle)

    set(ANGLE_FOLDER "Thirdparty/Angle")

    set(ANGLE_TARGETS
        libEGL
        libANGLE
        libGLESv2
        angle_common
        angle_image_util
        angle_preprocessor
        angle_translator
    )

    foreach(ANGLE_TARGET ${ANGLE_TARGETS})
        set_target_properties (${ANGLE_TARGET} PROPERTIES FOLDER ${ANGLE_FOLDER})
    endforeach()

    if(TESTS)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        add_subdirectory(googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
    endif()
endif()
