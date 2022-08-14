# Content Aware Image Resizing

This project is an implementation of Seam carving (or liquid rescaling) which  an algorithm for content-aware image resizing, developed by Shai Avidan, of Mitsubishi Electric Research Laboratories (MERL), and Ariel Shamir, of the Interdisciplinary Center and MERL. It functions by establishing a number of seams (paths of least importance) in an image and automatically removes seams to reduce image size or inserts seams to extend it. Seam carving also allows manually defining areas in which pixels may not be modified, and features the ability to remove whole objects from photographs.

Reference : [https://faculty.runi.ac.il/arik/scweb/imret/index.html](http://graphics.cs.cmu.edu/courses/15-463/2012_fall/hw/proj3-seamcarving/imret.pdf)
          : https://github.com/esimov/caire/tree/e5f861daa4f19614e6315cc45686ded67fb6353f
## Results
<img src="Data/snow.gif"/>
![alt text](https://github.com/jayalekshmi434/SeamCarving/blob/master/Results/result1.JPG)
![alt text](https://github.com/jayalekshmi434/SeamCarving/blob/master/Results/result2.JPG)
![alt text](https://github.com/jayalekshmi434/SeamCarving/blob/master/Results/result3.JPG)
![alt text](https://github.com/jayalekshmi434/SeamCarving/blob/master/Results/result4.JPG)

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
4. Run it: `./SeamCarving --image ../Data/broadway.jpg`

## Use the following keys to resize :
* l----> to decrease width
* r----> to increase width
* d----> to decrease height
* u----> to increase height


Class Information:
![alt text](https://github.com/jayalekshmi434/SeamCarving/blob/master/Results/classdiag.JPG)
