
#include "Mesh.hpp"
#include <sstream>
#include <limits>

std::string	TrimWs(std::string input)
{
	int start = 0;
    int end = input.length();

    while (start < end && std::isspace(input[start]))
        ++start;
    while (end > start && std::isspace(input[end - 1]))
        --end;

    return input.substr(start, end - start);
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

// # List of texture coordinates, in (u, [v, w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
// vt 0.500 1 [0]
// vt ...
// ...
// # List of vertex normals in (x,y,z) form; normals might not be unit vectors.
// vn 0.707 0.000 0.707
// vn ...
// ...
// # Parameter space vertices in (u, [v, w]) form; free form geometry statement (see below)
// vp 0.310000 3.210000 2.100000
// vp ..


Mesh::Mesh(std::ifstream& obj_file)
{
    std::string line;
    while (obj_file.good())
    {
        getline(obj_file, line, '\n');
        switch(line[0])
        {
            case 'o':
                object_name = TrimWs(line.substr(1));
                break;
            case '#':
                break;
            case 'm':
                if (line.substr(0, 6) == "mtllib")
                    material_file = TrimWs(line.substr(6));
                break;
            case 'u':
                if (line.substr(0, 6) == "usemtl")
                    material_name = TrimWs(line.substr(6));
                break;
            case 's':
                if (TrimWs(line.substr(1)) == "on")
                    smooth_shading = true;
                break;
            case 'v':
                if (line[1] == 'n')
                    normals.push_back(parse_vec3<float>(line));
                else if (line[1] == 't')
                    // # List of texture coordinates, in (u, [v, w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
                    // vt 0.500 1 [0]
                    texture_vertices.push_back(parse_vec3<float>(line)); //TODO: these need to be vec2 with own parser
                else if (line[1] == 'p')
                    // # Parameter space vertices in (u, [v, w]) form; free form geometry statement (see below)
                    // vp 0.310000 3.210000 2.100000
                    paramater_vertices.push_back(parse_vec3<float>(line)); //TODO: these need to be vec2 with own parser
                else
                    points.push_back(parse_vec3<float>(line));
                break;
            case 'f':
                faces.push_back(parse_faces(line));
                break;
        }
    }
    std::cout << "Material file: " << material_file << std::endl;
    std::cout << "Object name: " << object_name << std::endl;
    std::cout << "smooth_shading: " << smooth_shading << std::endl;

    std::cout <<  FCYN("mesh created") << std::endl;
};
