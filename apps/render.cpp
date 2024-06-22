#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "render.hpp"


namespace scop {
//TODO: pick up from page 37

    void draw(Mesh &object, sf::Window & window) {
        // clear the buffers
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // glMatrixMode(GL_PROJECTION); and glLoadIdentity(); ensure the projection matrix is set correctly.
        // glMatrixMode(GL_MODELVIEW); and glLoadIdentity(); reset the modelview matrix to the identity.
        // Set the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        /*
            glOrtho: Defines a 2D orthographic projection matrix. Here it maps coordinates directly to normalized device coordinates where (0,0) is the bottom-left and (1,1) is the top-right.
            glMatrixMode: Sets the current matrix mode. GL_PROJECTION is for projection matrix operations (defining the view volume), and GL_MODELVIEW is for model transformations.
            glLoadIdentity: Replaces the current matrix with the identity matrix, resetting any previous transformations.
        */
        glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

        // Set the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Set the drawing color to white
        glColor3f(1.0, 0.5, 1.0);

        // Draw the white square
        glBegin(GL_POLYGON);
            glVertex3f(0.25, 0.25, 0.0);
            glVertex3f(0.75, 0.25, 0.0);
            glVertex3f(0.75, 0.75, 0.0);
            glVertex3f(0.25, 0.75, 0.0);
        glEnd();
        glFlush();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    int render(Mesh &object) {
        sf::Window window(sf::VideoMode(800, 600), object.get_name(), sf::Style::Default, sf::ContextSettings(32));
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        // Set the viewport to match the window size
        glViewport(0, 0, window.getSize().x, window.getSize().y);

        ////// main rendering loop /////////
        bool running = true;
        while (running) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                } else if (event.type == sf::Event::Resized) {
                    glViewport(0, 0, event.size.width, event.size.height);
                }
            }
            draw(object, window);
        }

        return 0;
    }
};
