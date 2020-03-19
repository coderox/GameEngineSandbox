cmake_minimum_required(VERSION 3.8)

set(GAME_TO_BUILD snake)
project(${GAME_TO_BUILD})

include(dependencies/pipeline/functions.cmake)
initialize_pipeline()

message(STATUS "Building '${GAME_TO_BUILD}' for platform ${PLATFORM}")

# Add dependencies for client project
add_subdirectory(dependencies)
add_subdirectory(${GAME_TO_BUILD})

if(TESTS)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)
else()
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${GAME_TO_BUILD})
endif()