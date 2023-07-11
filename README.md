# SFND 2D Feature Tracking
## Project Rubric
### Step1: Mid-Term Report
|Success Criteria|Specifications|Details|
|---|---|---|
| MP.0 Mid Term Report| <span style= "color:green">&#x2713;</span> Done:<br>[Readme](https://github.com/mcitir/SFND_2D_Feature_Tracking/blob/main/README.md)||
| MP.1 Data Buffer Optimization| <span style= "color:green">&#x2713;</span> Done|Codes updated|
| MP.2 Keypoint Detection|<span style= "color:green">&#x2713;</span> Done|Codes updated|
| MP.3 Keypoint Removal|<span style= "color:green">&#x2713;</span> Done|Codes updated|
| MP.4 Keypoint Descriptors|<span style= "color:green">&#x2713;</span> Done|Codes updated|
| MP.5 Descrriptor Matching|<span style= "color:green">&#x2713;</span> Done|Codes updated|
| MP.6 Descriptor Distance Ratio|<span style= "color:green">&#x2713;</span> Done|Codes updated|
| MP.7 Performance Evaluation 1|<span style= "color:green">&#x2713;</span> Done|[Section > MP.7](#mp7)|
| MP.8 Performance Evaluation 2|<span style= "color:green">&#x2713;</span> Done|[Section > MP.8](#mp8)|
| MP.9 Performance Evaluation 3|<span style= "color:green">&#x2713;</span> Done|[Section > MP.9](#mp9)|


#### MP.7 Performance Evaluation 1 {#mp7}
|Detector|Average number of Keypoints|Average Time (ms)|
|:------:|:-------------------------:|:---------------:|
|SHITOMASI|117.9|8.52|
|HARRIS|24.8|8.53|
|FAST|149.1|0.91|
|BRISK|276.2|65.88|
|ORB|116.1|7.99|
|AKAZE|167|56.21|
|SIFT|138.6|80.18|

#### MP.8 Performance Evaluation 2 {#mp8}
|Detector/Descriptor|Avg. # of Keypoints in ROI|Avg. # of Keypoints|
|:-----------------:|:------------------------:|:-----------------:|
|**SHITOMASI**      |                          |                   |
|**_** + BRISK      |117.9                     |1342.3             |
|**_** + BRIEF      |117.9                     |1342.3             |
|**_** + ORB        |117.9                     |1342.3             |
|**_** + FREAK      |117.9                     |1342.3             |
|**_** + AKAZE      |N/A                       |N/A                |
|**_** + SIFT       |N/A                       |N/A                |
|**HARRIS**         |                          |                   |
|**_** + BRISK      |24.8                      |173.7              |
|**_** + BRIEF      |24.8                      |173.7              |
|**_** + ORB        |24.8                      |173.7              |
|**_** + FREAK      |24.8                      |173.7              |
|**_** + AKAZE      |N/A                       |N/A                |
|**_** + SIFT       |N/A                       |N/A                |
|**FAST**           |                          |                   |
|**_** + BRISK      |149.1                     |1787.4             |
|**_** + BRIEF      |149.1                     |1787.4             |
|**_** + ORB        |149.1                     |1787.4             |
|**_** + FREAK      |149.1                     |1787.4             |
|**_** + AKAZE      |N/A                       |N/A                |
|**_** + SIFT       |N/A                       |N/A                |
|**BRISK**          |                          |                   |
|**_** + BRISK      |276.2                     |2711.6             |
|**_** + BRIEF      |276.2                     |2711.6             |
|**_** + ORB        |276.2|2711.6|
|**_** + FREAK      |276.2|2711.6|
|**_** + AKAZE      |N/A|N/A|
|**_** + SIFT       |N/A|N/A|
|**ORB**|           ||
|**_** + BRISK      |116.1|500|
|**_** + BRIEF      |116.1|500|
|**_** + ORB        |116.1|500|
|**_** + FREAK      |116.1|500|
|**_** + AKAZE      |N/A|N/A|
|**_** + SIFT       |N/A|N/A|
|**AKAZE**|         ||
|**_** + BRISK      |167|1342.9|
|**_** + BRIEF      |167|1342.9|
|**_** + ORB        |167|1342.9|
|**_** + FREAK      |167|1342.9|
|**_** + AKAZE      |167|1342.9|
|**_** + SIFT       |N/A|N/A|
|**SIFT**|          ||
|**_** + BRISK      |138.6|1385.9|
|**_** + BRIEF      |138.6|1385.9|
|**_** + ORB        |N/A|N/A|
|**_** + FREAK      |138.6|1385.9|
|**_** + AKAZE      |N/A|N/A|
|**_** + SIFT       |N/A|N/A|


