
#include <SFML/Window.hpp>   // Include SFML window header
#include <SFML/OpenGL.hpp>
#include "Mesh.hpp"



namespace scop{

    int render(Mesh & object)
    {
        sf::Window window(sf::VideoMode(800, 600), object.get_name(), sf::Style::Default, sf::ContextSettings(32));
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        // load resources, initialize the OpenGL states, ...


        //////  main rendering loop /////////
        bool running = true;
        while (running)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    running = false;
                }
                else if (event.type == sf::Event::Resized)
                {
                    glViewport(0, 0, event.size.width, event.size.height);
                }
            }

            // clear the buffers
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // draw...

            // end the current frame (internally swaps the front and back buffers)
            window.display();
        }

        // release resources...

        return 0;
    }
};