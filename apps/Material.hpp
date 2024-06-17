
#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "vec3.hpp"
#include "vec2.hpp"

#include "colours.hpp"

class Material
{
    private:
        std::map<std::string, vec3<float>> amb_colour; //Ka
        std::map<std::string, vec3<float>> diffuse_colour;//Kd
        std::map<std::string, vec3<float>> specular_colour;//Ks
        std::map<std::string, vec3<float>> tansmission_filt_col; //Tf
        std::map<std::string, float> specular_exponent;  //Ns
        std::map<std::string, float> transparency; //sometimes discolve Tr/d
        std::map<std::string, float> optical_density; // Ni
        std::map<std::string, int> illumination_model; // Illum
        std::vector<std::string> material_names;
        /*0. Color on and Ambient off
            1. Color on and Ambient on
            2. Highlight on
            3. Reflection on and Ray trace on
            4. Transparency: Glass on, Reflection: Ray trace on
            5. Reflection: Fresnel on and Ray trace on
            6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
            7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
            8. Reflection on and Ray trace off
            9. Transparency: Glass on, Reflection: Ray trace off
            10. Casts shadows onto invisible surfaces
        */

    public:
        Material(std::ifstream & material_file);
        Material(); //TODO: no i do not want this here
};