# Content Aware Image Resizing

Seam carving (or liquid rescaling) is an algorithm for content-aware image resizing, developed by Shai Avidan, of Mitsubishi Electric Research Laboratories (MERL), and Ariel Shamir, of the Interdisciplinary Center and MERL. It functions by establishing a number of seams (paths of least importance) in an image and automatically removes seams to reduce image size or inserts seams to extend it. Seam carving also allows manually defining areas in which pixels may not be modified, and features the ability to remove whole objects from photographs.

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

