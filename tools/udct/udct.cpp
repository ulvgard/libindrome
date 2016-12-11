#include <fstream>
#include <cxxopts.hpp>
#include <indrome/io.h>

cxxopts::Options parse_args(int argc, char* argv[])
{
    cxxopts::Options options("udct", "Ultimate Data Conversion Tool");
    options.add_options()
        ("h,help", "Print help")
        ("i,input", "Input file", cxxopts::value<std::string>())
        ("o,output", "Output file", cxxopts::value<std::string>())
        ;
    options.parse(argc, argv);
    return options;
}

void applog(const std::string& msg) 
{ 
    std::cout << ":: " << msg << std::endl; 
}

int main(int argc, char* argv[])
{
    auto args = parse_args(argc, argv);

    applog("UDCT - Ultimate Data Conversion Tool");

    if (args.count("help") || argc == 1)
    {
        std::cout << args.help({"", "Group"}) << std::endl;
        exit(0);
    }

    std::ifstream ifp;
    if(args.count("input") > 0)
    {
        auto is = args["input"].as<std::string>();
        ifp.open(is);
        applog("input file: " + is);
    }

    auto data = indrome::io::csv::readlines<float>(ifp);
    applog("read " + std::to_string(data.size())+ " lines");
}
