#include <opencv2/opencv.hpp>


namespace indrome 
{
    /**
     * Signal to close the stream on a file descriptor
     *
     * @param fd a file descriptior of the stream
     **/
    void write_close_signal_to_fd(int fd);

    /**
     * Signal to close the stream on stdout
     **/
    void write_close_signal_to_stdout();

    /**
     * Write an continous OpenCV Mat to a file descriptor
     *
     * @param frame a continous OpenCV Mat write 
     * @param fd file descriptor to write to
     **/
    void write_frame_to_fd(const cv::Mat& frame, int fd);

    /**
     * Write an continous OpenCV Mat to stdout 
     *
     * @param frame a continous OpenCV Mat write 
     **/
    void write_frame_to_stdout(const cv::Mat& frame);

    /**
     * Read an OpenCV Mat from a file descriptor
     *
     * @param fd file desrriptor to read from
     * @return a OpenCV Mat read from a file descriptor
     **/
    cv::Mat read_frame_from_fd(int fd);

    /**
     * Read an OpenCV Mat from stdin 
     *
     * @return a OpenCV Mat read from a stdin 
     **/
    cv::Mat read_frame_from_stdin();
}
