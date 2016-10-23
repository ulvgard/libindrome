#include <opencv2/opencv.hpp>
#include <iostream>
#include <indrome/util.h>
#include <iostream>
#include <fstream>

void usage() 
{
    std::cerr << "Usage: WIDTH_INNER_CORNERS HEIGHT_INNER_CORNERS [OUTPUT_FILE_NAME].txt" << std::endl;
    std::cerr << "Sequentially output frames from captures" << std::endl;
}

int main(int argc, char* argv[]) 
{
    if(argc < 3)
    {
        usage();
        return -1;
    }

    const cv::Size board_size(atoi(argv[1]), atoi(argv[2])); 

	auto output_to_file = false;
	auto output_file_name = "";

	if(argc >= 4)
	{
		output_file_name = argv[3];
		output_to_file = true;
	}


    // object points
    std::vector<std::vector<cv::Vec3f>> object_points;
    std::vector<std::vector<cv::Vec2f>> image_points;

	cv::Mat optimalCameraMatrix;
	cv::Mat distCoeffs = cv::Mat::zeros(8, 1, CV_64F);

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

        
        cv::Mat undistored = view.clone();
        if(found)
        {
            cv::cvtColor(view, view, cv::COLOR_BGR2GRAY);
            // Increase detection accuracy
            cv::cornerSubPix(
                    view, 
                    points, 
                    cv::Size(11,11), 
                    cv::Size(-1,-1),  
                    cv::TermCriteria(
                    cv::TermCriteria::COUNT|cv::TermCriteria::EPS, 30, 0.01));

            // Add image points 
            image_points.push_back(points);

            // Add object points
            std::vector<cv::Vec3f> board_points; 
            for(int i = 0; i < board_size.height; ++i)
                 for(int j = 0; j < board_size.width; ++j)
                     board_points.push_back(cv::Vec3f(j, i, 0));

            object_points.push_back(board_points);

            drawChessboardCorners(view, board_size, cv::Mat(points), found);

            std::vector<cv::Mat> rvecs;
            std::vector<cv::Mat> tvecs;
            cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);

            const auto rms = calibrateCamera(
                    object_points, 
                    image_points, 
                    view.size(), 
                    cameraMatrix,
                    distCoeffs, 
                    rvecs, 
                    tvecs, 
                    CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);

            std::cerr << "RMS: " << rms << std::endl;
            std::cerr << "Camera matrix:\n" << cameraMatrix << std::endl;
            std::cerr << "Distortion matrix:\n" << distCoeffs << std::endl;

            const auto alpha = 0;
            optimalCameraMatrix = cv::getOptimalNewCameraMatrix(
                    cameraMatrix,
                    distCoeffs,
                    view.size(),
                    alpha);

            undistort(view, undistored, optimalCameraMatrix, distCoeffs);
        }
        else
        {
            std::cerr << argv[0] << ": " << "Could not find chessboard" << std::endl;
        }


        indrome::write_frame_to_stdout(undistored);
    }

	if(output_to_file)
	{
		auto kpair = std::make_pair(indrome::keywords::K, optimalCameraMatrix);
		auto dpair = std::make_pair(indrome::keywords::distCoeffs, distCoeffs);

		std::vector<std::pair<const std::string, const cv::Mat> > pairs = {kpair, dpair};

		indrome::write_mats_to_file(output_file_name, pairs);
	}
    
    return 0;
}
