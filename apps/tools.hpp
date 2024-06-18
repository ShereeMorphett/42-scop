#pragma once

#include <string>



namespace scop
{
        
    std::string	trim_ws(std::string input);
    std::string construct_new_file_path(const std::string& obj_path, const std::string& file_name);
};