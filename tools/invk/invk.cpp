#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>
#include <string>
#include <fstream>

void usage() 
{
    std::cerr << "Usage: CALIBRATION_FILE" << std::endl;
    std::cerr << "Apply the inverted camera calibraiton matrix\n" << std::endl;
}

int main(int argc, char* argv[]) 
{
    if(argc != 2)
    {
		std::cerr << "Error using " << argv[0] << std::endl;
        usage();
        return -1;
    }

	std::vector<std::string> tags = {indrome::keywords::K, indrome::keywords::distCoeffs};

	auto mats = indrome::read_mats_from_file(
			std::string(argv[1]), tags);

	auto K = mats[0];
	auto distCoeffs = mats[1];

    for(;;)
    {
        cv::Mat view = indrome::read_frame_from_stdin();
        cv::Mat undistored = view.clone();

        if(view.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }

		undistort(view, undistored, K, distCoeffs);
        indrome::write_frame_to_stdout(undistored);
    }
    
    return 0;
}
