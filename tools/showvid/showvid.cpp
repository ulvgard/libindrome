#include <indrome/util.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

void usage()
{
	std::cerr << "Usage: [FRAME_DELAY]" << std::endl;
}

int main(int argc, char* argv[])
{
	int delay = 5;

	if(argc > 2)
	{
		std::cerr << "Error: invalid arguments\n" << std::endl;
		usage();
		return -1;
	}

	if(argc == 2)
		delay = atoi(argv[1]);

    for(;;) {

        cv::Mat view = indrome::read_frame_from_stdin();

        if(view.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }

        cv::imshow("", view);
        cv::waitKey(delay);
        indrome::write_frame_to_stdout(view);
    }

    return 0;
}
