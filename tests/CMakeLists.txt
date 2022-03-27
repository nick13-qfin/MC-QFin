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
#     set(EIGEN3_INCLUDE_DIR "~/Coding/eigen/eigen_build")
#     include_directories(${EIGEN3_INCLUDE_DIR})
    set(BOOST_ROOT "~/Coding/boost/boost_1_77_0")
    set(BOOST_INCLUDEDIR "~/Coding/boost/boost_1_77_0")
    set(BOOST_LIBRARYDIR "~/Coding/boost/boost_1_77_0/stage/lib")
endif()
if(WIN32)
    set(Boost_COMPILER -vc143)
    set(BOOST_ROOT "c:\\dev\\boost_1_78_0")
    set(BOOST_INCLUDEDIR "C:\\dev\\boost_1_78_0\\boost")
    set(BOOST_LIBRARYDIR "C:\\dev\\boost_1_78_0\\stage\\lib")
endif()




#find_package(Boost REQUIRED)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})     

message(STATUS "boost Library ${Boost_LIBRARIES}")
message(STATUS "boost unit test  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")



# Add source to this project's executable.
add_executable (param "test_param.cpp"  )
target_link_libraries(param ${Boost_LIBRARIES})
# tell CMake to use CTest extension
add_test(NAME tp COMMAND param)

add_executable (interp test_interp.cpp  )
target_link_libraries(interp ${Boost_LIBRARIES})
add_test(NAME ti COMMAND interp)


