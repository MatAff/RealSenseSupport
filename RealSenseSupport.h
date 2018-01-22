#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

// External libraries
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

using namespace std;
using namespace cv;

// RealSenseSupport
class RealSenseSupport
{
public:
    RealSenseSupport();
    ~RealSenseSupport ();

    cv::Mat getColor();
    cv::Mat getIR();
    cv::Mat getDepth();

private:

    //Contruct a pipeline which abstracts the device
    rs2::pipeline pipe;

    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;

    // Frame set 
    rs2::frameset frames;
};
 


