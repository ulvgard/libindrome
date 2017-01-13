#include "../inc/indrome/pose/simple_velocity.h" 
namespace indrome
{
    namespace pose 
    {
        void SimpleVelocityModel::add_measurment(const std::array<float, 3>& new_position)
        {
            using ms = std::chrono::milliseconds;
            auto now = std::chrono::steady_clock::now();
            auto dt = std::chrono::duration_cast<ms>(now - get_timestamp());

            auto status_now = get_status();

            if(status_now == INVALID) {
                set_position(new_position);
                set_timestamp(now);
                transcend(VALID);
            }
            else if(status_now == VALID) {

                if(dt > measurement_deadline) 
                    transcend(INVALID);

                set_position(new_position);
                set_timestamp(now);
            }
        }

        std::array<float, 3> SimpleVelocityModel::get_position()
        {
            pos_guard.lock();
            auto pos = position;
            pos_guard.unlock();
            return pos;
        }

        ModelStatus SimpleVelocityModel::get_status()
        {
            status_guard.lock();
            auto status_now = status;
            status_guard.unlock();
            return status_now;
        }

        void SimpleVelocityModel::set_timestamp(std::chrono::steady_clock::time_point tp)
        {
            time_guard.lock();
            timestamp = tp;
            time_guard.unlock();
        }
        
        std::chrono::steady_clock::time_point SimpleVelocityModel::get_timestamp()
        {
            time_guard.lock();
            auto current_ts = timestamp;
            time_guard.unlock();
            return current_ts;
        }

        void SimpleVelocityModel::set_position(std::array<float, 3> new_position)
        {
            pos_guard.lock();
            position = new_position;
            pos_guard.unlock();
        }

        void SimpleVelocityModel::transcend(ModelStatus new_status)
        {
            status_guard.lock();
            status = new_status;
            status_guard.unlock();
        }
    }
}
