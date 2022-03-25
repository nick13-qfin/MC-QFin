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

#### Installation
In order to install Boost:
- see general instructions  from [here](https://www.boost.org/)
- for Linux, from [here](https://www.boost.org/doc/libs/1_62_0/more/getting_started/unix-variants.html).

#### Specifying its folder path
Its location must be specified in Cmake [tests/CMakeLists.txt](tests/CMakeLists.txt). Currently it is:
- in Linux: 
  ```cmake
  set(BOOST_ROOT "~/Coding/boost/boost_1_77_0")
  set(BOOST_INCLUDEDIR "~/Coding/boost/boost_1_77_0")
  set(BOOST_LIBRARYDIR "~/Coding/boost/boost_1_77_0/stage/lib")
  ```
- in Windows:
  ```cmake
  set(BOOST_ROOT "c:\\dev\\boost_1_78_0")
  set(BOOST_INCLUDEDIR "C:\\dev\\boost_1_78_0\\boost")
  set(BOOST_LIBRARYDIR "C:\\dev\\boost_1_78_0\\stage\\lib")
  ```
 ### 2. Eigen
Eigen is the solution of choice for representing linear algebra matrices `A` and their operations, e.g. `A^T` or `ABc`, as long as realization of multi-dimentional stochastic processes `(X_t, t>0)` 
 
#### Installation
In order to install Eigen, you need to download it (see instructions [here](http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)). 

In order to include Eigen in Cmake, it must be installed from the `INSTALL` file:
```
Let's call this directory 'source_dir' (where this INSTALL file is).
Before starting, create another directory which we will call 'build_dir'.

Do:

  cd build_dir
  cmake source_dir
  make install
 ```
 #### Specifying its folder path
 Differently from Boost, that is only used for testing, Eigen is used by all the projects and its path is therefore specifyied in the main cmakelist file [here](CMakeLists.txt), using the following commands
 ```cmake
 set(EIGEN3_INCLUDE_DIR "~/Coding/eigen/eigen_build")
 include_directories(${EIGEN3_INCLUDE_DIR})
 ```
