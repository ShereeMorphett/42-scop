#pragma once

#include <GLFW/glfw3.h>
#include "Mesh.hpp"


namespace scop
{
    void update_input(GLFWwindow* window);
    void draw(GLFWwindow* window, int width, int height);
    void render(Mesh & object);
};