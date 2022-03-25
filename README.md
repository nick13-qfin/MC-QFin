# MC-QFin
Place holder for MC-related experiments with C++.

The project uses CMake to build both on Linux and on Windows.

## Prerequisites
In order to compile the project, you must have 
- Boost
- Eigen
installed.
### 1. Boost
At this stage, Boost is only used to run unit testing.

Install Boost (see instructions starting from [here](https://www.boost.org/)). 
Its location is specified in Cmake [tests/CMakeLists.txt](tests/CMakeLists.txt):
- in Linux: 
  ```
  set(BOOST_ROOT "~/Coding/boost/boost_1_77_0")
  set(BOOST_INCLUDEDIR "~/Coding/boost/boost_1_77_0")
  set(BOOST_LIBRARYDIR "~/Coding/boost/boost_1_77_0/stage/lib")
  ```
- in Windows:
  ```
  set(BOOST_ROOT "c:\\dev\\boost_1_78_0")
  set(BOOST_INCLUDEDIR "C:\\dev\\boost_1_78_0\\boost")
  set(BOOST_LIBRARYDIR "C:\\dev\\boost_1_78_0\\stage\\lib")
  ```
 ### 2. Eigen
Eigen is the solution of choice for representing linear algebra matrices `A` and their operations as long as realization of multi-dimentional stochastic processes `X_t` 
 
