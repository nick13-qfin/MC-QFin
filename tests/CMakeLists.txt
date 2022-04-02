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
set(BOOST_TEST_LOG_LEVEL message)
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

message(STATUS "CMAKE_CURRENT_SOURCE_DIR ====== ${CMAKE_CURRENT_SOURCE_DIR} ")

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#Run through each source
foreach(testSrc ${TEST_SRCS})
    message(STATUS "current filename ====== ${testSrc} ")
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)
    message(STATUS "current testname ====== ${testName} ")
    string(REPLACE test_ "" shname ${testName})
    message(STATUS "current testname ====== ${shname} ")

    #Add compile target
    add_executable(${shname} ${testSrc})
    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${shname} ${Boost_LIBRARIES} rng)
    add_test(NAME ${shname} COMMAND ${shname})

    #add_test(NAME ${testName} COMMAND ${testName})
    ##I like to move testing binaries into a testBin directory
    #set_target_properties(${testName} PROPERTIES
    #    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)
    ##Finally add it to test execution -
    ##Notice the WORKING_DIRECTORY and COMMAND
    #add_test(NAME ${testName}
    #            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
    #            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
    
endforeach(testSrc)



