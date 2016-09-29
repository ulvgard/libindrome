#include <indrome/util.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <string>

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

        std::cerr << argv[0] << ": Press q to quit" << std::endl;

        cv::imshow("", frame);
        while(cv::waitKey(100) != 113)  // 'q'
        {}
        indrome::write_frame_to_stdout(frame);
    }

    return 0;
}
