add_executable(
    dset.x
    basic_hdf5_ex.c
)

target_link_libraries(
    dset.x
    hdf5
)
