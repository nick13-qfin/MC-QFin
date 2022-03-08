# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Test0 VERSION 0.1)
# Add source to this project's executable.
#definitions
add_definitions(-DWIN32)
add_definitions(-DBOOST_UNITTEST)
add_definitions(-DG_NEWIOSTREAM)

# Configure outputs 
#set(ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../output/lib")
#set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../output/lib")
#set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../output/bin")

# Detect operating system
message(STATUS "Operating system is ${CMAKE_SYSTEM_NAME}")
if($(CMAKE_SYSTEM_NAME) STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if($(CMAKE_SYSTEM_NAME) STREQUAL "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()

# Detect host processor 
message (STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

enable_testing()




# At the end find the package, include and link
#find_package(Boost 1.78.0 REQUIRED COMPONENTS unit_test_framework    ) 
#include_directories(${Boost_INCLUDE_DIRS})     

# Configure source files for production code
#file(GLOB SOURCES ../../sources/*.cpp)
# Configure source files for unit-test code
#file(GLOB SOURCES source/*.cpp)
#file(GLOB SOURCES source/subs/*.cpp)

file(GLOB SOURCES *.cpp)

# Tell the cmake what needs to be builded
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable( Test0 ${SOURCES} )

# Tell CMake to link it
#target_link_libraries( Test0 ${Boost_LIBRARIES} )

#add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h")

# TODO: Add tests and install targets if needed.
# tell CMake to use CTest extension
#enable_testing()