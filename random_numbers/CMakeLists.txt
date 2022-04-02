# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.[hc]pp")
add_library(rng STATIC ${_HDRS} ${_SRCS})
message(STATUS "rng: CMAKE_CURRENT_SOURCE_DIR ====== ${CMAKE_CURRENT_SOURCE_DIR} ")
message(STATUS "rng: CMAKE_INSTALL_LIBD ====== ${CMAKE_INSTALL_LIBDIR} ")

target_include_directories(rng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS rng DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/rng)
install(FILES ${_HDRS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/rng)
