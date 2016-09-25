#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>

int main() 
{
    for(;;)
    {
        cv::Mat frame = indrome::read_frame_from_stdin();
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        indrome::write_frame_to_stdout(frame);
    }
}
