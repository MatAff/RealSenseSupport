
#include "RealSenseSupport.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

// External libraries
#include <opencv2/opencv.hpp>

// Constructor
RealSenseSupport::RealSenseSupport()
{
    //Add desired streams to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    //Instruct pipeline to start streaming with the requested configuration
    pipe.start(cfg);

    // Camera warmup - dropping several first frames to let auto-exposure stabilize
    for(int i = 0; i < 30; i++)
    {
        //Wait for all configured streams to produce a frame
        frames = pipe.wait_for_frames();
    }

}

// Destructor
RealSenseSupport::~RealSenseSupport()
{
}


cv::Mat RealSenseSupport::getColor()
{
    frames = pipe.wait_for_frames();
    rs2::frame color_frame = frames.get_color_frame();

    // Creating OpenCV Matrix from a color image
    Mat color(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

    // Return color image
    return color;
}

