message(STATUS "Adding dependency utilities")
add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/dependencies/utilities)

message(STATUS "Adding dependency engine")
add_subdirectory(engine ${CMAKE_CURRENT_BINARY_DIR}/dependencies/engine)

#if(UWP)
    message(STATUS "Adding thirdparties")
    add_subdirectory(thirdparty ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
#endif(UWP)