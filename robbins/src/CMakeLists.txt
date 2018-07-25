add_executable(
    ${PROJECT_NAME}.x
    showtimes.c
)

target_link_libraries(
    ${PROJECT_NAME}.x
    ${CMOCKA_LIBRARIES}
)
