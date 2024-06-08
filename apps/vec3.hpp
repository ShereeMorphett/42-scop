#include <vector>
#include <sstream>
#include <limits>




template <typename T>
struct vec3
{
    T x;
    T y;
    T z;
};

template <typename T>
vec3<T> parse_vec3(const std::string &line) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;
    if (prefix != "v") {
        throw std::invalid_argument("Invalid prefix for vec3");
    }
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

    if (values.size() != 3) {
        throw std::invalid_argument("Invalid number of values for vec3");
    }

    vec3<T> point;
    point.x = values[0];
    point.y = values[1];
    point.z = values[2];

    return point;
}

