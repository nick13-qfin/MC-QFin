# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")
add_library(interp STATIC ${_HDRS} ${_SRCS})
message(STATUS "interp: CMAKE_CURRENT_SOURCE_DIR ====== ${CMAKE_CURRENT_SOURCE_DIR} ")
message(STATUS "interp: CMAKE_INSTALL_LIBD ====== ${CMAKE_INSTALL_LIBDIR} ")

target_include_directories(interp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(interp PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS interp DESTINATION  lib)
install(FILES ${_HDRS} DESTINATION include)
