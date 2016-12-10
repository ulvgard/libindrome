#pragma once
#include <iostream>
#include <vector>

namespace indrome
{
    namespace io
    {
        namespace csv 
        {
            /**
             * Read a line of consistent CSV from input stream.
             * @param is a stream of CSV delimited by ',' and ended by '\n'
             * @return a vector of parsed values.
             **/
            template<typename T> std::vector<T> readline(const std::string&);

            template<typename T>
            std::vector<std::vector<T> > readlines(std::istream&);
        }
    }
}
