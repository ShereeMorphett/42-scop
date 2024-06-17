

#include "Material.hpp"
#include "tools.hpp"


/*      std::map<std::string, vec3<float>> amb_colour; //Ka
        std::map<std::string, vec3<float>> diffuse_colour;//Kd
        std::map<std::string, vec3<float>> specular_colour;//Ks
        std::map<std::string, vec3<float>> tansmission_filt_col; //Tf
        std::map<std::string, float> specular_exponent;  //Ns
        std::map<std::string, float> transparency; //sometimes discolve Tr/d
        std::map<std::string, float> optical_density; // Ni
        std::map<std::string, int> illumination_model; // Illum
        std::vector<std::string> material_names;

*/

Material::Material(std::ifstream & material_file)
{
    std::string line;
    std::string current_key;
    while (material_file.good())
    {
        getline(material_file, line, '\n');
        switch(line[0])
        {
            //newmtl
            case '#':
                break;
            case 'Ka':
                break;
            case 'Kd':
                break;
            case 'Ks':
                break;
            case 'Tf':
                break;
            case 'Ns':
                break;
            case 'Ni':
                break;
            case 'ne':
                if (line.substr(0, 4) == "newmtl")
                {
                    current_key = trim_ws(line.substr(5));
                    std::cout << current_key << std::endl;
                    
                    material_names.push_back(current_key);
                }
                break;
            case 'Il':
                if (line.substr(0, 4) == "Illum")
                {

                    // material_names.push_back(trim_ws(line.substr(6)));
                }
                break;
        }
    }

    std::cout <<  FCYN("Material Library created with Material: ") << std::endl;
    // PRINT TEXTURE
};

Material::Material(){};