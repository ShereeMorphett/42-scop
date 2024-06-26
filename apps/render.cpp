#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <vector>
#include <iostream>
#include <cmath>
#include "Mesh.hpp"

namespace scop {

    vec3<float> calculateBoundingBox(Mesh& object) {

        std::vector<vec3<float>> vertices = object.get_points();
        vec3<float> centeroid;
        
        if (vertices.empty())
        {
            throw std::invalid_argument("Invalid nuber of vertices");
            return centeroid;
        }

        float size = vertices.size();
        std::cout << "size: " << size << std::endl;
        for (const auto& vertex : vertices) {
            centeroid.x += vertex.x;
            centeroid.y += vertex.y;
            centeroid.z += vertex.z;
        }
        centeroid.x /= size;
        centeroid.y /= size;
        centeroid.z /= size;

        return centeroid;
    }

    void setupProjection(int width, int height) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspect = (float)width / (float)height;
        float near = 0.1f;
        float far = 100.0f;
        float fovY = 100.0f;
        float fH = tan(fovY / 360.0f * 3.14159f) * near;
        float fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, near, far);
        glMatrixMode(GL_MODELVIEW);
    }

    void setupView(vec3<float> eye, vec3<float> center, vec3<float> up)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        vec3<float> forward = {center.x - eye.x, center.y - eye.y, center.z - eye.z};
        float forwardNorm = sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
        forward = {forward.x / forwardNorm, forward.y / forwardNorm, forward.z / forwardNorm};

        vec3<float> right = {
            forward.y * up.z - forward.z * up.y,
            forward.z * up.x - forward.x * up.z,
            forward.x * up.y - forward.y * up.x
        };
        float rightNorm = sqrt(right.x * right.x + right.y * right.y + right.z * right.z);
        right = {right.x / rightNorm, right.y / rightNorm, right.z / rightNorm};

        up = {
            right.y * forward.z - right.z * forward.y,
            right.z * forward.x - right.x * forward.z,
            right.x * forward.y - right.y * forward.x
        };

        float viewMatrix[16] = {
            right.x, up.x, -forward.x, 0.0f,
            right.y, up.y, -forward.y, 0.0f,
            right.z, up.z, -forward.z, 0.0f,
            0.0f,    0.0f,  0.0f,      1.0f
        };

        glMultMatrixf(viewMatrix);
        glTranslatef(-eye.x, -eye.y, -eye.z);
    }



    void handleInput(sf::Window &window, vec3<float>& eye, vec3<float>& center, float &yaw, float &pitch) {
        const float moveSpeed = 0.1f;
        const float turnSpeed = 1.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            eye.z -= moveSpeed;
            center.z -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            eye.z += moveSpeed;
            center.z += moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            eye.x -= moveSpeed;
            center.x -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            eye.x += moveSpeed;
            center.x += moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {  //TODO: make these controls less shit
            eye.y -= moveSpeed;
            center.y -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            eye.y += moveSpeed;
            center.y += moveSpeed;
        }

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

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        float radYaw = yaw * 3.14159f / 180.0f;
        float radPitch = pitch * 3.14159f / 180.0f;

        center.x = eye.x + cos(radYaw) * cos(radPitch);
        center.y = eye.y + sin(radPitch);
        center.z = eye.z + sin(radYaw) * cos(radPitch);
        
    }

    void draw(Mesh &object, sf::Window &window) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);

        std::vector<vec3<float>> vertices = object.get_points();
        std::vector<std::vector<int>> faces = object.get_faces();

        float green = 0.0;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        for (auto face : faces) {
            // glBegin(GL_TRIANGLES);
            glBegin(GL_POLYGON);

            for (unsigned int index = 0; index < face.size(); index++) {
                green += 0.1;
                glColor3f(1.0, green, 1.0);
                int vertexIndex = face[index];
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
            }
            glEnd();
        }

        window.display();
    }

    int render(Mesh &object) {
        sf::Window window(sf::VideoMode(800, 600), object.get_name(), sf::Style::Default, sf::ContextSettings(32));
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        setupProjection(window.getSize().x, window.getSize().y);


        vec3<float> center = calculateBoundingBox(object); //TODO: this needs to be done with the centroid, add all the vertices together and use median
        std::cout << "camera.x: " << center.x << " camera.y: " << center.y << " camera.z: " << center.z << std::endl;
        vec3<float> eye;
        eye.x = center.x;
        eye.y = center.y;
        eye.z = center.z;
        vec3<float> up = {};
        up.y = 1.0f;

        float yaw = 0.0f, pitch = 0.0f;

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

            handleInput(window, eye, center, yaw, pitch);
            setupView(eye, center, up);

            draw(object, window);
        }

        return 0;
    }
}
