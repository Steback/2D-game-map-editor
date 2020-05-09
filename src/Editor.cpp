#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"

#include "Editor.h"
#include "Constants.h"
#include "Shader.h"
#include "Mesh.h"

Editor::Editor(ImGuiIO& _io) : window(WINDOW_WIDTH, WINDOW_HEIGHT), ui(_io),
    camera(90.0f, window.getWindowSize().x, window.getWindowSize().y, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 20.0f)) {  }

Editor::~Editor() = default;

void Editor::initialized() {
    // Setup Dear ImGui context

    window.initialized();
    ui.initialized(window.getWindow());

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
}

bool Editor::isRunning() { return window.isRunning(); }

void Editor::render() {
    // This function processes only those events that are already in the event queue and then returns immediately.
    glfwPollEvents();

    window.render();
    ui.renderUI();

    shaders[0]->UseShader();

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.0f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(shaders[0]->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shaders[0]->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(camera.getprojectionMatrix()));
    glUniformMatrix4fv(shaders[0]->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
    mesh[0]->RenderMesh();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window.swapBuffers();
}

void Editor::destory() {
    window.destroy();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    for ( auto& s : shaders ) {
        delete s;
    }

    for ( auto& m : mesh ) {
        delete m;
    }
}