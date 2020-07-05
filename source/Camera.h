#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
    public:
        Camera(GLfloat FOV, GLfloat _width, GLfloat _height, GLfloat _nearPlane, GLfloat _farPlane, glm::vec3 _camPos);
        ~Camera();
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix() const;
        glm::vec3 getCameraPosition();
        void setCamPos(const glm::vec2& _mousePos, const glm::vec2& _windowSize, glm::vec2 _camOffset);

    private:
        glm::vec3 cameraPos;
        GLfloat FOV;
        glm::vec2 windowSize;
        glm::vec3 center;
        GLfloat nearPlane;
        GLfloat farPlane;
};

#endif