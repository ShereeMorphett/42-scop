
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "vec3.hpp"
#include "vec2.hpp"
#include "Material.hpp"
#include "colours.hpp"

class Material;

//https://en.wikipedia.org/wiki/Wavefront_.obj_file#:~:text=MTL%20File%20Format%20is%20a,OBJ%20files.

namespace scop
{
    class Mesh
    {
        private:
            std::string object_name;
            bool smooth_shading = false;
            std::vector<vec3<float>> points;
            std::vector<vec3<float>> normals;
            std::vector<std::vector<int>> faces;
            std::vector<vec2<float>> paramater_vertices;
            std::vector<vec2<float>> texture_vertices;
            std::vector<std::string> material_names;
            unsigned int num_indices;
            unsigned int num_vertices;

            bool material_loaded;
            Material* mat;

        public:
            std::string get_name();
            std::vector<std::vector<int>> get_faces();
            std::vector<vec3<float>> get_points();
            std::vector<vec3<float>> get_normals();


            unsigned int get_num_indices();
            Mesh(std::ifstream & obj_file, std::string obj_path);
            ~Mesh();

            void set_num_indices(unsigned int size);
            void set_num_vertices(unsigned int size);

            std::vector<float> get_interleaved_vertex_data();
            std::vector<unsigned int> get_index_data();

    };
}
