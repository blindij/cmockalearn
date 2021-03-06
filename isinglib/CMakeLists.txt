cmake_minimum_required(VERSION 3.6)
project(ising C)
enable_language(C)

# set the C standard
set(C_STANDARD 99)

# specify the build type
# build types: Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Debug)

# set install prefix
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/local)
include(GNUInstallDirs)

# set CTest
include(CTest)

# specifiy where to place binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/lib
)

#  Enable createing a compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Options
option(ENABLE_OpenMP "Enable OpenMP" OFF)
option(ENABLE_MPI "Enable MPI" OFF)
option(ENABLE_CMOCKA "Enable CMocka" ON)
option(ENABLE_HDF5 "Enable HDF5" OFF)

### find OpenMP
if (ENABLE_OpenMP)
    find_package(OpenMPi Required)
        if (OpenMP_FOUND)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS ${OpenMP_C_FLAGS}")
        else()
            message(FATAL_ERROR "Could not find OpenMP library") # CMake Error, stop processing and generation
        endif()
endif()

### find MPI
if (ENABLE_MPI)
   find_package(MPI)
      if (MPI_FOUND)
            include_directories(${MPI_INCLUDE_PATH})
            add_definitions(-DENABLE_MPI)
     else()
            message(FATAL_ERROR "Could not find any MPI installation, check $PATH")  # CMake Error, stop processing and generation
     endif()
endif()

### find CMocka
if (ENABLE_CMOCKA)
   find_package(CMOCKA REQUIRED)
       if (CMOCKA_FOUND)
        include_directories(${CMOCKA_INCLUDE_DIR})
        message(STATUS "CMocka include dir: ${CMOCKA_INCLUDE_DIR}")
       else()
        message(FATAL_ERROR "Could not find any CMocka installation")
       endif()
endif()

### find HDF5
if (ENABLE_HDF5)
#    set(HDF5_ROOT $ENV{HOME}/local/hdf5-1.10.3)
    find_package(HDF5 REQUIRED)
    if (${HDF5_FOUND})
        include_directories(${HDF5_INCLUDE_DIRS})
        link_directories(${HDF5_LIBRARIES})
        message(STATUS "HDF5 found, version: ${HDF5_VERSION}")
    else()
        message(FATAL_ERROR "Could not find any HDF5 library")
    endif()
endif()

### find OpenMP
if (ENABLE_OpenMP)
    find_package(OpenMPi Required)
        if (OpenMP_FOUND)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS ${OpenMP_C_FLAGS}")
        else()
            message(FATAL_ERROR "Could not find OpenMP library") # CMake Error, stop processing and generation
        endif()
endif()

### find MPI
if (ENABLE_MPI)
   find_package(MPI)
      if (MPI_FOUND)
            include_directories(${MPI_INCLUDE_PATH})
            add_definitions(-DENABLE_MPI)
     else()
            message(FATAL_ERROR "Could not find any MPI installation, check $PATH")  # CMake Error, stop processing and generation
     endif()
endif()

### find CMocka
if (ENABLE_CMOCKA)
   find_package(CMOCKA REQUIRED)
       if (CMOCKA_FOUND)
        include_directories(${CMOCKA_INCLUDE_DIR})
        message(STATUS "CMocka include dir: ${CMOCKA_INCLUDE_DIR}")
       else()
        message(FATAL_ERROR "Could not find any CMocka installation")
       endif()
endif()

### find HDF5
if (ENABLE_HDF5)
#    set(HDF5_ROOT $ENV{HOME}/local/hdf5-1.10.3)
    find_package(HDF5 REQUIRED)
    if (${HDF5_FOUND})
        include_directories(${HDF5_INCLUDE_DIRS})
        link_directories(${HDF5_LIBRARIES})
        message(STATUS "HDF5 found, version: ${HDF5_VERSION}")
    else()
        message(FATAL_ERROR "Could not find any HDF5 library")
    endif()
endif()

if (ENABLE_OpenMP)
    find_package(OpenMPi Required)
        if (OpenMP_FOUND)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS ${OpenMP_C_FLAGS}")
        else()
            message(FATAL_ERROR "Could not find OpenMP library") # CMake Error, stop processing and generation
        endif()
endif()

### find MPI
if (ENABLE_MPI)
   find_package(MPI)
      if (MPI_FOUND)
            include_directories(${MPI_INCLUDE_PATH})
            add_definitions(-DENABLE_MPI)
     else()
            message(FATAL_ERROR "Could not find any MPI installation, check $PATH")  # CMake Error, stop processing and generation
     endif()
endif()

### find CMocka
if (ENABLE_CMOCKA)
   find_package(CMOCKA REQUIRED)
       if (CMOCKA_FOUND)
        include_directories(${CMOCKA_INCLUDE_DIR})
        message(STATUS "CMocka include dir: ${CMOCKA_INCLUDE_DIR}")
       else()
        message(FATAL_ERROR "Could not find any CMocka installation")
       endif()
endif()

### find HDF5
if (ENABLE_HDF5)
#    set(HDF5_ROOT $ENV{HOME}/local/hdf5-1.10.3)
    find_package(HDF5 REQUIRED)
    if (${HDF5_FOUND})
        include_directories(${HDF5_INCLUDE_DIRS})
        link_directories(${HDF5_LIBRARIES})
        message(STATUS "HDF5 found, version: ${HDF5_VERSION}")
    else()
        message(FATAL_ERROR "Could not find any HDF5 library")
    endif()
endif()

# include projects own header files
message(STATUS "src dir: ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# The source directory
add_subdirectory(src)

# The test directory
add_subdirectory(test)
