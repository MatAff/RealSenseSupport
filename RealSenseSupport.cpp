
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
    cfg.enable_stream(RS2_STREAM_INFRARED, 640, 480, RS2_FORMAT_Y8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

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

cv::Mat RealSenseSupport::getIR()
{
    frames = pipe.wait_for_frames();
    rs2::frame ir_frame = frames.first(RS2_STREAM_INFRARED);
    
    // Creating OpenCV matrix from IR image
    cv::Mat ir(Size(640, 480), CV_8UC1, (void*)ir_frame.get_data(), Mat::AUTO_STEP);

    // Apply Histogram Equalization
    equalizeHist( ir, ir );
    applyColorMap(ir, ir, COLORMAP_JET);

    // Return ir image
    return ir;
}

cv::Mat RealSenseSupport::getDepth()
{
    frames = pipe.wait_for_frames();
    //rs2::frame ir_frame = frames.first(RS2_STREAM_DEPTH);
    rs2::frame depth = color_map(frames.get_depth_frame()); // Find and colorize the depth data
    
    // Creating OpenCV Matrix from a color image
    Mat color(Size(640, 480), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);

    // Return image
    return color;
}


