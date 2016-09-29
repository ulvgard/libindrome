#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>

int main(int, char* argv[]) 
{
    for(;;)
    {
        cv::Mat frame = indrome::read_frame_from_stdin();

        if(frame.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        indrome::write_frame_to_stdout(frame);
    }
}
