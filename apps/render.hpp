#pragma once
#include <SFML/Window.hpp>
#include "Mesh.hpp"
#include "render.hpp"



namespace scop
{
    void draw(Mesh & object, sf::Window & window);
    int render(Mesh & object);
};