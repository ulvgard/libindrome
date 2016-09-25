#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>

void usage() 
{
    std::cout << "Usage: [VIDEO_DEVICE_ID]" << std::endl;
    std::cout << "Sequentially output frames from captures" << std::endl;
}

int main(int argc, char* argv[]) 
{

    if(argc == 1)
    {
        usage();
        return -1;
    }

    std::vector<cv::VideoCapture> captures;

    for(int arg = 1; arg < argc; arg++)
    {
        cv::VideoCapture cap;
        int id = atoi(argv[arg]);

        cap.open(id);

        if(!cap.isOpened())
        {
            std::cerr << "Could not open default camera" << std::endl;
            return -1;
        }

        captures.push_back(cap);
    }

    cv::Mat frame;

    for(;;)
    {
        for(auto& cap: captures)
        {
            cap.read(frame);
            indrome::write_frame_to_stdout(frame);
        }
    }
}
