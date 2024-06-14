
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "vec3.hpp"
#include "vec2.hpp"

#include "colours.hpp"


class Mesh
{
    private:
        std::string object_name;
        std::string material_file;
        std::string material_name;
        bool smooth_shading = false;
        bool material_loaded; //TODO: if material is given the file needs to be loaded

        std::vector<vec3<float>> points;
        std::vector<vec3<float>> normals;
        std::vector<std::vector<int>> faces;
        std::vector<vec2<float>> paramater_vertices; //TODO: make a vec2 class to allow for this format
        std::vector<vec2<float>> texture_vertices;  

    public:
        std::string get_name();
        Mesh(std::ifstream & obj_file);

};
