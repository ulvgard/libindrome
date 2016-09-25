#include <indrome/util.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    for(;;) {
        cv::Mat frame = indrome::read_frame_from_stdin();
        cv::imshow("", frame);
        cv::waitKey(5);
        indrome::write_frame_to_stdout(frame);
    }

    return 0;
}
