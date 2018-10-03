
add_library(
    ${PROJECT_NAME}
    SHARED
    iolib.c
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumer's build
# paths
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes tht project importable from the install directory
# Put the config file in per-project dir (name MUST match),
# can also just go into 'cmake'
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)

# This makes the project importable from the build directory
# export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)
