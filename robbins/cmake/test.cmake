add_executable(
    unit.x
    test/main.c
)

target_link_libraries(
    unit.x
    ${CMOCKA_LIBRARIES}
    ${PROJECT_NAME}
)
