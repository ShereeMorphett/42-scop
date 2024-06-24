#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "Mesh.hpp"


namespace scop {

    void setupProjection(int width, int height)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspect = (float)width / (float)height;
        float near = 0.1f;
        float far = 100.0f;
        float fovY = 45.0f;
        float fH = tan(fovY / 360.0f * 3.14159f) * near;
        float fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, near, far);
        glMatrixMode(GL_MODELVIEW);
    }

    void setupView(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Calculate forward, right and up vectors
        float forward[3], right[3], up[3];
        forward[0] = centerX - eyeX;
        forward[1] = centerY - eyeY;
        forward[2] = centerZ - eyeZ;

        // Normalize forward vector
        float forwardNorm = sqrt(forward[0]*forward[0] + forward[1]*forward[1] + forward[2]*forward[2]);
        forward[0] /= forwardNorm;
        forward[1] /= forwardNorm;
        forward[2] /= forwardNorm;

        // Calculate right vector as cross product of forward and up
        right[0] = forward[1]*upZ - forward[2]*upY;
        right[1] = forward[2]*upX - forward[0]*upZ;
        right[2] = forward[0]*upY - forward[1]*upX;

        // Normalize right vector
        float rightNorm = sqrt(right[0]*right[0] + right[1]*right[1] + right[2]*right[2]);
        right[0] /= rightNorm;
        right[1] /= rightNorm;
        right[2] /= rightNorm;

        // Recalculate up vector as cross product of right and forward
        up[0] = right[1]*forward[2] - right[2]*forward[1];
        up[1] = right[2]*forward[0] - right[0]*forward[2];
        up[2] = right[0]*forward[1] - right[1]*forward[0];

        // Create a 4x4 view matrix from right, up, and forward vectors
        float viewMatrix[16] = {
            right[0],  up[0],  -forward[0],  0.0f,
            right[1],  up[1],  -forward[1],  0.0f,
            right[2],  up[2],  -forward[2],  0.0f,
            0.0f,      0.0f,   0.0f,         1.0f
        };

        glMultMatrixf(viewMatrix);
        glTranslatef(-eyeX, -eyeY, -eyeZ);
    }

        void handleInput(sf::Window &window, float &eyeX, float &eyeY, float &eyeZ, float &centerX, float &centerY, float &centerZ, float &yaw, float &pitch) {
        const float moveSpeed = 0.1f;
        const float turnSpeed = 1.0f;

        // Keyboard movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            eyeZ -= moveSpeed;
            centerZ -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            eyeZ += moveSpeed;
            centerZ += moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            eyeX -= moveSpeed;
            centerX -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            eyeX += moveSpeed;
            centerX += moveSpeed;
        }

        // Arrow key movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pitch -= turnSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pitch += turnSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            yaw -= turnSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            yaw += turnSpeed;
        }

        // Clamp the pitch to avoid gimbal lock
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Calculate the new direction vector
        float radYaw = yaw * 3.14159f / 180.0f;
        float radPitch = pitch * 3.14159f / 180.0f;

        centerX = eyeX + cos(radYaw) * cos(radPitch);
        centerY = eyeY + sin(radPitch);
        centerZ = eyeZ + sin(radYaw) * cos(radPitch);
    }

    void draw(Mesh &object, sf::Window & window) {
        // clear the buffers
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set the modelview matrix
        glMatrixMode(GL_MODELVIEW);

        // Set the drawing color to purple
        std::vector<vec3<float>> vertices = object.get_points();
        std::vector<std::vector<int>> faces = object.get_faces();

        float green = 0.0;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glPolygonMode(GL_FRONT, GL_FILL);

        for (auto face: faces) {
            glBegin(GL_POLYGON);
            for (int index = 0; index < face.size(); index++) {
                green += 0.1;
                glColor3f(1.0, green, 1.0);
                int vertexIndex = face[index];
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
            }
            glEnd();
            glFlush();
        }

        window.display();
    }

    int render(Mesh &object) {
        sf::Window window(sf::VideoMode(800, 600), object.get_name(), sf::Style::Default, sf::ContextSettings(32));
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        setupProjection(window.getSize().x, window.getSize().y);

        // Camera parameters
        float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 5.0f;
        float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
        float upX = 0.0f, upY = 1.0f, upZ = 0.0f;
        float yaw = 0.0f, pitch = 0.0f;

        ////// main rendering loop /////////
        bool running = true;
        while (running) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                } else if (event.type == sf::Event::Resized) {
                    glViewport(0, 0, event.size.width, event.size.height);
                    setupProjection(event.size.width, event.size.height);
                }
            }

            // Handle camera movement
            handleInput(window, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, yaw, pitch);
            // Set up the view matrix
            setupView(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

            draw(object, window);
        }

        return 0;
    }
}
