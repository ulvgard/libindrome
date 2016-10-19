#include <indrome/util.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>



namespace indrome
{
    namespace 
    {
        /**
         * The header includes infromation required to read 
         * the serialized stream and to deserialize the object
         **/
        struct stream_header
        {
            int rows = 0;
            int cols = 0;
            int matrix_type = CV_8U;
            size_t stream_size = 0;
            bool closed = false;
        };

        /**
         * Create a stream header from an OpenCV Mat
         *
         * @param m any continuous OpenCV Mat
         * @return a header object for the Mat m
         **/
        stream_header create_header(const cv::Mat& m)
        {
            return stream_header {
                .rows = m.rows,
                .cols = m.cols,
                .matrix_type = m.type(),
                .stream_size = m.size().area()*m.elemSize(),
                .closed = false
            };
        }
    }

    void write_close_signal_to_stdout()
    {
        write_close_signal_to_fd(STDOUT_FILENO);
    }

    void write_close_signal_to_fd(int fd)
    {
        stream_header h; h.closed = true;
        write(fd, &h, sizeof(stream_header));
    }

    void write_frame_to_stdout(const cv::Mat& frame) 
    { 
        write_frame_to_fd(frame, STDOUT_FILENO); 
    }

    void write_frame_to_fd(const cv::Mat& frame, int fd)
    {
        if(!frame.isContinuous())
        {
            std::cerr << "Error writing frame: not continuous" << std::endl;
            exit(1);
        }

        // write the header
        stream_header h = create_header(frame);
        write(fd, &h, sizeof(h));

        // write the frame
        write(fd, frame.ptr(), h.stream_size);
    }

    cv::Mat read_frame_from_fd(int fd)
    {
        // read the header
        stream_header h;
        read(fd, &h, sizeof(stream_header));

        // check for the stop signal
        if(h.stream_size == 0)
            return cv::Mat();

        // read the frame
        cv::Mat frame = cv::Mat::zeros(h.rows, h.cols, h.matrix_type);
        read(fd, frame.ptr(), h.stream_size);

        return std::move(frame);
    }

    cv::Mat read_frame_from_stdin() 
    { 
        return std::move(read_frame_from_fd(STDIN_FILENO)); 
    }

	void write_mat_to_file(const std::string& filename, const std::string& tag, const cv::Mat& frame)
	{
		cv::FileStorage f(filename, cv::FileStorage::WRITE);

		if(!f.isOpened())
		{
			std::cerr << "Unable to write Mat to file " << filename << std::endl;
			return;
		}

		f << tag << frame;
		f.release();
	}

	void write_mats_to_file(const std::string& filename, std::vector<std::pair<const std::string, const cv::Mat>>& tags_and_mats)
	{
		cv::FileStorage f(filename, cv::FileStorage::WRITE);

		if(!f.isOpened())
		{
			std::cerr << "Unable to write Mat to file " << filename << std::endl;
			return;
		}

		for(const auto& p: tags_and_mats)
			f << p.first << p.second;

		f.release();
	}

	cv::Mat read_mat_from_file(const std::string& filename, const std::string& tag)
	{
		cv::FileStorage f(filename, cv::FileStorage::READ);

		if(!f.isOpened())
		{
			std::cerr << "Unable to write Mat to file " << filename << std::endl;
			return cv::Mat();
		}

		cv::Mat frame;
		f[tag] >> frame;
		f.release();

		return frame;
	}

	std::vector<cv::Mat> read_mats_from_file(
			const std::string& filename,
			const std::vector<std::string> tags)
	{
		cv::FileStorage f(filename, cv::FileStorage::READ);

		if(!f.isOpened())
		{
			std::cerr << "Unable to write Mat to file " << filename << std::endl;
			return cv::Mat();
		}

		std::vector<cv::Mat> mats;

		for(const auto& tag: tags)
		{
			cv::Mat frame;
			f[tag] >> frame;
			mats.push_back(frame);
		}
		f.release();

		return mats;
	}

}
