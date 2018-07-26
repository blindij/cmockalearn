add_executable(
    ${PROJECT_NAME}.x
    showtimes.c
)

add_library(
    ${PROJECT_NAME}
    SHARED
    listlib.c
)

target_link_libraries(
    ${PROJECT_NAME}.x
    ${CMOCKA_LIBRARIES}
    ${PROJECT_NAME}
)
