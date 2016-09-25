#include <opencv2/opencv.hpp>

namespace indrome 
{
    /**
     * Writes a frame as jpeg to stdout includign a header
     *
     * The format is: |size_0|size_1|size_2|size_3|byte|byte|byte...
     *
     * where the first 4 bytes represent the size of the frame 
     * as an unsigned integer. The consecutive bytes are the 
     * contents of the jpeg. This stream can be read by @ref read_frame_from_stdio.
     *
     * @param frame The OpenCV frame to print
     **/
    void write_frame_to_stdout(const cv::Mat& frame);

    /**
     * Reads a jpeg from stdin including a header
     *
     * The format is: |size_0|size_1|size_2|size_3|byte|byte|byte...
     *
     * where the first 4 bytes represent the size of the frame 
     * as an unsigned integer. The consecutive bytes are the 
     * contents of the jpeg. This stream can be read output form 
     * @ref write_frame_to_stdout.
     *
     * @return frame the read OpenCV frame; 
     **/
    cv::Mat read_frame_from_stdin();
}
