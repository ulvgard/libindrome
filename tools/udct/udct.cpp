#include <fstream>
#include <cxxopts.hpp>
#include <indrome/io.h>

void applog(const std::string& msg)
{
    std::cout << ":: " << msg << std::endl;
}

enum FORMAT_TYPE {
    INVALID_TYPE = 0,
    CSV_TYPE,
    JSON_TYPE,
};

std::string to_string(FORMAT_TYPE f)
{
    switch(f)
    {
        case CSV_TYPE:
            return "csv";
        case JSON_TYPE:
            return "json";
        default:
            return "";
    }
}

FORMAT_TYPE from_string(std::string path)
{
    auto ext = path.substr(path.find_last_of(".")+1);
    if(ext.compare("csv") == 0)
        return CSV_TYPE;
    else if(ext.compare("js") == 0 || ext.compare("json") == 0)
        return JSON_TYPE;
    else
        return INVALID_TYPE;
}

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



int main(int argc, char* argv[])
{
    auto args = parse_args(argc, argv);

    applog("UDCT - Ultimate Data Conversion Tool");

    if (args.count("help") || argc == 1)
    {
        std::cout << args.help({"", "Group"}) << std::endl;
        exit(0);
    }


    std::string is;

    if(args.count("input") > 0)
        is = args["input"].as<std::string>();

    std::ifstream ifp;
    ifp.open(is);
    applog("input file: " + is);

    std::vector<std::vector<float>> data;
    if(from_string(is) == CSV_TYPE)
        data = indrome::io::csv::readlines<float>(ifp);
    else
        applog("ERROR: unknown file format");

    std::ostream stream(nullptr);
    stream << "";
    stream.rdbuf(std::cout.rdbuf()); 

    indrome::io::csv::writelines<float>(data, stream);
}
