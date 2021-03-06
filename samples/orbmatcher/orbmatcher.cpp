#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <indrome/util.h>
#include <indrome/algo.h>

int main(int , char* argv[])
{

	cv::Mat ref_keyframe;
	cv::Mat ref_descriptors;
	std::vector<cv::KeyPoint> ref_keypoints;

	cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();

    for(;;)
    {
        cv::Mat view = indrome::read_frame_from_stdin();

        if(view.empty())
        {
            std::cerr << argv[0] << ": received close signal" << std::endl;
            indrome::write_close_signal_to_stdout();
            break;
        }
	
		if(ref_keypoints.empty() || ref_descriptors.empty())
		{
			detector->detectAndCompute(view, cv::noArray(), ref_keypoints, ref_descriptors);
			ref_keyframe = view.clone();
			continue;
		}

		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;

		detector->detectAndCompute(view, cv::noArray(), keypoints, descriptors, false);

		std::vector< std::vector<cv::DMatch> > matches;
		cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");
		matcher->knnMatch( ref_descriptors, descriptors, matches, 500 );

		double tresholdDist = 0.25 * sqrt(double(ref_keyframe.size().height*ref_keyframe.size().height + ref_keyframe.size().width*ref_keyframe.size().width));

		std::vector< cv::DMatch > good_matches2;
		good_matches2.reserve(matches.size());  

		std::vector<cv::Vec2f> pl, pr;

		for (int i = 0; i < (int)matches.size(); ++i)
		{ 

			for (int j = 0; j < (int)matches[i].size(); j++)
			{
				cv::Point2f from = ref_keypoints[matches[i][j].queryIdx].pt;
				cv::Point2f to = keypoints[matches[i][j].trainIdx].pt;
		
				double dist = sqrt((from.x - to.x) * (from.x - to.x) + (from.y - to.y) * (from.y - to.y));

				if (dist < tresholdDist && fabs(from.y-to.y)<5)
				{
					good_matches2.push_back(matches[i][j]);
					j = matches[i].size();

					if(pr.size() != 8)
					{
						pr.push_back(cv::Vec2f(from.x, from.y));
					}

					if(pl.size() != 8)
					{
						pl.push_back(cv::Vec2f(to.x, to.y));
					}
				}
			}
		}

		cv::Mat matchview;
		cv::drawMatches(ref_keyframe
				, ref_keypoints
				, view
				, keypoints
				, good_matches2
				, matchview);
        indrome::write_frame_to_stdout(matchview);
    }
    
    return 0;
}
