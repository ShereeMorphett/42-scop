
#include <GLFW/glfw3.h>
#include "Mesh.hpp"


namespace scop
{

    void display(GLFWwindow* window, int width, int height) {
        (void) width;
        (void) height;
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        // Your OpenGL rendering code here
        glfwSwapBuffers(window);
    }



    void render(Mesh & object)
    {
        // Initialize GLFW
        if (!glfwInit()) {
            throw std::logic_error("Failed to initialize GLFW"); //TODO: this is not a logic error
        }

        // Create a windowed mode window and its OpenGL context
        GLFWwindow* window = glfwCreateWindow(500, 500, object.get_name().c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            throw std::logic_error("Failed to open window"); //TODO: this is not a logic error
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Set the function for rendering
        glfwSetFramebufferSizeCallback(window, display);

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window)) {
            // Render here
            display(window, 500, 500);

            // Poll for and process events
            glfwPollEvents();
        }

        // Clean up GLFW
        glfwTerminate();

    }




};