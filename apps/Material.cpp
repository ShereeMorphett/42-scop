#include "Material.hpp"
#include "tools.hpp"  // Include tools.hpp for trim_ws
#include <iostream>
#include <sstream>

namespace scop {

    Material::Material(std::ifstream &material_file)
    {
        std::string line;
        std::string current_key;
        while (material_file.good())
        {
            getline(material_file, line, '\n');
            if (line.substr(0, 6) == "newmtl")
            {
                current_key = trim_ws(line.substr(6));
                material_names.push_back(current_key);
            }
            else if (line.substr(0, 2) == "Ka")
            {
                amb_colour[current_key] = parse_vec3<float>(trim_ws(line.substr(2)));
            }
            else if (line.substr(0, 2) == "Kd")
            {
                diffuse_colour[current_key]= parse_vec3<float>(trim_ws(line.substr(2)));;
            }
            else if (line.substr(0, 2) == "Ks")
            {
                specular_colour[current_key] = parse_vec3<float>(trim_ws(line.substr(2)));
            }
            else if (line.substr(0, 2) == "Tf")
            {
                std::istringstream iss(trim_ws(line.substr(2)));
                float x, y, z;
                iss >> x >> y >> z;
                tansmission_filt_col[current_key] = vec3<float>{x, y, z};
            }
            else if (line.substr(0, 2) == "Ns")
            {
                specular_exponent[current_key] = std::stof(trim_ws(line.substr(2)));
            }
            else if (line.substr(0, 2) == "Ni")
            {
                optical_density[current_key] = std::stof(trim_ws(line.substr(2)));
            }
            else if (line.substr(0, 5) == "illum")
            {
                illumination_model[current_key] = std::stoi(trim_ws(line.substr(5)));
            }
        }

        std::cout << "Material Library created with Material: " << std::endl;
    }

} 
