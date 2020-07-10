#include "Camera.h"

Camera::Camera(GLfloat FOV, GLfloat _width, GLfloat _height, GLfloat _nearPlane, GLfloat _farPlane, glm::vec3 _camPos)
    : cameraPos(_camPos), FOV(FOV), windowSize(_width, _height), nearPlane(_nearPlane), farPlane(_farPlane),
    center(0.0f, 0.0f, 0.0f), camOffset(0.0f, 0.0f) {  }

Camera::~Camera() = default;

glm::mat4 Camera::getViewMatrix() { return glm::lookAt(cameraPos, center, glm::vec3(0.0f, 1.0f, 0.0f)); }

glm::mat4 Camera::getProjectionMatrix() const { return glm::perspective(FOV, windowSize.x / windowSize.y, nearPlane, farPlane); }

glm::vec3 Camera::getCameraPosition() { return cameraPos; }

void Camera::setCamPos(const glm::vec2& _mousePos, const glm::vec2& _windowSize) {
    if ( _mousePos.x > 200 && _mousePos.x < 210 ) {
        cameraPos.x += 1;
        center.x += 1;
        camOffset.x += 1;
    }

    if ( _mousePos.y > 22 && _mousePos.y < 32) {
        cameraPos.y -= 1;
        center.y -= 1;
        camOffset.y -= 1;
    }

    if ( _mousePos.x < (_windowSize.x - 200) && _mousePos.x > (_windowSize.x - 210) ) {
        cameraPos.x -= 1;
        center.x -= 1;
        camOffset.x -= 1;
    }

    if ( _mousePos.y < _windowSize.y && _mousePos.y > ( _windowSize.y - 20 ) ) {
        cameraPos.y += 1;
        center.y += 1;
        camOffset += 1;
    }
}

glm::vec2 Camera::getCamOffset() const {
    return camOffset;
}
