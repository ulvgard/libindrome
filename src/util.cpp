#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

namespace indrome
{

    void write_frame_to_stdout(const cv::Mat& frame)
    {
        std::vector<unsigned char> raw_frame;

        raw_frame.resize(frame.total() * frame.elemSize());

        cv::imencode(".jpg", frame, raw_frame);

        // write the header
        unsigned char bytes[4];
        bytes[0] = (raw_frame.size() & 0xFF);
        bytes[1] = (raw_frame.size() >>  8 & 0xFF);
        bytes[2] = (raw_frame.size() >> 16 & 0xFF);
        bytes[3] = (raw_frame.size() >> 24 & 0xFF);

        std::cout << bytes[0]; 
        std::cout << bytes[1]; 
        std::cout << bytes[2]; 
        std::cout << bytes[3]; 

        // write the frame
        for(auto u: raw_frame)
            std::cout << u;
    }

    cv::Mat read_frame_from_stdin()
    {
        // read the header
        unsigned char bytes[4];
        bytes[0] = (unsigned char)fgetc(stdin);
        bytes[1] = (unsigned char)fgetc(stdin);
        bytes[2] = (unsigned char)fgetc(stdin);
        bytes[3] = (unsigned char)fgetc(stdin);

        unsigned int stream_size = 0;
        stream_size |= (bytes[3] << 24 & 0xFF000000);
        stream_size |= (bytes[2] << 16 & 0x00FF0000);
        stream_size |= (bytes[1] << 8  & 0x0000FF00);
        stream_size |= (bytes[0] & 0x000000FF);

        // read the frame
        std::vector<unsigned char> raw_frame(stream_size, 0);

        for(unsigned int bcount = 0; bcount < stream_size; bcount++)
            raw_frame[bcount] = (unsigned char)fgetc(stdin);

        return cv::imdecode(cv::Mat(raw_frame), CV_LOAD_IMAGE_COLOR);
    }
}
