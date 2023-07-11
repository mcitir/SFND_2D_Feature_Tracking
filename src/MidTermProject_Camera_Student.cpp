// unset GTK_PATH
/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

//using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{
    // Opencv version check
    std::cout << "OpenCV version : " << CV_VERSION << std::endl;
    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    std::string dataPath = "../";

    // camera
    std::string imgBasePath = dataPath + "images/";
    std::string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    std::string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    std::vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = false;            // visualize results

    /* MAIN LOOP OVER ALL IMAGES */

        double totalKeypoints = 0.0; // Variable to store the total number of keypoints in all frame
        double roiKeypoints = 0.0; // Variable to store the total number of keypoints in ROI
        double totalDescriptorTime = 0.0; // Variable to store the total time for descriptor extraction

        double totalDetectionTime = 0.0; // Variable to store the total time for detection
        double totalMatcherTime = 0.0; // Variable to store the total time for matching



    for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
    {
        /* LOAD IMAGE INTO BUFFER */

        // assemble filenames for current index
        std::ostringstream imgNumber;
        imgNumber << std::setfill('0') << std::setw(imgFillWidth) << imgStartIndex + imgIndex;
        std::string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

        // load image from file and convert to grayscale
        cv::Mat img, imgGray;
        img = cv::imread(imgFullFilename);
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        //// STUDENT ASSIGNMENT
        //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

        // push image into data frame buffer
        DataFrame frame;
        frame.cameraImg = imgGray;
        dataBuffer.push_back(frame);
        
        // appy ring buffer based on predefined dataBufferSize 
        if (dataBuffer.size() > dataBufferSize)
        {
            dataBuffer.erase(dataBuffer.begin());
        }

        // print out the size of dataBuffer allocated
        std::cout << "dataBuffer.size() = " << dataBuffer.size() << std::endl; 

        //// EOF STUDENT ASSIGNMENT
        std::cout << "#1 : LOAD IMAGE INTO BUFFER done" << std::endl;

        /* DETECT IMAGE KEYPOINTS */

        // extract 2D keypoints from current image
        std::vector<cv::KeyPoint> keypoints; // create empty feature list for current image

        // The detectorType selection
        std::string detectorType = "SHITOMASI";
        //std::string detectorType = "HARRIS";
        //std::string detectorType = "FAST";
        //std::string detectorType = "BRISK";
        //std::string detectorType = "ORB";
        //std::string detectorType = "AKAZE";
        //std::string detectorType = "SIFT";

        //// STUDENT ASSIGNMENT
        //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
        //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
        double detectionTime = 0.0; // Declaration of variable to store the detection time
        if (detectorType.compare("SHITOMASI") == 0)
        {
            detKeypointsShiTomasi(keypoints, imgGray, bVis, detectionTime);   
        }
        else if (detectorType.compare("HARRIS") == 0)
        {
            detKeypointsHarris(keypoints, imgGray, bVis, detectionTime);
        }
        else if (detectorType.compare("FAST") == 0 || detectorType.compare("BRISK") == 0 || 
                 detectorType.compare("ORB") == 0 || detectorType.compare("AKAZE") == 0 || 
                 detectorType.compare("SIFT") == 0)
        {
            detKeypointsModern(keypoints, imgGray, detectorType, bVis, detectionTime);
        }
        else
        {
            throw std::invalid_argument("Please select a valid detectorType, "+detectorType+" is not valid");
        }

        totalDetectionTime += detectionTime; // Accumulate the total detection time for all frames
        

        //// EOF STUDENT ASSIGNMENT

        //// STUDENT ASSIGNMENT
        //// TASK MP.3 -> only keep keypoints on the preceding vehicle

        // only keep keypoints on the preceding vehicle
        bool bFocusOnVehicle = true;
        cv::Rect vehicleRect(535, 180, 180, 150);
        if (bFocusOnVehicle)
        {
            std::cout << "For all frame = " << keypoints.size() << std::endl;
            double numKeypoints = keypoints.size();
            totalKeypoints += numKeypoints;

            for (auto it = keypoints.begin(); it != keypoints.end();)
            {
                if (!vehicleRect.contains(it->pt))
                {
                    it = keypoints.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            std::cout << "For ROI = " << keypoints.size() << std::endl;
            double numKeypointsROI = keypoints.size();
            roiKeypoints += numKeypointsROI;
        }

        //// EOF STUDENT ASSIGNMENT

        // optional : limit number of keypoints (helpful for debugging and learning)
        bool bLimitKpts = false;
        if (bLimitKpts)
        {
            int maxKeypoints = 50;

            if (detectorType.compare("SHITOMASI") == 0)
            { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
            }
            cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
            std::cout << " NOTE: Keypoints have been limited!" << std::endl;
        }

        // push keypoints and descriptor for current frame to end of data buffer
        (dataBuffer.end() - 1)->keypoints = keypoints;
        std::cout << "#2 : DETECT KEYPOINTS done" << std::endl;

        /* EXTRACT KEYPOINT DESCRIPTORS */

        //// STUDENT ASSIGNMENT
        //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
        //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

        cv::Mat descriptors;
        double descriptorTime = 0.0; // Declare a variable to store the descriptor extraction time

        // BRISK, BRIEF, ORB, FREAK, AKAZE, SIFT
        std::string descriptorType = "BRISK";
        //std::string descriptorType = "BRIEF"; 
        //std::string descriptorType = "ORB";
        //std::string descriptorType = "FREAK";
        //std::string descriptorType = "AKAZE";
        //std::string descriptorType = "SIFT";
        descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType, descriptorTime);
        totalDescriptorTime += descriptorTime;
        //// EOF STUDENT ASSIGNMENT

        // push descriptors for current frame to end of data buffer
        (dataBuffer.end() - 1)->descriptors = descriptors;

        std::cout << "#3 : EXTRACT DESCRIPTORS done" << std::endl;

        if (dataBuffer.size() > 1) // wait until at least two images have been processed
        {

            /* MATCH KEYPOINT DESCRIPTORS */

            std::vector<cv::DMatch> matches;
            std::string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
            std::string descriptorType = "DES_BINARY"; // DES_BINARY, DES_HOG
            std::string selectorType = "SEL_NN";       // SEL_NN, SEL_KNN

            //// STUDENT ASSIGNMENT
            //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
            //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

            double matcherTime = 0.0; // Declare a variable to store the matcher time   

            matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                             (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                             matches, descriptorType, matcherType, selectorType, matcherTime);

            totalMatcherTime += matcherTime; // Accumulate the total matcher time for all frames

            //// EOF STUDENT ASSIGNMENT

            // store matches in current data frame
            (dataBuffer.end() - 1)->kptMatches = matches;

            std::cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << std::endl;

            // visualize matches between current and previous image
            bVis = true;
            if (bVis)
            {
                cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                matches, matchImg,
                                cv::Scalar::all(-1), cv::Scalar::all(-1),
                                std::vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                std::string windowName = "Matching keypoints between two camera images";
                cv::namedWindow(windowName, 7);
                cv::imshow(windowName, matchImg);
                std::cout << "Press key to continue to next image" << std::endl;
                //cv::waitKey(0); // wait for key to be pressed
            }
            bVis = false;
        }

    } // eof loop over all images


    // Calculate the average number of keypoints
    std::cout << "Total number of keypoints: " << totalKeypoints << std::endl;
    std::cout << "Total number of keypoints in ROI: " << roiKeypoints << std::endl;
    double avgKeypoints = totalKeypoints / (imgEndIndex - imgStartIndex + 1);
    std::cout << "Average number of keypoints: " << avgKeypoints << std::endl;
    double avgKeypointsROI = roiKeypoints / (imgEndIndex - imgStartIndex + 1);
    std::cout << "Average number of keypoints in ROI: " << avgKeypointsROI << std::endl;

    // Calculate the average detection time
    std::cout << "Total detection time: " << totalDetectionTime << std::endl;
    double avgDetectionTime = totalDetectionTime / (imgEndIndex - imgStartIndex + 1);
    std::cout << "Average detection time: " << avgDetectionTime << std::endl;

    // Calculate the average descriptor extraction time
    std::cout << "Total descriptor extraction time: " << totalDescriptorTime << std::endl;
    double avgDescriptorTime = totalDescriptorTime / (imgEndIndex - imgStartIndex + 1);
    std::cout << "Average descriptor extraction time: " << avgDescriptorTime << std::endl;

    // Calculate total time
    double totalTime = totalDetectionTime + totalDescriptorTime;
    std::cout << "Total time: " << totalTime << std::endl;
    double avgTime = totalTime / (imgEndIndex - imgStartIndex + 1);
    std::cout << "Average time: " << avgTime << std::endl;   

    // Calculate the average matcher time
    std::cout << "Total matcher time: " << totalMatcherTime << std::endl;
    double avgMatcherTime = totalMatcherTime / (imgEndIndex - imgStartIndex + 1);
    std::cout << "Average matcher time: " << avgMatcherTime << std::endl;

    std::cout << "...." << std::endl;
    std::cout << "Average number of keypoints in ROI: " << avgKeypointsROI << std::endl;
    std::cout << "Average number of keypoints: " << avgKeypoints << std::endl;
    std::cout << "Average time: " << avgTime << std::endl; 

    return 0;
}