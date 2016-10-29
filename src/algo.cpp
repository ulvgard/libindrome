#include <indrome/algo.h>

namespace indrome {
namespace algo 
{
	cv::Mat compute_fundamental(
			std::vector<cv::Points2f> points_left, 
			std::vector<cv::Points2f> points_right)
	{
		return cv::findFundamentalMat(
				points_left,
				points_right,
				cv::CV_FM_8POINT)
	}
}
}
