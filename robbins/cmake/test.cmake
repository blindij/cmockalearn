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

set_target_properties(
    unit.x
    PROPERTIES
    LINK_FLAGS  "-Wl,--wrap=accessdata,--wrap=adddata,--wrap=getdata"
)

# add test
add_test(unit ${PROJECT_BINARY_DIR}/bin/unit.x)
