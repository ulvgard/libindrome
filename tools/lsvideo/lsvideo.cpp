#include <iostream>
#include <indrome/video.h>
#include <opencv2/videoio.hpp>

int main() 
{

    std::cout << "Listing found camera ids:" << std::endl; 
    for(auto id: indrome::get_video_device_id())
    {
        auto cap = cv::VideoCapture(id);
        auto width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        auto height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        auto fps = cap.get(cv::CAP_PROP_FPS);
        auto format = cap.get(cv::CAP_PROP_FORMAT);
        std::cout << "* id: " << id;
        if(width != -1 && height != -1) std::cout << " size: " << width 
            << "x" << height 
            << " fps: " << fps
            << " format: " << format
            << std::endl;
    }
    return 0;
}
