
#include <stdio.h>
#include <iostream>
 
// RealSense 
#include <librealsense2/rs.hpp>
#include "RealSenseSupport.h"

// OpenCV
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // Initialize RS Support
    RealSenseSupport rs;
    
    while(1)
    {
        //Get each frame
        cv::Mat frame = rs.getColor();

        // Display in a GUI
        namedWindow("Window", WINDOW_AUTOSIZE );
        imshow("Window", frame);
        cv::waitKey(5);
    }

    return 0;
}
