cmake_minimum_required(VERSION 3.8)
project(game_engine_sandbox)

if(MSVC)
  if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
    set(UWP 1)
    set(PLATFORM UWP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /await")
  else()
    set(PLATFORM WIN32)
  endif()
else()
  set(PLATFORM OSX)
endif()

include(dependencies/pipeline/functions.cmake)

# Enable folders grouping in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Add dependencies for client project
add_subdirectory(dependencies)
add_subdirectory(game)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)