#### MP.9 Performance Evaluation 3  {#mp9}
##### Average Processing (Detection + Extraction) Time (ms)
|Detector/Descriptor|BRISK|BRIEF|ORB|FREAK|AKAZE|SIFT|
|---|---|---|---|---|---|---|
|SHITOMASI|11.491|12.567|10.375|29.437|N/A|N/A|
|HARRIS|9.898|9.927|8.940|30.539|N/A|N/A|
|FAST|2.836|1.511|1.689|23.4052|N/A|N/A|
|BRISK|35.436|34.828|39.396|59.331|N/A|N/A|
|ORB|8.270|6.851|9.824|26.088|N/A|N/A|
|AKAZE|65.654|75.381|68.722|79.432|123.847|N/A|
|SIFT|85.498|79.344|N/A|95.240|N/A|N/A|

If the TOP 3 detector + descriptor combination has to be selected, the FAST detector can be selected because of its speed. Despite its speed, it can detect a high number of key points. Meanwhile, HARRIS detector seems to be fast enough, but its detection ability is too low. Therefore, after FAST, the ORB detector can be selected with the BRIEF or BRISK identifier.

|TOP3|
|-|
|FAST+BRIEF|
|FAST+ORB|
|FAST+BRISK|


## Previous README
<img src="images/keypoints.png" width="820" height="248" />

The idea of the camera course is to build a collision detection system - that's the overall goal for the Final Project. As a preparation for this, you will now build the feature tracking part and test various detector / descriptor combinations to see which ones perform best. This mid-term project consists of four parts:

* First, you will focus on loading images, setting up data structures and putting everything into a ring buffer to optimize memory load. 
* Then, you will integrate several keypoint detectors such as HARRIS, FAST, BRISK and SIFT and compare them with regard to number of keypoints and speed. 
* In the next part, you will then focus on descriptor extraction and matching using brute force and also the FLANN approach we discussed in the previous lesson. 
* In the last part, once the code framework is complete, you will test the various algorithms in different combinations and compare them with regard to some performance measures. 

See the classroom instruction and code comments for more details on each of these parts. Once you are finished with this project, the keypoint matching part will be set up and you can proceed to the next lesson, where the focus is on integrating Lidar points and on object detection using deep-learning. 

## Dependencies for Running Locally
1. cmake >= 2.8
 * All OSes: [click here for installation instructions](https://cmake.org/install/)

2. make >= 4.1 (Linux, Mac), 3.81 (Windows)
 * Linux: make is installed by default on most Linux distros
 * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
 * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)

3. OpenCV >= 4.1
 * All OSes: refer to the [official instructions](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html)
 * This must be compiled from source using the `-D OPENCV_ENABLE_NONFREE=ON` cmake flag for testing the SIFT and SURF detectors. If using [homebrew](https://brew.sh/): `$> brew install --build-from-source opencv` will install required dependencies and compile opencv with the `opencv_contrib` module by default (no need to set `-DOPENCV_ENABLE_NONFREE=ON` manually). 
 * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)

4. gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using either [MinGW-w64](http://mingw-w64.org/doku.php/start) or [Microsoft's VCPKG, a C++ package manager](https://docs.microsoft.com/en-us/cpp/build/install-vcpkg?view=msvc-160&tabs=windows). VCPKG maintains its own binary distributions of OpenCV and many other packages. To see what packages are available, type `vcpkg search` at the command prompt. For example, once you've _VCPKG_ installed, you can install _OpenCV 4.1_ with the command:
```bash
c:\vcpkg> vcpkg install opencv4[nonfree,contrib]:x64-windows
```
Then, add *C:\vcpkg\installed\x64-windows\bin* and *C:\vcpkg\installed\x64-windows\debug\bin* to your user's _PATH_ variable. Also, set the _CMake Toolchain File_ to *c:\vcpkg\scripts\buildsystems\vcpkg.cmake*.


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./2D_feature_tracking`.
