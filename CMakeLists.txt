# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
if(UNIX)
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-10") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -D_GLIBCXX_DEBUG")
endif()

project ("MC-QFin")

set(CMAKE_CXX_STANDARD 20)


set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(EIGEN_DIR "~/Coding/eigen/eigen-3.4.0")
    #set(GCC_COVERAGE_COMPILE_FLAGS "-fconcepts")
    #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()
if(WIN32)
    set(EIGEN_DIR "c:\\dev\\eigen\\eigen-3.4.0")
endif()
#     set(EIGEN3_INCLUDE_DIR "~/Coding/eigen/eigen_build")

# include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${EIGEN_DIR})
enable_testing()

# Include sub-projects.
add_subdirectory (tests)


