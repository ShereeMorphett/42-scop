#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include "colours.hpp"
#include "Mesh.hpp"
#include <unistd.h>


void display(GLFWwindow* window, int width, int height) {
    (void) width;
    (void) height;
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // Your OpenGL rendering code here
    glfwSwapBuffers(window);
}

std::string getCurrentPath() {
    char temp[FILENAME_MAX];
    if (getcwd(temp, sizeof(temp)) != NULL) {
        return std::string(temp);
    } else {
        perror("getcwd error");
        return "";
    }
}

int main(int argc, char** argv) {

    if (argc != 2)
    {
        std::cerr << BOLD(FRED("Please give a filename at startup")) << std::endl;
        return 1;
    }

    std::cout << argv[1] << std::endl;

    std::ifstream object_file(argv[1]);
    
    if (object_file.is_open())
    {
        try
        {
            Mesh object(object_file);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr << BOLD(FRED("Invalid .obj file")) << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << BOLD(FRED("Error opening file")) << std::endl;
        return 1;
    }











    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(500, 500, "Your first OpenGL Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
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

    return 0;
}
