cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(stencil4p)
enable_language(C)

#set the C standard
set(C_STANDARD 99)

# specify build type - types Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Debug)

# specify where to place binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
    )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/lib
    )

## find OpenMP
#find_package(OpenMP)
#if (OPENMP_FOUND)
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif()

## Options 
option(ENABLE_MPI "Enable MPI" OFF)
option(ENABLE_CMOCKA "Enable CMocka" ON)

if (ENABLE_MPI)
   find_package(MPI)
      if (MPI_FOUND)
            include_directories(${MPI_INCLUDE_PATH})
            add_definitions(-DENABLE_MPI)
     else()
            message(FATAL_ERROR "Could not find any MPI installation, check $PATH")  # CMake Error, stop processing and generation
     endif()
endif()
if (ENABLE_CMOCKA)
   find_package(CMOCKA REQUIRED)
       if (CMOCKA_FOUND)
        include_directories(${CMOCKA_INCLUDE_DIR})
        message(STATUS "CMocka include dir: ${CMOCKA_INCLUDE_DIR}")
       else()
        message(FATAL_ERROR "Could not find any CMocka installation")
       endif()
endif()

add_subdirectory(src)
