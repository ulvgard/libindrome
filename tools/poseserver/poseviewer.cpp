void open_window(indrome::pose::SimpleVelocityModel& posemodel)
{
    using namespace cv;

    viz::Viz3d pose_window("Pose estimation");

    pose_window.showWidget("axis widget", viz::WCoordinateSystem());

    Point3d cam_focal_point(2.0f,2.0f,2.0f), cam_y_dir(-1.0f,0.0f,0.0f);

    Mat rot_vec = Mat::zeros(1,3,CV_32F);
    Mat rot_mat;

    while(!pose_window.wasStopped())
    {

        if(posemodel.get_status() == indrome::pose::VALID)
        {
            rot_vec.at<float>(0,0) += CV_PI * 0.00f;
            rot_vec.at<float>(0,1) += CV_PI * 0.00f;
            rot_vec.at<float>(0,2) += CV_PI * 0.00f;
            auto pos = posemodel.get_position();
            auto cam_pos = Point3d((double)pos[0], (double)pos[1], (double)pos[2]);
            auto cam_pose = viz::makeCameraPose(cam_pos, cam_focal_point, cam_y_dir);
            viz::WCameraPosition cpw(0.5); // Coordinate axes
            viz::WCameraPosition cpw_frustum(Vec2f(0.889484, 0.523599)); // Camera frustum
            pose_window.showWidget("CPW", cpw, cam_pose);
            pose_window.showWidget("CPW_FRUSTUM", cpw_frustum, cam_pose);

            Rodrigues(rot_vec, rot_mat);
            Affine3f pose(rot_mat, Vec3f(0.0, 0.0, 0.0));
            pose_window.setWidgetPose("axis widget", pose);
        }

        pose_window.spinOnce(1, true);
    }
}
