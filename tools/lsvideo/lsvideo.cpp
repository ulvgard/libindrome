#include <iostream>
#include <indrome/video.h>

int main() 
{

    std::cout << "Listing found camera ids:" << std::endl; 
    for(auto id: indrome::get_video_device_id())
        std::cout << "id: " << id << std::endl;
    return 0;
}
