include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(
    unit.x
    main.c
)

target_link_libraries(
    unit.x
    m
    ${CMOCKA_LIBRARIES}
    ising
    hdf5
)

#set_target_properties(
#    unit.x
#    PROPERTIES
#    LINK_FLAGS "-Wl, --wrap=<functionnametowrap>"
#)

# make a temporary subdirectory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tmp)

# make a temporary file
#file(WRITE ${PROJECT_BINARY_DIR}/tmp/nintynine.txt "test5test5test5test5test5test5test5test5test5test5test5test5test5test5te
#"
#)

# add test
add_test(${PROJECT_NAME} ${PROJECT_BINARY_DIR}/bin/unit.x)
