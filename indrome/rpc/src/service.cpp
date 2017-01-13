#include "../inc/service.h"

namespace indrome
{
    namespace io
    {
        namespace rpc 
        {
            namespace pose
            {
                namespace 
                {
                    /**
                     * Remove this when properly implemented message handling is done
                     **/
                    void print(const indrome_grpc::Mat& m)
                    {
                        for(auto i = 0; i < m.rows(); i++)
                        {
                            for(auto j = 0; j < m.cols(); j++)
                                printf("%5.3f ", m.coeffs(i*m.cols() +j));
                            std::cout << "\n";
                        }
                    }
                }
                grpc::Status PoseUpdaterService::PoseUpdate(
                    ServerContext* context,
                    const Pose* request,
                    Empty* null_reply)
                {
                    print(request->r());
                    print(request->t());
                    return grpc::Status::OK;
                }
            }
        }
    }
}
