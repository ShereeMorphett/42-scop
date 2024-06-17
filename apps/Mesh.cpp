
#include "Mesh.hpp"
#include "tools.hpp"

#include <sstream>
#include <limits>


std::string Mesh::get_name()
{
    return object_name;
}

std::vector<int> parse_faces(const std::string &line) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix != "f") {
        throw std::invalid_argument("Invalid prefix for faces");
    }

    iss >> std::ws;
    std::vector<int> indices;
    long long index;
    while (iss >> index)
    {
        if (index > std::numeric_limits<int>::max() || index < std::numeric_limits<int>::min()) {
            throw std::invalid_argument("Integer overflow/underflow detected in face indices");
        }

        char c;
        if (iss.get(c) && !isspace(c) && c != '/') {
            std::cout << "|" << c << "|" << std::endl; //TODO: remove before finishing
            throw std::invalid_argument("Invalid character detected in face indices");
        }
        if (c != '/')
            indices.push_back(static_cast<int>(index));
    }

    return indices;
}


Mesh::Mesh(std::ifstream& obj_file, std::string obj_path)
{
    std::string line;
    while (obj_file.good())
    {
        getline(obj_file, line, '\n');
        switch(line[0])
        {
            case 'o':
                object_name = trim_ws(line.substr(1));
                break;
            case '#':
                break;
            case 'm':
                if (line.substr(0, 6) == "mtllib")
                {
                    std::string file_name = construct_new_file_path(obj_path, trim_ws(line.substr(6)));
                    std::ifstream material_file(file_name);
                    try
                    {
                        if (material_file.is_open())
                        {
                            mat = Material(material_file);
                            material_loaded = true;
                        }
                        else
                        {
                            throw std::invalid_argument("Invalid .mtl file"); //TODO: IS this correct?
                        }
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                break;
            case 'u':
                if (line.substr(0, 6) == "usemtl")
                {
                    material_names.push_back(trim_ws(line.substr(6)));
                }
                break;
            case 's':
                if (trim_ws(line.substr(1)) == "on")
                    smooth_shading = true;
                break;
            case 'v':
                if (line[1] == 'n')
                    normals.push_back(parse_vec3<float>(line));
                else if (line[1] == 't')
                    // # List of texture coordinates, in (u, [v, w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
                    // vt 0.500 1 [0]
                    texture_vertices.push_back(parse_vec2<float>(line)); //TODO: these need to be vec2 with own parser
                else if (line[1] == 'p')
                    // # Parameter space vertices in (u, [v, w]) form; free form geometry statement (see below)
                    // vp 0.310000 3.210000 2.100000
                    paramater_vertices.push_back(parse_vec2<float>(line)); //TODO: these need to be vec2 with own parser
                else
                    points.push_back(parse_vec3<float>(line));
                break;
            case 'f':
                faces.push_back(parse_faces(line));
                break;
        }
    }

    // std::cout << "Material file: " << mat.material_file << std::endl;
    std::cout << "Object name: " << object_name << std::endl;
    std::cout << "smooth_shading: " << smooth_shading << std::endl;

    std::cout <<  FCYN("mesh created") << std::endl;
};
