#include <gtest/gtest.h>
#include <indrome/algo.h>
#include <iostream>

TEST(Algo, compute_fundamental_planar)
{
	std::vector<cv::Vec3f> pr;
	std::vector<cv::Vec3f> pl;

	pr.push_back(cv::Vec3f(500,500,1));
	pr.push_back(cv::Vec3f(550,500,1));
	pr.push_back(cv::Vec3f(500,480,1));
	pr.push_back(cv::Vec3f(550,480,1));
	pr.push_back(cv::Vec3f(500,460,1));
	pr.push_back(cv::Vec3f(550,460,1));
	pr.push_back(cv::Vec3f(500,440,1));
	pr.push_back(cv::Vec3f(550,440,1));

	pl.push_back(cv::Vec3f(100,500,1));
	pl.push_back(cv::Vec3f(150,500,1));
	pl.push_back(cv::Vec3f(100,480,1));
	pl.push_back(cv::Vec3f(150,480,1));
	pl.push_back(cv::Vec3f(100,460,1));
	pl.push_back(cv::Vec3f(150,460,1));
	pl.push_back(cv::Vec3f(100,440,1));
	pl.push_back(cv::Vec3f(150,440,1));

	cv::Mat F = indrome::algo::compute_fundamental(pl, pr);
	cv::Mat xr(pr);
	cv::Mat xl(pl);

	cv::transpose(xr, xr);

	std::cerr << F << std::endl;

	double min, max;
	cv::minMaxLoc(xl*F*xr, &min, &max);
	EXPECT_FLOAT_EQ(min, 0.0);
	EXPECT_FLOAT_EQ(max, 0.0);

}
