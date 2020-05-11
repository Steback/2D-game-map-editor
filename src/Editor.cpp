#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"

#include "Editor.h"
#include "Window.h"
#include "EditorUI.h"
#include "Constants.h"
#include "Shader.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityManager.h"
#include "AssetsManager.h"


// TODO: Statics objects
AssetsManager* Editor::assetsManager;
EntityManager* Editor::entityManaer;
std::vector<Shader*> Editor::shaders;
std::vector<Mesh*> Editor::mesh;

Editor::Editor() : window(new Window(WINDOW_WIDTH, WINDOW_HEIGHT)) {  }

Editor::~Editor() = default;

void Editor::initialized() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    window->initialized();

    ui = new EditorUI(io);
    ui->initialized(window->getWindow());

    camera = new Camera(90.0f, window->getWindowSize().x, window->getWindowSize().y, 0.1f, 100.0f,
            glm::vec3(0.0f, 0.0f, 100.0f));

    entityManaer = new EntityManager;
    assetsManager = new AssetsManager;

    std::vector<Shape> vertices {
            { -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,},
            { -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    };

    std::vector<GLuint> indices{
            0, 1, 2,
            0, 2, 3
    };

    auto* shader = new Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    shaders.push_back(shader);

    Mesh* mesh1 = new Mesh(vertices, indices);
    mesh.push_back(mesh1);

    Entity& entity = entityManaer->addEntity("chopper", PLAYER_LAYER);
    entity.addComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 2.5f, 0.0f),
            0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    entityManaer->initialize();
}

bool Editor::isRunning() { return window->isRunning(); }

void Editor::update() {
    GLfloat now = glfwGetTime();
    deltaTime = now - lastTime;
    lastTime = now;

    shaders[0]->UseShader();

    entityManaer->update(deltaTime);
}

void Editor::render() {
    // This function processes only those events that are already in the event queue and then returns immediately.
    glfwPollEvents();

    window->render();
    ui->renderUI();

    glUniformMatrix4fv(shaders[0]->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(camera->getprojectionMatrix()));
    glUniformMatrix4fv(shaders[0]->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));

    entityManaer->render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window->swapBuffers();
}

void Editor::destory() {
    window->destroy();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    for ( auto& s : shaders ) {
        delete s;
    }

    for ( auto& m : mesh ) {
        delete m;
    }

    delete window;
    delete ui;
    delete camera;
    delete entityManaer;
    delete assetsManager;
}