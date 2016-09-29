#include <indrome/util.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>

int main(int, char* argv[])
{
    cv::Mat frame = indrome::read_frame_from_stdin();

    if(frame.empty())
    {
        std::cerr << std::string(argv[0]) + ": error reading image from stdin" << std::endl;
        return -1;
    }

    std::cerr << argv[0] << ": Press q to quit" << std::endl;

    cv::imshow("", frame);
    while(cv::waitKey(100) != 113)  // 'q'
    {}
    indrome::write_frame_to_stdout(frame);

    return 0;
}
