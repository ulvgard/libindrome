#include <indrome/util.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    for(;;) {

        cv::Mat view = indrome::read_frame_from_stdin();

        if(view.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }

        cv::imshow(window_name, view);
        cv::waitKey(5);
        indrome::write_frame_to_stdout(view);
    }

    return 0;
}
