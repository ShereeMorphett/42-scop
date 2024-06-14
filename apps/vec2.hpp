#pragma once

#include <vector>
#include <sstream>
#include <limits>

template <typename T> //TODO: this may be an issue but for now W Defaults to 0
struct vec2
{
    T u;
    T v;
};

template <typename T>
vec2<T> parse_vec2(const std::string &line) {
    std::istringstream iss(line);
    std::string prefix;

    // std::cout << line << std::endl;

    iss >> prefix;
    iss >> std::ws;
    std::vector<T> values;
    T value;

    while (iss >> value) {
        char c;
        if (iss.get(c) && !isspace(c)) {
            throw std::invalid_argument("Invalid character detected in vec3 values");
        }

        values.push_back(value);
    }

    if (values.size() == 3) {
        std::cout << ("UV format includes a W, this will default to 0, consider another format") << std::endl;
    }
    if (values.size() != 2) {
        throw std::invalid_argument("Invalid number of values for vec2");
    }

    vec2<T> point;
    point.u = values[0];
    point.v = values[1]; // TODO: does this need to be an array to allow for uv??

    return point;
}

