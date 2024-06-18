#pragma once

#include <GLFW/glfw3.h>
#include "Mesh.hpp"


namespace scop
{
    void display(GLFWwindow* window, int width, int height);
    void render(Mesh & object);
};