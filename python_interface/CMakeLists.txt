cmake_minimum_required(VERSION 3.4...3.18)
project(qfin)

add_subdirectory(extern/pybind11)
include_directories("${CMAKE_SOURCE_DIR}/random_numbers/include")
include_directories("${CMAKE_SOURCE_DIR}/montecarlo")

pybind11_add_module(qfin src/functions.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_link_libraries(qfin PUBLIC rng)
target_compile_definitions(qfin
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})