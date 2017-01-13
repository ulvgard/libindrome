#include <iostream>
#include <memory>
#include <vector>
#include "../inc/client.h"

namespace indrome 
{
    namespace io
    {
        namespace rpc 
        {
            FrameBrokerClient NewFrameBrokerClient(const std::string& address) {
                return FrameBrokerClient(grpc::CreateChannel(
                    address, grpc::InsecureChannelCredentials()));
            }
            FrameBrokerClient::FrameBrokerClient(std::shared_ptr<grpc::Channel> channel) 
                : stub_(FrameBroker::NewStub(channel)) {}

            bool FrameBrokerClient::SendFrame() 
            {
                indrome_grpc::FrameRequest request; 
                indrome_grpc::FrameReply reply;
                grpc::ClientContext context;

                grpc::Status status = stub_->SendFrame(&context, request, &reply);

                if(status.ok())
                    return true;
                else 
                    return false;
            }

            namespace pose
            {
                PoseUpdaterClient NewPoseUpdaterClient(const std::string& address) 
                {
                    return PoseUpdaterClient(
                                grpc::CreateChannel(
                                    address, 
                                    grpc::InsecureChannelCredentials())
                           );
                }

                PoseUpdaterClient::PoseUpdaterClient(std::shared_ptr<grpc::Channel> channel) 
                : stub_(PoseUpdater::NewStub(channel)) {}

                namespace 
                {
                    void set_coeffs(indrome_grpc::Mat& mat, const std::vector<std::vector<float>>& vmat)
                    {
                        for(const auto& row: vmat)
                            for(const auto& v: row)
                                mat.add_coeffs(v);
                    }

                    indrome_grpc::Mat to_grpc_mat(const std::vector<std::vector<float>>& vmat)
                    {
                        indrome_grpc::Mat mat;
                        if(vmat.size() < 1)
                            return mat;

                        mat.set_rows(vmat.size());
                        mat.set_cols(vmat[0].size());
                        set_coeffs(mat, vmat);
                        return mat;
                    }
                }

                bool PoseUpdaterClient::PoseUpdate(
                        const std::vector<std::vector<float>>& R,
                        const std::vector<std::vector<float>>& t)
                {
                    indrome_grpc::Pose request;
                    indrome_grpc::Empty reply;
                    grpc::ClientContext context;

                    indrome_grpc::Mat* flat_r = new indrome_grpc::Mat(to_grpc_mat(R));
                    indrome_grpc::Mat* flat_t = new indrome_grpc::Mat(to_grpc_mat(t));
                    request.set_allocated_r(flat_r);
                    request.set_allocated_t(flat_t);

                    grpc::Status status = stub_->PoseUpdate(&context, request, &reply);
                    return status.ok();
                }
            }

        }
    }
}
