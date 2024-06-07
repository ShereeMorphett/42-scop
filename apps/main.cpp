#include <iostream>
#include <GLFW/glfw3.h>

void display(GLFWwindow* window, int width, int height) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Your OpenGL rendering code here
    glfwSwapBuffers(window);


}

int main() {
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
