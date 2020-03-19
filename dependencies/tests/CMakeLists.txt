cmake_minimum_required(VERSION 3.10)
project(tests)

set_property(GLOBAL PROPERTY PLATFORM_RESOURCES_DIRECTORY)
set_property(GLOBAL PROPERTY COMMON_RESOURCES_DIRECTORY)
set_property(GLOBAL PROPERTY RESOURCES)

add_subdirectory(resources)

get_property(PLATFORM_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_PLATFORM_RESOURCES_DIRECTORY)
get_property(COMMON_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_COMMON_RESOURCES_DIRECTORY)
get_property(RESOURCES GLOBAL PROPERTY GLOBAL_RESOURCES)

set(DEPENDENCIES 
#    application
#    game-loop
#    renderer
#    textures
#    input
#    scenes
    url
)

if(WINDOWS_STORE)
    set(GAME_PACKAGE_NAME  "se.coderox.gameenginesandboxtests")
    set(GAME_VERSION       "0.1.0.0")
    set(GAME_TITLE         "tests")
    set(GAME_DESCRIPTION   "tests")
    set(PHONE_PRODUCT_ID   "B9EC94EF-8576-33B8-81E6-0092C89DBED8")
    set(PHONE_PUBLISHER_ID "00000000-0000-0000-0000-000000000000")

#    set(APPLICATION_EXTENSIONS '<Extensions><uap5:Extension Category="windows.appExecutionAlias" Executable="tests.exe" EntryPoint="tests.App><uap5:AppExecutionAlias desktop4:Subsystem="console"><uap5:ExecutionAlias Alias="GameEngineSandboxTests.exe /></uap5:AppExecutionAlias></uap5:Extension></Extensions>')

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/../pipeline/uwp/package.console.appxManifest.in"
        "${PROJECT_BINARY_DIR}/package.appxManifest"
        @ONLY
    )
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/../pipeline/uwp/TemporaryKey.pfx"
        "${PROJECT_BINARY_DIR}/TemporaryKey.pfx"
        COPYONLY
    )

    list(APPEND RESOURCES
        "${PROJECT_BINARY_DIR}/package.appxManifest"
        "${PROJECT_BINARY_DIR}/TemporaryKey.pfx"
    )
endif()

if(LINUX)
    message(STATUS "Temporary solution for Linux: Finding GLUT")
    find_package(GLUT REQUIRED)
    list(APPEND DEPENDENCIES 
        GLUT::GLUT
    )
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group("resources" ${RESOURCES})

if(WINDOWS_STORE)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS /SUBSYSTEM:CONSOLE
    )
else()

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${COMMON_RESOURCES_DIRECTORY} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
    
    set(PLATFORM_RESOURCES)
    if(EXISTS "${PLATFORM_RESOURCES_DIRECTORY}" AND IS_DIRECTORY "${PLATFORM_RESOURCES_DIRECTORY}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${PLATFORM_RESOURCES_DIRECTORY} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
    endif()
endif()
