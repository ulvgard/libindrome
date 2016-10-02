#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>

void usage() 
{
    std::cout << "Usage: [VIDEO_DEVICE_ID]" << std::endl;
    std::cout << "Sequentially output frames from captures" << std::endl;
}

static bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
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

        if(is_number(argv[arg]))
        {
            int id = atoi(argv[arg]);
            cap.open(id);
        }
        else
        {
            cap.open(argv[arg]);
        }

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
