#include <indrome/video.h>

#include <fcntl.h>
#include <string>

namespace indrome
{
    std::vector<int> get_video_device_id()
    {
        std::vector<int> found_cameras;
#ifdef _WIN32
        // TODO: exception
#elif __linux__
        int fd;
        int cam_id = 0;
        while(fd = open((std::string("/dev/video") + std::to_string(cam_id)).c_str(), O_RDONLY) != -1)
            found_cameras.push_back(cam_id++);

        return found_cameras; 
#endif
    }
}
