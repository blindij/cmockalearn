add_library(
    myapp
    SHARED
    myapp.c
)

add_executable(
    ${PROJECT_NAME}.x
    myapp_test.c
)

target_link_libraries(
    ${PROJECT_NAME}.x
    myapp
    m
    ${CMOCKA_LIBRARIES}
)

install(
    TARGETS ${PROJECT_NAME}.x
    RUNTIME DESTINATION bin
)

install(
    TARGETS myapp
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
