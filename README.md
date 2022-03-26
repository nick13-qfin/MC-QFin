# MC-QFin
Place holder for MC-related experiments with C++.

The project uses CMake to build both on Linux and on Windows.

References:
- LaTeX in this Readme: [https://latex.codecogs.com/](https://latex.codecogs.com/) (set svg and HTML)

## Prerequisites
In order to compile the project, you must install 
-  [Boost](#boost)
-  [Eigen](#eigen)
### Boost
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
 ### Eigen
Eigen is the solution of choice for representing linear algebra matrices
<img src="https://latex.codecogs.com/svg.image?\bf&space;A&space;&space;" title="https://latex.codecogs.com/svg.image?\bf A " />
and their operations, e.g. 
<img src="https://latex.codecogs.com/svg.image?\bf&space;A^T&space;&space;" title="https://latex.codecogs.com/svg.image?\bf A^T " /> 
or 
<img src="https://latex.codecogs.com/svg.image?\bf&space;A&space;\bf&space;b&space;&space;" title="https://latex.codecogs.com/svg.image?\bf A \bf b " />
, as long as realization of multi-dimentional stochastic processes 
<img src="https://latex.codecogs.com/svg.image?({X}_t,\&space;t&space;\geq&space;0)&space;&space;" title="https://latex.codecogs.com/svg.image?({X}_t,\ t \geq 0) " />
 
#### Installation
In order to install Eigen, you need to download it (see instructions [here](http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)). 

##### Linux
In order to include Eigen in Cmake, it must be installed first (even if it is a header-only file).
This is an extract from the `INSTALL` file that explains the steps:
```
Let's call this directory 'source_dir' (where this INSTALL file is).
Before starting, create another directory which we will call 'build_dir'.

Do:

  cd build_dir
  cmake source_dir
  make install
 ```
 Once this is done we would be able to, e.g., `#include <eigen3/Eigen/Dense>`. 
 The following symbolic link enables us to use `#include <Eigen/Dense>` instead:
 ```
 cd /usr/local/include
sudo ln -sf eigen3/Eigen Eigen
 ```
 ##### Windows
No need to install it. We just include the extracted headers-only library path (see next section).
 #### Specifying its folder path
 Differently from Boost, that is only used for testing, Eigen is used by all the projects and its path is therefore specifyied in the main cmakelist file [here](CMakeLists.txt), using the following commands
 ```cmake
if(UNIX)
    set(EIGEN_DIR "~/Coding/eigen/eigen-3.4.0")
endif()
if(WIN32)
    set(EIGEN_DIR "c:\\dev\\eigen\\eigen-3.4.0")
endif()
include_directories(${EIGEN_DIR})
 ```

