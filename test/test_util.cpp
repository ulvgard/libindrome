#include <gtest/gtest.h>
#include <indrome/util.h>
#include <fcntl.h>

TEST(Util, stream_single_frame)
{
    cv::Mat I = cv::Mat::eye(2,2, CV_8U);

    int pipen[2]; pipe(pipen);

    indrome::write_frame_to_fd(I, pipen[1]);
    indrome::write_close_signal_to_fd(pipen[1]);

    cv::Mat data = indrome::read_frame_from_fd(pipen[0]);

    ASSERT_TRUE(!data.empty());
    ASSERT_TRUE(data.type() == CV_8U);
    ASSERT_EQ(data.size().width, 2);
    ASSERT_EQ(data.size().height, 2);

    cv::Mat no_data = indrome::read_frame_from_fd(pipen[0]);
    ASSERT_TRUE(no_data.empty());
}

TEST(Util, stream_multiple_frames)
{
    const int num_frames = 3;
    cv::Mat I = cv::Mat::eye(2,2, CV_8U);

    int pipen[2]; pipe(pipen);

    for(int i = 0; i < num_frames; i++)
        indrome::write_frame_to_fd(I, pipen[1]);
    indrome::write_close_signal_to_fd(pipen[1]);

    for(int i = 0; i < num_frames; i++)
    {
        cv::Mat data = indrome::read_frame_from_fd(pipen[0]);

        ASSERT_TRUE(!data.empty());
        ASSERT_TRUE(data.type() == CV_8U);
        ASSERT_EQ(data.size().width, 2);
        ASSERT_EQ(data.size().height, 2);
    }

    cv::Mat no_data = indrome::read_frame_from_fd(pipen[0]);
    ASSERT_TRUE(no_data.empty());
}

TEST(Util, stream_different_frame_types)
{
    int pipen[2]; pipe(pipen);

    cv::Mat I = cv::Mat::eye(2,2, CV_8UC3);
    indrome::write_frame_to_fd(I, pipen[1]);

    cv::Mat data = indrome::read_frame_from_fd(pipen[0]);
    ASSERT_TRUE(!data.empty());
    ASSERT_TRUE(data.type() == CV_8UC3);
    ASSERT_EQ(data.size().width, 2);
    ASSERT_EQ(data.size().height, 2);
}
