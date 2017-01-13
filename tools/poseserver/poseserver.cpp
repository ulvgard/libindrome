#include <string>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>

#include <cxxopts.hpp>
#include <grpc++/grpc++.h>

#include <pose.pb.h>
#include <pose.grpc.pb.h>

#include <indrome/pose/simple_velocity.h>

#include "poseviewer.cpp"

using grpc::Server;
using grpc::ServerContext;
using grpc::Status;

using indrome_grpc::PoseUpdater;
using indrome_grpc::Pose;
using indrome_grpc::Empty;


std::string usage(const cxxopts::Options& options) { return options.help(options.groups()); }

cxxopts::Options parse_args(int argc, char* argv[])
{
    cxxopts::Options options("Pose server", "Pose server - a tool for visualizing camera pose");
    options.add_options()
        ("h,help","Print help")
        ("url","Server url (default=0.0.0.0:50100)", cxxopts::value<std::string>()
         ->default_value("0.0.0.0:50100"),"URL");

    try
    {
        options.parse(argc, argv);
    }
    catch(const cxxopts::option_not_exists_exception& e) 
    {
        std::cout << "ERROR: " << e.what() << "\n";
        std::cout << usage(options) << std::endl;
        exit(1);
    }

    return options;
}

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;

class ServerImpl final {
    public:
        ServerImpl(indrome::pose::SimpleVelocityModel* posemodel) :
            posemodel(posemodel)
    {}

        void Shutdown() {
            server_->Shutdown();
            cq_->Shutdown();
        }

        void Run(const std::string& url) {

            ServerBuilder builder;
            builder.AddListeningPort(url, grpc::InsecureServerCredentials());
            builder.RegisterService(&service_);
            cq_ = builder.AddCompletionQueue();
            server_ = builder.BuildAndStart();
            std::cout << "Server listening on " << url << std::endl;

            HandleRpcs();
        }

    private:
        indrome::pose::SimpleVelocityModel* posemodel;
        
        class CallData {
            public:
            CallData(PoseUpdater::AsyncService* service, ServerCompletionQueue* cq, indrome::pose::SimpleVelocityModel* posemodel) 
                : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), posemodel(posemodel) {
                Proceed();
            }

            void Proceed() {
                if (status_ == CREATE) {
                    // Make this instance progress to the PROCESS state.
                    status_ = PROCESS;

                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    
                    service_->RequestPoseUpdate(&ctx_, &request_, &responder_, cq_, cq_, this); 
                } else if (status_ == PROCESS) {
                    // Spawn a new CallData instance to serve new clients while we process
                    // the one for this CallData. The instance will deallocate itself as
                    // part of its FINISH state.
                    new CallData(service_, cq_, posemodel);

                    // The actual processing.
                    auto R = request_.r();
                    auto t = request_.t();

                    posemodel->add_measurment(
                        std::array<float, 3>{t.coeffs(0), t.coeffs(1), t.coeffs(2)}
                    );

                    // And we are done! Let the gRPC runtime know we've finished, using the
                    // memory address of this instance as the uniquely identifying tag for
                    // the event.
                    status_ = FINISH;
                    responder_.Finish(reply_, Status::OK, this);
                } else {
                    GPR_ASSERT(status_ == FINISH);
                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            PoseUpdater::AsyncService* service_;
            ServerCompletionQueue* cq_;
            ServerContext ctx_;
            indrome::pose::SimpleVelocityModel* posemodel;

            Pose request_;
            Empty reply_;

            // The means to get back to the client.
            ServerAsyncResponseWriter<Empty> responder_;
            // Let's implement a tiny state machine with the following states.
            enum CallStatus { CREATE, PROCESS, FINISH };
            CallStatus status_;  // The current serving state.
        };

        // This can be run in multiple threads if needed.
        void HandleRpcs() {
            
            new CallData(&service_, cq_.get(), posemodel);

            void* tag;  // uniquely identifies a request.
            bool ok;
            while (true) {
                // Block waiting to read the next event from the completion queue. The
                // event is uniquely identified by its tag, which in this case is the
                // memory address of a CallData instance.
                // The return value of Next should always be checked. This return value
                // tells us whether there is any kind of event or cq_ is shutting down.
                GPR_ASSERT(cq_->Next(&tag, &ok));
                GPR_ASSERT(ok);
                static_cast<CallData*>(tag)->Proceed();
            }
        }

        std::unique_ptr<ServerCompletionQueue> cq_;
        PoseUpdater::AsyncService service_;
        std::unique_ptr<Server> server_;
};

void server_runlet(ServerImpl* s, const std::string& url) 
{ 
    s->Run(url); 
}

int main(int argc, char* argv[])
{
    cxxopts::Options options = parse_args(argc, argv);

    if(options.count("help") == 1)
    {
        std::cout << usage(options) << std::endl;
        exit(1);
    }

    std::string url = options["url"].as<std::string>();
    cv::Mat rotation = cv::Mat::zeros(1,3,CV_32F);

    indrome::pose::SimpleVelocityModel posemodel;

    ServerImpl server(&posemodel);
    std::thread server_thread(server_runlet, &server, url);

    open_window(posemodel);

    std::cout << "Pose window closed" << std::endl;
    server.Shutdown();
    server_thread.join();
    std::cout << "Server shutdown" << std::endl;
}
