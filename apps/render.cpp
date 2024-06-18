#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"

///https://www.youtube.com/watch?v=p6PqJPFOIm4 TODO:WATCH THIS!!

namespace scop {

    GLuint VAO, VBO, EBO, core_program;

    void draw(GLFWwindow* window, int width, int height, Mesh& object)
    {
        (void) width;
        (void) height;
        
        // Clear the screen
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(core_program);

        // Draw using the VAO
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, object.get_num_indices(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glFlush();
    }

    void update_input(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

    std::string readFile(const char* filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + std::string(filePath));
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    GLuint compileShader(const char* source, GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
        }
        return shader;
    }

    GLuint createShaderProgram(const char* vertexFilePath, const char* fragmentFilePath) {
        std::string vertexSourceStr = readFile(vertexFilePath);
        std::string fragmentSourceStr = readFile(fragmentFilePath);
        const char* vertexSource = vertexSourceStr.c_str();
        const char* fragmentSource = fragmentSourceStr.c_str();

        GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            throw std::runtime_error("Shader linking failed: " + std::string(infoLog));
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

  void setup_VAO(Mesh& object)
  {
        // Replace with actual function to get your data
        std::vector<float> vertices = object.get_interleaved_vertex_data(); // This should return a vector of floats
        std::vector<unsigned int> indices = object.get_index_data(); // This should return a vector of indices
        object.set_num_indices(indices.size());
        object.set_num_vertices(vertices.size());
        // Generate and bind the VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind the VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Generate and bind the EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Assuming interleaved data format: position, normal, texCoord
        // Each vertex attribute should be set up accordingly

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Unbind the VAO
        glBindVertexArray(0);

    }

    void render(Mesh& object)
    {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        const int window_width = 500;
        const int window_height = 500;

        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        GLFWwindow* window = glfwCreateWindow(window_width, window_height, object.get_name().c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to open window");
        }

        glfwMakeContextCurrent(window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLEW");
        }

        const char* vertexSource = "../apps/vertex_shader.glsl"; // Load your vertex shader source here
        const char* fragmentSource = "../apps/fragment_shader.glsl"; // Load your fragment shader source here
        core_program = createShaderProgram(vertexSource, fragmentSource);


        // Setup VAO
        setup_VAO(object);

        // OpenGL configuration
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Main loop
        while (!glfwWindowShouldClose(window)) {
            update_input(window);

            // Draw function
            draw(window, window_width, window_height, object);

            // Poll for and process events
            glfwPollEvents();
        }

        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
    }

}
