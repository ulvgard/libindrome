#pragma once
#include <iostream>
#include <memory>
#include <grpc++/grpc++.h>
#include <frame.pb.h>
#include <frame.grpc.pb.h>
#include <pose.pb.h>
#include <pose.grpc.pb.h>

using indrome_grpc::FrameBroker;
using indrome_grpc::PoseUpdater;

namespace indrome 
{
    namespace io
    {
        namespace rpc 
        {

            class FrameBrokerClient 
            {
                public:
                    FrameBrokerClient(std::shared_ptr<grpc::Channel> channel);
                    bool SendFrame();

                private:
                    std::unique_ptr<FrameBroker::Stub> stub_;
            };
            FrameBrokerClient NewFrameBrokerClient(const std::string& address="0.0.0.0:50100");
            indrome_grpc::Mat to_grpc_mat(const std::vector<std::vector<float>>& vec);

            namespace pose 
            {
                class PoseUpdaterClient
                {
                    public:
                        PoseUpdaterClient(std::shared_ptr<grpc::Channel> channel);
                        bool PoseUpdate(
                            const std::vector<std::vector<float>>& R,
                            const std::vector<std::vector<float>>& t);
                    private:
                        std::unique_ptr<PoseUpdater::Stub> stub_;
                };
                
                PoseUpdaterClient NewPoseUpdaterClient(const std::string& address="0.0.0.0:50100");
            }
        }
    }
}
