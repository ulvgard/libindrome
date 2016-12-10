#include <indrome/algo.h>

namespace indrome {
namespace algo 
{
	cv::Mat compute_fundamental(
			const std::vector<cv::Vec3f> points_left,
			const std::vector<cv::Vec3f> points_right)
	{
		std::vector<cv::Vec2f> pl;
		std::vector<cv::Vec2f> pr;

		for(const auto& p: points_left)
			pl.push_back(cv::Vec2f(p(0), p(1)));

		for(const auto& p: points_right)
			pr.push_back(cv::Vec2f(p(0), p(1)));

		return compute_fundamental(pl, pr);
	}

	cv::Mat compute_fundamental(
			const std::vector<cv::Vec2f> points_left,
			const std::vector<cv::Vec2f> points_right)
	{
		return cv::findFundamentalMat(
				points_left,
				points_right,
				CV_FM_8POINT);
	}
}
}
