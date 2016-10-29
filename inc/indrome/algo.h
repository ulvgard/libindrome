#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

namespace indrome {
namespace algo {
cv::Mat compute_fundamental(
		std::vector<cv::Points2f> points_left, 
		std::vector<cv::Points2f> points_right);
}
}
