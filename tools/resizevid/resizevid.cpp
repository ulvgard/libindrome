#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>

void usage() 
{
    std::cout << "Usage: WIDTH HEIGHT" << std::endl;
    std::cout << "Resize frame from stdin to WIDTHxHEIGHT and output on stdout" << std::endl;
}

int main(int argc, char* argv[]) 
{

    if(argc != 3)
    {
        usage();
        return -1;
    }

    auto width = atoi(argv[1]);
    auto height = atoi(argv[2]);

    for(;;)
    {
        cv::Mat frame = indrome::read_frame_from_stdin();

        if(frame.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }

        cv::resize(frame, frame, cv::Size(width,height));
        indrome::write_frame_to_stdout(frame);
    }
}
