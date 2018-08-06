cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(robbins)
enable_language(C)

# set the C standard
set(C_STANDARD 99)
set(CMAKE_C_COMPILER clang)

# specify the build type - types: Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Debug)

# set CTest
include(CTest)

# specify where to place binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/lib
)

# Enable creating a compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Options
option(ENABLE_OpenMP "Enable OpenMP" OFF)
option(ENABLE_MPI "Enable MPI" OFF)
option(ENABLE_CMOCKA "Enable CMokca" ON)

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

# Our additional modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(test)

add_subdirectory(src)
