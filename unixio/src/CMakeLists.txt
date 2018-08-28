add_executable(
    ${PROJECT_NAME}.x
    showfile.c
)

add_library(
    ${PROJECT_NAME}
    SHARED
    iolib.c
)

target_link_libraries(
    ${PROJECT_NAME}.x
    ${CMOCKA_LIBRARIES}
    ${PROJECT_NAME}
)
