#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tinyxml2.h"

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
std::unique_ptr<AssetsManager> Editor::assetsManager;
std::unique_ptr<EntityManager> Editor::entityManager;
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

    ui = std::make_unique<EditorUI>(io);
    ui->initialized(window->getWindow());

    camera = std::make_unique<Camera>(-90.0f, window->getWindowSize().x, window->getWindowSize().y, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 20.0f));

    entityManager = std::make_unique<EntityManager>();
    assetsManager = std::make_unique<AssetsManager>();

    std::vector<Shape> vertices {
            { glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0) },
            { glm::vec2(1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
    };

    std::vector<GLuint> indices{
            1, 3, 2,
            0, 3, 2
    };

    auto* shader = new Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    shaders.push_back(shader);

    Mesh* mesh1 = new Mesh(vertices, indices);
    mesh.push_back(mesh1);

    tinyxml2::XMLDocument tileMap;

    tinyxml2::XMLError error = tileMap.LoadFile("assets/tilemap.xml");

    if ( error != tinyxml2::XML_SUCCESS ) {
        std::cerr << "Error loading XML file: assets/tilemap.xml" << '\n';
    }
    
    tinyxml2::XMLNode* elem = tileMap.RootElement()->FirstChild();

    while ( elem != nullptr ) {
        assetsManager->addTexture( elem->FirstChildElement("name")->FirstChild()->Value(),
                elem->FirstChildElement("path")->FirstChild()->Value() );

        std::cout << elem->FirstChildElement("name")->FirstChild()->Value() << '\n';
        std::cout << elem->FirstChildElement("path")->FirstChild()->Value() << '\n';

        elem = elem->NextSibling();
    }

    entityManager->initialize();
}

bool Editor::isRunning() { return window->isRunning(); }

void Editor::update() {
    GLfloat now = glfwGetTime();
    deltaTime = now - lastTime;
    lastTime = now;

    shaders[0]->UseShader();

    entityManager->update(deltaTime);
}

void Editor::render() {

    glfwPollEvents();

    window->render();
    ui->renderUI();

    glUniformMatrix4fv(shaders[0]->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(camera->getprojectionMatrix()));
    glUniformMatrix4fv(shaders[0]->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
    entityManager->render();

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
}