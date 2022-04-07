cmake_minimum_required(VERSION 3.4...3.18)
project(cmake_example)

add_subdirectory(extern/pybind11)
include_directories("${CMAKE_SOURCE_DIR}/random_numbers/include")
pybind11_add_module(rand src/functions.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_link_libraries(rand PUBLIC rng)
target_compile_definitions(rand
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})