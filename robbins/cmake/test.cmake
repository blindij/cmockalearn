include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(
    unit.x
    test/main.c
)

target_link_libraries(
    unit.x
    ${CMOCKA_LIBRARIES}
    ${PROJECT_NAME}
)
