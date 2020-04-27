#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"
#include "Editor.h"
#include "Mesh.h"
#include "Shader.h"

int main(int, char**) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    auto* editor = new Editor(io);

    editor->initialized(WINDOW_WIDTH, WINDOW_HEIGHT);

    Shape vertices[] = {
            { -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,},
            { 1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, },
            { 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, },
            { -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f },
    };

    GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

    Mesh mesh(vertices, indices, 4, 6);

    GLuint uniformModel = 0;

    // Main loop
    while ( Editor::isRunning() ) {
        editor->processInput();
        editor->render();

        shader.UseShader();

        uniformModel = shader.GetUniformLocation("model");

        glm::mat4 model(1.0f);
//        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        mesh.RenderMesh();

        editor->swapBuffers();
    }

    editor->destroy();

    delete editor;

    return 0;
}