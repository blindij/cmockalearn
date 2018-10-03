include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(
    unit.x
    main.c
)

target_link_libraries(
    unit.x
    m
    ${CMOCKA_LIBRARIES}
    ${PROJECT_NAME}
)

# add test
add_test(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/bin/unit.x)
