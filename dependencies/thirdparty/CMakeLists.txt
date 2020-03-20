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
endif()

if(TESTS)
    if(WINDOWS_STORE)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    add_subdirectory(googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

    set(GOOGLETEST_FOLDER "Thirdparty/GoogleTest")

    set(GOOGLETEST_TARGETS
        gtest
        gtest_main
        gmock
        gmock_main
    )

    foreach(GOOGLETEST_TARGET ${GOOGLETEST_TARGETS})
        set_target_properties (${GOOGLETEST_TARGET} PROPERTIES FOLDER ${GOOGLETEST_FOLDER})
    endforeach()
endif()
