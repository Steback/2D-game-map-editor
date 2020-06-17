#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <memory>

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include "GLFW/glfw3.h"

class Window;
class EditorUI;
class Camera;
class Mesh;
class Shader;
class AssetsManager;
class EntityManager;

class Editor {
    public:
        Editor();
        ~Editor();
        void initialized();
        bool isRunning();
        void render();
        void renderEntities();
        void destroy();

        static std::unique_ptr<AssetsManager> assetsManager;
        static std::unique_ptr<EntityManager> entityManager;
        static std::vector<Shader*> shaders;

    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<EditorUI> ui{};
        std::unique_ptr<Camera> camera{};
        GLfloat deltaTime = 0.0f;
        GLfloat lastTime = 0.0f;
};

#endif