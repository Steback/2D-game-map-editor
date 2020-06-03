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
    window->initialized();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

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

    tinyxml2::XMLDocument tileMap;

    tinyxml2::XMLError error = tileMap.LoadFile("assets/tilemap.xml");

    if ( error != tinyxml2::XML_SUCCESS ) {
        std::cerr << "Error loading XML file: assets/tilemap.xml" << '\n';
    }
    
    tinyxml2::XMLNode* tile = tileMap.RootElement()->FirstChild();

    while ( tile != nullptr ) {
        assetsManager->addTexture( tile->FirstChildElement("name")->FirstChild()->Value(),
                tile->FirstChildElement("path")->FirstChild()->Value() );

        tile = tile->NextSibling();
    }

    for ( int i = 0; i < 30; i++ ) {
        Entity& entityTile = entityManager->addEntity("tile-" + std::to_string( i + ( 1 * 100 ) ), TILEMAP_LAYER);
        entityTile.addComponent<SpriteComponent>("tile-" + std::to_string(i + 1));
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

void Editor::destroy() {
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