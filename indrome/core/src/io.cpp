#include <indrome/io.h>
#include <sstream>
#include <stdexcept>


namespace indrome
{
    namespace io
    {
        namespace csv 
        {
            template<typename T> std::vector<T> readline(const std::string& line)
            {
                std::istringstream sline(line);
                std::string buf;

                std::vector<T> vec;

                while(std::getline(sline, buf, ',')) 
                {
                    std::stringstream ss; T val;
                    ss.str(buf);
                    ss >> val;

                    if(ss.fail())
                        throw std::runtime_error("CSV format is inconsistent");

                    vec.push_back(val);
                }

                return vec;
            }

            template std::vector<int>       readline(const std::string& line);
            template std::vector<float>     readline(const std::string& line);
            template std::vector<double>    readline(const std::string& line);

            template<typename T>
            std::vector<std::vector<T> > readlines(std::istream& is)
            {
                std::vector<std::vector<T>> v;
                std::string line;

                while(std::getline(is, line))
                    v.push_back(readline<T>(line));

                return v; 
            }

            template std::vector<std::vector<int>>       readlines(std::istream& is);
            template std::vector<std::vector<float>>     readlines(std::istream& is);
            template std::vector<std::vector<double>>    readlines(std::istream& is);

            template<typename T> void writeline(const std::vector<T>& row, std::ostream& os)
            {
                for(auto it = row.begin(); it != row.end()-1; it++)
                    os << std::to_string(*it) << ",";
                os << std::to_string(*(row.end()-1)) << "\n";
            }

            template void writeline(const std::vector<int>& row, std::ostream& os);
            template void writeline(const std::vector<float>& row, std::ostream& os);
            template void writeline(const std::vector<double>& row, std::ostream& os);

            template<typename T> void writelines(const std::vector<std::vector<T>>& data, std::ostream& os)
            {
                for(const auto& row: data)
                    writeline<T>(row, os);
            }

            template void writelines(const std::vector<std::vector<int>>& data, std::ostream& os);
            template void writelines(const std::vector<std::vector<float>>& data, std::ostream& os);
            template void writelines(const std::vector<std::vector<double>>& data, std::ostream& os);
        }
    }
}
