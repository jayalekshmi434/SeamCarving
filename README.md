# CPPND: Capstone Hello World Repo

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* OpenCV >= 4.1
    The OpenCV 4.1.0 source code can be found here

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./HelloWorld`.

| Sl no| Specification                                              |                     |
|------|------------------------------------------------------------|---------------------|
|    1 | The project uses Object Oriented Programming techniques.   |:heavy_check_mark:   | 
|    2 | Classes use appropriate access specifiers for class members|:heavy_check_mark:   |                                                          |               |    3 | Class constructors utilize member initialization lists.    |:heavy_check_mark:   |
|    4 | Classes abstract  details from their interfaces.           |:heavy_check_mark:   |
|    5 |Classes encapsulate behavior                                |:heavy_check_mark:   |
|    6 |Overloaded functions allow the same function to operate <br>on different parameters.|:heavy_check_mark:   |
|    7 |The project makes use of references in function declarations| :heavy_check_mark:  |
|    8 |The project uses destructors appropriately.                 |                     |
|    9 |At least one class uses unmanaged dynamically allocated <br>memory, along with any class that otherwise needs<br> to modify state upon the termination of an object<br> uses a destructor.|:heavy_check_mark: |
|   10|The project uses multiple threads in the execution.          |:heavy_check_mark:   |
|   11|A mutex or lock (e.g. std::lock_guard or `std::unique_lock)<br> is used to protect data that is shared across<br> multiple threads in the project code.|:heavy_check_mark:|

