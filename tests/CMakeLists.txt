# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

#project(Test1 VERSION 0.1)
# Settings the Boost Library 
set(Boost_USE_STATIC_LIBS ON) 
add_definitions(-DBOOST_UNITTEST)

#set(Boost_USE_MULTITHREADED OFF)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
#add_definitions(-DBOOST_TEST_DYN_LINK) 
#add_definitions(-DBOOST_UNITTEST)

#set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_DEBUG ON)
if(UNIX)
    message(STATUS "Siamo in ${CMAKE_SYSTEM_NAME}")
    add_definitions(-DSYSTEM_LINUX)
    set(BOOST_ROOT "~/Coding/boost/boost_1_77_0")
    set(BOOST_INCLUDEDIR "~/Coding/boost/boost_1_77_0/boost")
    set(BOOST_LIBRARYDIR "~/Coding/boost/boost_1_77_0/stage/lib")
endif(UNIX)
if(WIN32)
    set(Boost_COMPILER -vc143)
    set(BOOST_ROOT "c:\\dev\\boost_1_78_0")
    set(BOOST_INCLUDEDIR "C:\\dev\\boost_1_78_0\\boost")
    set(BOOST_LIBRARYDIR "C:\\dev\\boost_1_78_0\\stage\\lib")
endif(WIN32)

add_library(mylib INTERFACE)
#target_sources(mylib INTERFACE lib/parameter.h)
message(STATUS "lib in : ${PROJECT_SOURCE_DIR}/lib")
target_include_directories(mylib INTERFACE "${PROJECT_SOURCE_DIR}/lib")

#find_package(Boost REQUIRED)
#find_package(Boost COMPONENTS system filesystem unit_test_framework)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
#C:\dev\vcpkg\scripts\buildsystems\vcpkg.cmake

if(Boost_FOUND)
    message(STATUS "aggio trovato ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})     

    # Add source to this project's executable.
    add_executable (test1 "test1.cpp")
    #  target_link_libraries(test1
    #                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    #                      )
    #target_include_directories(test1 PUBLIC
    #                        ${Boost_INCLUDE_DIRS}
    #                        )
    find_library(LIB mylib)
    target_link_libraries(test1 INTERFACE ${LIB})
    #target_link_libraries(test1 ${Boost_LIBRARIES} )
#    ${Boost_FILESYSTEM_LIBRARY}
#                      ${Boost_SYSTEM_LIBRARY}
# TODO: Add tests and install targets if needed.
# tell CMake to use CTest extension
    #add_test(Test1 test1)

endif()


