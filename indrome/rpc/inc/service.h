#pragma once
#include <utility>
#include <grpc++/grpc++.h>
#include <pose.pb.h>
#include <pose.grpc.pb.h>


namespace indrome
{
    namespace io
    {
        namespace rpc 
        {
            namespace pose
            {
                using grpc::ServerContext;
                using indrome_grpc::PoseUpdater;
                using indrome_grpc::Empty;
                using indrome_grpc::Pose;

                class PoseUpdaterService final : public PoseUpdater::Service 
                {
                    grpc::Status PoseUpdate(ServerContext*, const Pose*, Empty*) override;            
                };
            }
        }
    }
}
