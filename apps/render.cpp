#include "glad/glad.h"
#include <SFML/Window.hpp>

#include <vector>
#include <iostream>
#include <cmath>
#include "Mesh.hpp"

namespace scop {
    bool camera_change = true;

    void setupProjection(int width, int height)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspect = (float)width / (float)height;
        float near = 0.1f;
        float far = 100.0f;
        float fovY = 45.5f;
        float fH = tan(fovY / 360.0f * 3.14159f) * near;
        float fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, near, far);
        glMatrixMode(GL_MODELVIEW);
    }

    void setupView(vec3<float> eye, vec3<float> center, vec3<float> up)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        vec3<float> forward = center - eye;
        forward = normalize(forward);

        vec3<float> right = cross(forward, up);
        right = normalize(right);

        up = cross(right, forward);

        float viewMatrix[16] = {
            right.x, up.x, -forward.x, 0.0f,
            right.y, up.y, -forward.y, 0.0f,
            right.z, up.z, -forward.z, 0.0f,
            0.0f,    0.0f,  0.0f,      1.0f
        };

        glMultMatrixf(viewMatrix);
        glTranslatef(-eye.x, -eye.y, -eye.z);
    }

    void handleInput(sf::Window &window, vec3<float>& eye, vec3<float>& center, float &yaw, float &pitch, float &zoom) {
        const float moveSpeed = 0.1f;
        const float turnSpeed = 1.0f;
     
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            zoom -= moveSpeed;
            camera_change = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            zoom += moveSpeed;
            camera_change = true;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pitch -= turnSpeed;
            camera_change = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pitch += turnSpeed;
            camera_change = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            yaw -= turnSpeed;
            camera_change = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            yaw += turnSpeed;
            camera_change = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {  // Reset view to look at origin (0, 0, 0)
            center = {0.0f, 0.0f, 0.0f};
            eye = {0.0f, 0.0f, 15.0f};
            camera_change = true;
        }

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        float radYaw = (yaw - 90) * 3.14159f / 180.0f;
        float radPitch = pitch * 3.14159f / 180.0f;
        if (camera_change)
        {
            std::cout << "Camera Position: (" << eye.x << ", " << eye.y << ", " << eye.z << ")" << std::endl;
            std::cout << "pitch:" << pitch << "Yaw: " << yaw << std::endl;
            camera_change = false;
        }

        eye.x  = center.x - cos(radYaw) * cos(radPitch);
        eye.y = center.y -  sin(radPitch);
        eye.z = center.z - sin(radYaw) * cos(radPitch);
        eye = eye * zoom;
    }

    void draw(Mesh &object, sf::Window &window, GLuint VAO) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        std::vector<std::vector<int>> faces = object.get_faces();
        //TODO: something is wrong here, hence the issues with meshs
        for (const auto& face : faces) {
            glBegin(GL_POLYGON);
            for (const auto& vertexIndex : face)
            {
                glArrayElement(vertexIndex);
            }
            glEnd();
        }

        glBindVertexArray(0);

        window.display();
    }

    int render(Mesh &object) {
        sf::Window window(sf::VideoMode(800, 600), object.get_name(), sf::Style::Default, sf::ContextSettings(32));
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        // Initialize Glad using SFML loader function
        if (!gladLoadGLLoader((GLADloadproc)sf::Context::getFunction)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        setupProjection(window.getSize().x, window.getSize().y);
        vec3<float> center = {0.0f, 0.0f, 0.0f};
        vec3<float> eye = {0.0f, 0.0f, 25.0f};

        vec3<float> up = {0.0f, 1.0f, 0.0f};      

        // Initialize camera yaw and pitch
        float yaw = 0.0f, pitch = 0.0f, zoom = 25.0f;


        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        std::vector<vec3<float>> vertices = object.get_points();
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3<float>), vertices.data(), GL_STATIC_DRAW);

        glVertexPointer(3, GL_FLOAT, sizeof(vec3<float>), (void*)0);
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindVertexArray(0);

        bool running = true;
        while (running) {
            setupView(eye, center, up);
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                } else if (event.type == sf::Event::Resized) {
                    glViewport(0, 0, event.size.width, event.size.height);
                    setupProjection(event.size.width, event.size.height);
                }
            }
            handleInput(window, eye, center, yaw, pitch, zoom);

            draw(object, window, VAO);
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        return 0;
    }
}
