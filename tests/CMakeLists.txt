# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Test1 VERSION 0.1)
# Settings the Boost Library 
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_DEBUG ON)
set(Boost_COMPILER -vc143)

#set(-DBoost_DEBUG ON)
set(BOOST_ROOT "c:\\dev\\boost_1_78_0")
set(BOOST_INCLUDEDIR "C:\\dev\\boost_1_78_0\\boost")
set(BOOST_LIBRARYDIR "C:\\dev\\boost_1_78_0\\stage\\lib")
set(Boost_USE_STATIC_LIBS ON)

#set(BOOST_ROOT "C:\\dev\\vcpkg\\installed\\x86-windows-static")
#set(BOOST_INCLUDEDIR "C:\\dev\\vcpkg\\installed\\x86-windows-static\\include\\boost")
#set(BOOST_LIBRARYDIR "C:\\dev\\vcpkg\\installed\\x86-windows-static\\lib")

#find_package(Boost REQUIRED)
find_package(Boost COMPONENTS system filesystem unit_test_framework)
#C:\dev\vcpkg\scripts\buildsystems\vcpkg.cmake
include_directories(${Boost_INCLUDE_DIRS})     


# Add source to this project's executable.
add_executable (test1 "test1.cpp")
target_link_libraries(test1
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )
#    ${Boost_FILESYSTEM_LIBRARY}
#                      ${Boost_SYSTEM_LIBRARY}
# TODO: Add tests and install targets if needed.
# tell CMake to use CTest extension
add_test(Test1 test1)