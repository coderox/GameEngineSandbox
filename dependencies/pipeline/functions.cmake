macro(initialize_pipeline)
    if(MSVC)

        if(MSVC_VERSION GREATER 1700)
            set(COMPILER_VERSION "12")
        elseif(MSVC_VERSION GREATER 1600)
            set(COMPILER_VERSION "11")
        endif()

        if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
            set(PLATFORM UWP)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await /DUWP")
        else()
            set(PLATFORM WIN32)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32")
        endif()
    else()
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            set(PLATFORM LINUX)
            set(LINUX 1)
        else()
            set(PLATFORM OSX)
            set(OSX 1)
        endif()
    endif()

    # Enable folders grouping in IDE
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endmacro()

macro(update_sources)
    file(GLOB_RECURSE COMMON_SOURCES
        source/common/*.cpp
        source/common/*.h*
    )
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${COMMON_SOURCES})
    
    file(GLOB PLATFORM_SOURCES
        source/${PLATFORM}/*.cpp
        source/${PLATFORM}/*.h*
    )
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PLATFORM_SOURCES})

    if(TESTS)
        file(GLOB TEST_SOURCES
            tests/source/${PLATFORM}/*.cpp
            tests/source/${PLATFORM}/*.h*
        )
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TEST_SOURCES})
    endif()

    if(UWP OR WIN32)
        file(GLOB PLATFORM_COMMON_SOURCES
            source/msft/*.cpp
            source/msft/*.h*
        )
    else()
        file(GLOB PLATFORM_COMMON_SOURCES
            source/posix/*.cpp
            source/posix/*.h*
        )
    endif()
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PLATFORM_COMMON_SOURCES})

endmacro()

function(build_library project_name)
    set(DEPENDENCIES ${ARGV1})
    set(SHARED ${ARGV2})

    update_sources()

    file(GLOB_RECURSE EXTERNAL_HEADERS 
        include/common/*.h*
        include/${PLATFORM}/*.h*
    )
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${EXTERNAL_HEADERS})

    set(LIBRARY_INCLUDE_DIRECTORIES 
        include/common
        include/${PLATFORM}
    )

    if(TESTS)
        file(GLOB_RECURSE TEST_HEADERS 
            tests/include/common/*.h*
            tests/include/${PLATFORM}/*.h*
        )
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${TEST_HEADERS})

        list(APPEND LIBRARY_INCLUDE_DIRECTORIES 
            tests/include/common
            tests/include/${PLATFORM}
        )
    endif()

    if(UWP OR WIN32)
        file(GLOB_RECURSE EXTERNAL_PLATFORM_COMMON_HEADERS 
            include/msft/*.h*
        )
        list(APPEND LIBRARY_INCLUDE_DIRECTORIES
            include/msft
        )
    else()
        file(GLOB_RECURSE EXTERNAL_PLATFORM_COMMON_HEADERS 
            include/posix/*.h*
        )
        list(APPEND LIBRARY_INCLUDE_DIRECTORIES
            include/posix
        )
    endif()
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${EXTERNAL_PLATFORM_COMMON_HEADERS})

    if(SHARED)
        add_library(${project_name} SHARED ${PLATFORM_SOURCES} ${COMMON_SOURCES} ${PLATFORM_COMMON_SOURCES} ${TEST_SOURCES} ${EXTERNAL_HEADERS} ${TEST_HEADERS} ${EXTERNAL_PLATFORM_COMMON_HEADERS})
    else()
        add_library(${project_name} STATIC ${PLATFORM_SOURCES} ${COMMON_SOURCES} ${PLATFORM_COMMON_SOURCES} ${TEST_SOURCES} ${EXTERNAL_HEADERS} ${TEST_HEADERS} ${EXTERNAL_PLATFORM_COMMON_HEADERS})
    endif()

    target_link_libraries(${project_name} ${DEPENDENCIES})

    target_include_directories(${project_name} PUBLIC 
       ${LIBRARY_INCLUDE_DIRECTORIES}
    )
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
endfunction()

function(build_executable project_name)
    set(DEPENDENCIES ${ARGV1})
    set(RESOURCES ${ARGV2})

    update_sources()

    set(EXECUTABLE_INCLUDE_DIRECTORIES 
        source/
        source/common
        source/${PLATFORM}
    )

    if(UWP OR WIN32)
        list(APPEND EXECUTABLE_INCLUDE_DIRECTORIES
            source/msft
        )
    else()
        list(APPEND EXECUTABLE_INCLUDE_DIRECTORIES
            source/posix
        )
    endif()

    include_directories(
        ${EXECUTABLE_INCLUDE_DIRECTORIES}
    )

    add_executable(${project_name} WIN32 ${COMMON_SOURCES} ${PLATFORM_SOURCES} ${PLATFORM_COMMON_SOURCES} ${RESOURCES})

    target_link_libraries(${project_name} ${DEPENDENCIES})
    
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
endfunction()