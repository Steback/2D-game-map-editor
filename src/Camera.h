#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
    public:
        Camera(GLfloat FOV, GLfloat _width, GLfloat _height, GLfloat _nearplane, GLfloat _farPlane, glm::vec3 _camPos);
        ~Camera();
        glm::mat4 getViewMatrix();
        glm::mat4 getprojectionMatrix();
        glm::vec3 getCameraPosition();

    private:
        glm::mat4 viewMatrix{};
        glm::mat4 projectionMatrix{};
        glm::vec3 cameraPos;
};

#endif