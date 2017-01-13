#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>
#include <indrome/rpc.h>
#include <iostream>
#include <fstream>

enum args 
{
	KFILE = 1,
	INNER_CORNER_WIDTH,
	INNER_CORNER_HEIGHT
};

void usage()
{
	std::cerr << "Usage: CALIBRATION_FILE INNER_CORNER_WIDTH INNER_CORNER_HEIGHT" << std::endl;
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
		std::cerr << "Error: wrong number of arguments\n" << std::endl;
		usage();
        return -1;
    }

	std::vector<std::string> tags = {indrome::keywords::K, indrome::keywords::distCoeffs};

	auto mats = indrome::read_mats_from_file(std::string(argv[args::KFILE]), tags);
	auto K = mats[0];
	auto distCoeffs = mats[1];

    const cv::Size board_size(
			atoi(argv[args::INNER_CORNER_WIDTH]),
			atoi(argv[args::INNER_CORNER_HEIGHT]));

    //auto frameBrokerClient = indrome::io::rpc::NewFrameBrokerClient();
    auto poseUpdaterClient = indrome::io::rpc::pose::NewPoseUpdaterClient("0.0.0.0:50100");

    for(;;)
    {
        cv::Mat view = indrome::read_frame_from_stdin();

        if(view.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }

        std::vector<cv::Vec2f> points;
        bool found = findChessboardCorners( view, board_size, points, cv::CALIB_CB_ADAPTIVE_THRESH);
        
        if(found)
        {
			cv::Mat grey = view.clone();
            cv::cvtColor(view, grey, cv::COLOR_BGR2GRAY);

			std::vector<cv::Vec3f> object_points;
			std::vector<cv::Vec2f> image_points;

            // Increase detection accuracy
            cv::cornerSubPix(
                    grey, 
                    points, 
                    cv::Size(11,11), 
                    cv::Size(-1,-1),  
                    cv::TermCriteria(
                    cv::TermCriteria::COUNT|cv::TermCriteria::EPS, 30, 0.01));

            // Add image points 
			for(const auto& p: points)
				image_points.push_back(p);

            // Add object points
            std::vector<cv::Vec3f> board_points; 
            for(int i = 0; i < board_size.height; ++i)
                 for(int j = 0; j < board_size.width; ++j)
                     object_points.push_back(cv::Vec3f(j, i, 0));

            cv::Mat rvec;
            cv::Mat tvec;
			cv::solvePnPRansac(object_points,
								image_points,
								K,
								distCoeffs,
								rvec,
								tvec);

			cv::Mat axis = (cv::Mat_<float>(3,3) << 3,0,0,0,3,0,0,0,-3);

			cv::Mat view_axis;
			cv::projectPoints(axis, rvec, tvec, K, distCoeffs, view_axis);

			const std::vector<cv::Scalar> colors = {cv::Scalar(255,0,0), cv::Scalar(0,255,0), cv::Scalar(0,0,255)};
			for(const auto& i: {0,1,2})
			{
				cv::line(view, 
						cv::Point(points[0]), 
						cv::Point(view_axis.at<float>(i,0), view_axis.at<float>(i,1)), 
						colors[i], 
						5);
			}

            cv::Mat R33; Rodrigues(rvec, R33);
            cv::Mat H;
            hconcat(R33, tvec, H);
            cv::Mat r4 = cv::Mat::zeros(1,4,CV_64F);
            cv::Mat V;
            vconcat(H, r4, V);
            V.at<double>(3,3) = 1.0;
            auto Vinv = V.inv();
            std::cerr << Vinv << std::endl;


            auto R = indrome::to_vec2d(rvec);
            auto t = indrome::to_vec2d(Vinv.col(3));
            poseUpdaterClient.PoseUpdate(R, t);
        }
        else
        {
            std::cerr << argv[0] << ": " << "Could not find chessboard" << std::endl;
        }

        indrome::write_frame_to_stdout(view);
    }
    
    return 0;
}
