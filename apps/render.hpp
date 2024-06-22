#pragma once
#include <SFML/Window.hpp>
#include "Mesh.hpp"
#include "render.hpp"



namespace scop
{
    // void update_input(GLFWwindow* window);
    void draw(Mesh & object, sf::Window & window);
    int render(Mesh & object);
};