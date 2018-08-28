include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(
    unit.x
    main.c
)

target_link_libraries(
    unit.x
    ${CMOCKA_LIBRARIES}
    ${PROJECT_NAME}
)

#set_target_properties(
#    unit.x
#    PROPERTIES
#    LINK_FLAGS "-Wl, --wrap=<functionnametowrap>"
#)

# make a temporary subdirectory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tmp)

# make a temporary file
file(WRITE ${PROJECT_BINARY_DIR}/tmp/nintynine.txt "test5test5test5test5test5test5test5test5test5test5test5test5test5test5te
"
)

# add test
add_test(unit ${PROJECT_BINARY_DIR}/bin/unit.x)
