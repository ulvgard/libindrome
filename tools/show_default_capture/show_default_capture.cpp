#include <opencv2/opencv.hpp>
#include <iostream>

/**
 * In essence a copy of a sample from OpenCV
 **/
int main()
{
    cv::VideoCapture cap;
    cap.open(0);

    if(!cap.isOpened())
    {
        std::cerr << "Could not open default camera" << std::endl;
        return -1;
    }

    std::cout << "Press 'q' to quit" << std::endl;

    cv::Mat frame;

    for(;;)
    {
        cap.read(frame);

        if(frame.empty())
        {
            std::cerr << "Captured frame is blank" << std::endl;
            break;
        }

        cv::imshow("Default capture", frame);

        if(cv::waitKey(5) == 'q')
            break;
    }

    return 0;
}
