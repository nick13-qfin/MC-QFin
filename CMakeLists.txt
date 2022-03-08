# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
project ("CMakeProject1")
enable_testing()

# Include sub-projects.
add_subdirectory (CMakeProject1)
add_subdirectory (tests)





#add_excecutable(testTheTester test1.cpp)
#target_link_libraries(test_unit CMakeProject1

