# MC-QFin
Place holder for MC-related experiments with C++.

The project is made of 3 libraries:
- [montecarlo](/montecarlo) is a headers-only lib that defines a MC engine and all the needed components (evol schemes, SDEs, parameters)
- [random_numbers](/random_number) is a static library used to generate random numbers
- [interpolation](/interpolation) is a static library used for interpolations

and 
- a [test](/tests) suite
- a [python interface](/python_interface). 
 
[pybind](https://pybind11.readthedocs.io/en/latest/) is used to expose functions to Python.

CMake is used to build both on Linux and on Windows.
Currently it is tested on: 
- Win: VS2022 community edition 
- Linux: Kdevelop

## Table of contents
- [Prerequisites](#prerequisites)
  - [Boost](#boost)
  - [Eigen](#eigen)
  - [CXX20 compiler](#cxx20-compiler)
- [Using Python](#using-python)
- [Open points](#open-points)
  - [Dates](#dates-handling)

References:
- LaTeX in this Readme: [https://latex.codecogs.com/](https://latex.codecogs.com/) (set svg and HTML)

## Prerequisites
The components needed to be installed in order to compile the project:
-  [Boost](#boost) for unit testing;
-  [Eigen](#eigen) for linear algebra as well as 2d containers;
-  [C++20](#cxx20-compiler) for using C++20 features.


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
### CXX20 compiler
#### Windows
No need to do anything if you are using VS2022
#### Linux (Ubuntu 20.4)
Ubuntu 20.4 comes with GCC9 installed and unfortunately this does not support C++20.
Support for C++20 features like `concepts` and `requires` can be obtained by:
1. Installing GCC10. In order to do this, run the following
```unix
sudo apt install -y gcc-10 g++-10 cpp-10
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 --slave /usr/bin/g++ g++ /usr/bin/g++-10 --slave /usr/bin/gcov gcov /usr/bin/gcov-10
```
2. Specifying the new compiler in CMake. This must be done before naming the project, in the main `CMakelists.txt` file:
```cmake
cmake_minimum_required (VERSION 3.8)
if(UNIX)
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-10") 
    set(CMAKE_CXX_FLAGS -std=c++2a)
endif()

project ("MC-QFin")
```

Note: you might have to delete `CMakeCache.txt` for `CMAKE_CXX_COMPILER` to be correctly updated.


## Using Python
### Windows 10
On Windows, I am using VScode to create notebooks.
In order to do that, you need to:
- install Python see [here](https://docs.python.org/3/installing/index.html)
- select a python interpreter (ctrl-shift-p).

For additional packages, I recommend going to cmd and doing the following:
```
python -m pip install <package-name>
```
#### Note
`cmd` will give you a warning
```
  WARNING: The scripts fonttools.exe, pyftmerge.exe, pyftsubset.exe and ttx.exe are installed in 'C:\Users\nicol\AppData\Local\Packages\PythonSoftwareFoundation.Python.3.10_qbz5n2kfra8p0\LocalCache\local-packages\Python310\Scripts' which is not on PATH.
```
This is due to Windows sandboxing python. 
One solution to this is to check the current python path in python:
```python
import sys
print(sys.path)
```
and then copying the installed binaries in the folders already in python path.

### Linux (Ubuntu 20.4)
Ubuntu comes with Python already installed



## Open points
### Dates handling
I am exploring using `std::chrono` new C++20 features, like `chrono::year_month_day` which looks promising.
However, while this is currently supported in VS2022, it is still under development work in GCC.

Useful resources:
- GCC current lib book of work -> [here](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html#status.iso.2020);
- a date headers-only library that might be used as a replacement in the meantime -> [here](https://github.com/HowardHinnant/date).


