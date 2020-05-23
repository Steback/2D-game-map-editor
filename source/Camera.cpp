#include "Camera.h"

Camera::Camera(GLfloat FOV, GLfloat _width, GLfloat _height, GLfloat _nearplane, GLfloat _farPlane, glm::vec3 _camPos) :
    cameraPos(_camPos) {
	viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projectionMatrix = glm::perspective(FOV, _width / _height, _nearplane, _farPlane);
}

Camera::~Camera()= default;

glm::mat4 Camera::getViewMatrix() { return viewMatrix; }

glm::mat4 Camera::getprojectionMatrix() { return projectionMatrix; }

glm::vec3 Camera::getCameraPosition() { return cameraPos; }