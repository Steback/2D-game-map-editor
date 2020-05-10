#ifndef EDITOR_H
#define EDITOR_H

#include <vector>

// OpenGL loader
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

class Window;
class EditorUI;
class Camera;
class Mesh;
class Shader;
class AssetsManager;
class EntityManager;

class Editor {
    public:
        explicit Editor();
        ~Editor();
        void initialized();
        bool isRunning();
        void update();
        void render();
        void destory();

        static AssetsManager* assetsManager;
        static EntityManager* entityManaer;
        static std::vector<Shader*> shaders;
        static std::vector<Mesh*> mesh;

    private:
        Window* window;
        EditorUI* ui{};
        Camera* camera{};
        GLfloat deltaTime = 0.0f;
        GLfloat lastTime = 0.0f;
};

#endif