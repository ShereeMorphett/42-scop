#include "tools.hpp"
#include <iostream>



namespace scop
{
    std::string	trim_ws(std::string input)
    {
        int start = 0;
        int end = input.length();

        while (start < end && std::isspace(input[start]))
            ++start;
        while (end > start && std::isspace(input[end - 1]))
            --end;

        return input.substr(start, end - start);
    }


    std::string construct_new_file_path(const std::string& obj_path, const std::string& file_name)
    {
        size_t last_slash_pos = obj_path.find_last_of('/');
            
        if (last_slash_pos == std::string::npos)
        {
            return obj_path + file_name;
        }
        else
        {
            std::string base_path = obj_path.substr(0, last_slash_pos + 1);
            return base_path + file_name;
        }
    }
}