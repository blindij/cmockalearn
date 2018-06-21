add_executable(
    ${PROJECT_NAME}.x
    simple_test.c
)

target_link_libraries(
    ${PROJECT_NAME}.x
    m
    ${CMOCKA_LIBRARIES}
)
