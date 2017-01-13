#pragma once
#include <array>
#include <chrono>
#include <mutex>

namespace indrome
{
    namespace pose
    {
        enum ModelStatus { INVALID, VALID};
        /**
         * A pose model for frame-to-frame pose estimation.
         * The model implements a decaying velocity model.
         **/
        class SimpleVelocityModel 
        {
            public:


                void add_measurment(const std::array<float, 3>& new_position);

                /**
                 * Lock and get a copy of the position
                 **/
                std::array<float, 3> get_position();

                /**
                 * Lock and get the state of the model.
                 **/
                ModelStatus get_status();

            private:

                ModelStatus status = INVALID;
                std::chrono::milliseconds measurement_deadline{200};
                std::mutex pos_guard, status_guard, time_guard;
                std::chrono::steady_clock::time_point timestamp;
                std::array<float, 3> position;
                std::array<float, 3> velocity;

                /**
                 * Lock and set the timestamp 
                 **/
                void set_timestamp(std::chrono::steady_clock::time_point tp);
                
                /**
                 * Lock and get the timestamp
                 **/
                std::chrono::steady_clock::time_point get_timestamp();

                /**
                 * Lock and set the position
                 **/
                void set_position(std::array<float, 3> new_position);

                /**
                 * Lock and set the state of the model.
                 **/
                void transcend(ModelStatus new_status);
        };

    }
}
