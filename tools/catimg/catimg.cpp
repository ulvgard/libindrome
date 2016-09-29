#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <indrome/util.h>

void usage() 
{
    std::cout << "Usage: [IMAGE]" << std::endl;
}

int main(int argc, char* argv[]) 
{

    if(argc < 2)
    {
        usage();
        return -1;
    }

    for(int i = 1; i < argc; i++)
    {
        auto path = std::string(argv[i]);

        cv::Mat image = cv::imread(path, CV_LOAD_IMAGE_COLOR);

        if(!image.data )
        {
            std::cerr << "Could not read file " << path << std::endl;
            return -1;
        }

        std::cerr << path << " :: " << image.size() << std::endl;

        indrome::write_frame_to_stdout(image);
    }
    indrome::write_close_signal_to_stdout();

    fclose(stdout);
}
