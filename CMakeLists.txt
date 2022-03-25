# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
project ("MC-QFin")

if(UNIX)
    set(EIGEN3_INCLUDE_DIR "~/Coding/eigen/eigen_build")
endif()
if(WIN32)
#TODO include it here
    set(EIGEN3_INCLUDE_DIR "~/Coding/eigen/eigen_build")
endif()

include_directories(${EIGEN3_INCLUDE_DIR})
enable_testing()

# Include sub-projects.
add_subdirectory (tests)


