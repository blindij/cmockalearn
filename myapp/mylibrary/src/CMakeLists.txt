add_executable(
    ${PROJECT_NAME}.x
    myapp.c
    myapp_test.c
)

target_link_libraries(
    ${PROJECT_NAME}.x
    ${CMOCKA_LIBRARIES}
)

install(
    TARGETS ${PROJECT_NAME}.x
    RUNTIME DESTINATION bin
)

