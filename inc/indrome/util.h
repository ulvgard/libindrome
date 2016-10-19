#include <opencv2/core.hpp>


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

	/**
	 * Write one or more and OpenCV Matrices to file
	 *
	 * @param filename location to save the matrices to
	 * @param tags_and_mats vector of name-mat pairs
	 **/
	void write_mats_to_file(const std::string& filename, std::vector<std::pair<const std::string, const cv::Mat>>& tags_and_mats);

	/**
	 * Write and OpenCV Mat to file
	 *
	 * @param filename location to save the matrix to
	 * @param tag the matrix's key identifier
	 * @param frame a matrix to save to file
	 **/
	void write_mat_to_file(const std::string& filename, const std::string& tag, const cv::Mat& frame);

	/**
	 * Read one OpenCV Matrix from file
	 *
	 * @param filename location of the file to read from
	 * @param tag matrix key identifier
	 * @return Matrix read from file identified by tag
	 **/
	cv::Mat read_mats_from_file(const std::string& filename,
			const std::string& tags);

	/**
	 * Read one or more OpenCV Matrix from file
	 *
	 * @param filename location of the file to read from
	 * @param tags a vector of matrix key identifiers
	 * @return a vector of matrices read from file in the order their respective tag appear.
	 **/
	std::vector<cv::Mat> read_mats_from_file(const std::string& filename,
			const std::vector<std::string> tags);

}
