#include <opencv2/opencv.hpp>
#include <vector>

namespace indrome {
namespace algo {
cv::Mat compute_fundamental(const std::vector<cv::Vec3f> points_left,
                            const std::vector<cv::Vec3f> points_right);
cv::Mat compute_fundamental(const std::vector<cv::Vec2f> points_left,
                            const std::vector<cv::Vec2f> points_right);
}
}
