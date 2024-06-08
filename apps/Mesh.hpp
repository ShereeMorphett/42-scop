
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "vec3.hpp"
#include "colours.hpp"


class Mesh
{
    private:
        std::string object_name;
        std::string material_file;
        std::string material_name;
        bool smooth_shading = false;
        bool material_loaded;

        std::vector<vec3<float>> points;
        std::vector<std::vector<int>> faces;

    public:
        Mesh(std::ifstream & obj_file);

};
