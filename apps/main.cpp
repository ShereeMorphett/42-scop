#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include "colours.hpp"
#include "Mesh.hpp"
#include "render.hpp"
#include <unistd.h>
#include <string>

using namespace scop;


std::string getCurrentPath() {
    char temp[FILENAME_MAX];
    if (getcwd(temp, sizeof(temp)) != NULL) {
        return std::string(temp);
    } else {
        perror("getcwd error");
        return "";
    }
}




int main(int argc, char** argv) {

    if (argc != 2)
    {
        std::cerr << BOLD(FRED("Please give a filename at startup")) << std::endl;
        return 1;
    }

    std::cout << argv[1] << std::endl;

    std::ifstream object_file(argv[1]);
    
    if (object_file.is_open())
    {
        try
        {
            Mesh object = Mesh(object_file, static_cast<std::string>(argv[1]));
            render(object);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr << BOLD(FRED("Invalid .obj file")) << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << BOLD(FRED("Error opening file")) << std::endl;
        return 1;
    }


    return 0;
}
