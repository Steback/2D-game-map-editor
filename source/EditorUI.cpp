#include <iostream>

#include "EditorUI.h"
#include "Editor.h"
#include "EntityManager.h"
#include "AssetsManager.h"
#include "Entity.h"

EditorUI::EditorUI(ImGuiIO& _io) : io(_io) {  }

EditorUI::~EditorUI() = default;

void EditorUI::initialized(GLFWwindow* _window) {
    // TODO: Setup Dear ImGui style
    ImGui::StyleColorsDark();
    style.WindowBorderSize = 0.0f;
    style.WindowRounding = 0;
    style.WindowPadding = ImVec2(10, 15);

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // TODO: Load Font
    io.Fonts->AddFontFromFileTTF("assets/fonts/Karla-Regular.ttf", 16.0f);

    // TODO: Window flags
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    windowFlags |= ImGuiWindowFlags_NoResize;
}

void EditorUI::renderUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    mainMenuBar();
    entitiesPanel();
    proprietiesPanel();
    tilesMapPanel();

    ImGui::Render();
}

void EditorUI::mainMenuBar() {
    // Menu bar
    if ( ImGui::BeginMainMenuBar() ) {
        if ( ImGui::BeginMenu("File") ) {
            if ( ImGui::MenuItem("New") ) {  }
            if ( ImGui::MenuItem("Open", "Ctrl+O") ) {  }
            if ( ImGui::MenuItem("Save", "Ctrl+S") ) {  }
            if ( ImGui::MenuItem("Save As..") ) { }

            ImGui::Separator();

            if ( ImGui::MenuItem("Options") ) {  }
            if ( ImGui::MenuItem("Versions") ) { showInfo = !showInfo; }
            if ( ImGui::MenuItem("Quit", "Alt+F4") ) {  }

            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu("Edit") ) {
            if ( ImGui::MenuItem("Undo", "CTRL+Z") ) {  }
            if ( ImGui::MenuItem("Redo", "CTRL+Y", false, false) ) {}  // Disabled item

            ImGui::Separator();

            if ( ImGui::MenuItem("Cut", "CTRL+X") ) {  }
            if ( ImGui::MenuItem("Copy", "CTRL+C") ) {  }
            if ( ImGui::MenuItem("Paste", "CTRL+V") ) {  }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    getVersions();
}

void EditorUI::entitiesPanel() {
    ImGui::SetNextWindowPos(ImVec2(0,22), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ( io.DisplaySize.y * 0.6f) - 22), ImGuiCond_Always);

    ImGui::Begin("Entities", nullptr, windowFlags);
        if ( ImGui::Button("Add Entity") ) createEntity = !createEntity;

        int entityIndex = 1;
        for ( auto & entityName : EntityManager::entitiesID ) {
            if ( entityIndex % 2 == 0 ) ImGui::SameLine();

            ImGui::Image( (void*)(intptr_t)Editor::assetsManager->getTexture(entityName.second.first)->getTextureID(),
                          ImVec2(60, 60) );

            entityIndex++;
        }

        // TODO: Create Entities
        if ( createEntity ) {
            ImGui::SetNextWindowPos(ImVec2(( io.DisplaySize.x / 2 ) - 150,( io.DisplaySize.y / 2 ) - 115), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(300, 230), ImGuiCond_Always);

            ImGui::Begin("Create Entity", &createEntity, ImGuiWindowFlags_NoResize);

            // Entity Name
            static std::array<char, 30> entityName{};
            ImGui::InputText("Entity Name", &entityName[0], entityName.size());

            // Entity Layer
            std::vector<std::string> layerTypes = { "VEGETATION_LAYER", "ENEMY_LAYER", "OBSTACLE_LAYER", "PLAYER_LAYER" };
            static int layerIndex = 0;
            std::string currentLayer = layerTypes[layerIndex];

            if ( ImGui::BeginCombo("Layer Type", &currentLayer[0]) ) {
                for ( int i = 0; i < layerTypes.size(); i++ ) {
                    const bool isSelected = ( layerIndex == i );

                    if ( ImGui::Selectable(&layerTypes[i][0], isSelected ) ) {
                        layerIndex = i;
                    }

                    if ( isSelected )
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            // Entity Sprite
            static int assetIndex = 0;
            std::string currentAsset = AssetsManager::texturesNames[assetIndex];

            if ( ImGui::BeginCombo("Sprite", &currentAsset[0]) ) {
                for ( int i = 0; i < AssetsManager::texturesNames.size(); i++ ) {
                    const bool isSelected = ( assetIndex == i );

                    if ( ImGui::Selectable(&AssetsManager::texturesNames[i][0], isSelected ) ) {
                        assetIndex = i;
                    }

                    ImGui::Image((void*)(intptr_t)Editor::assetsManager->getTexture(AssetsManager::texturesNames[i])->getTextureID(),
                            ImVec2(60, 60));

                    if ( isSelected )
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            ImGui::Image( (void*)(intptr_t)Editor::assetsManager->getTexture(currentAsset)->getTextureID(),
                        ImVec2(60, 60) );

            // Button
            if ( ImGui::Button("Create") ) {
                Entity& entity = Editor::entityManager->addEntity(Editor::entityManager->entitiesCount() + 1,
                        entityName.data(), static_cast<LayerType>(layerIndex + 1));

                entity.addComponent<TransformComponent>(glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 2.0f),
                                                        0.0f, glm::vec2(0.0f, 0.0f));

                entity.addComponent<SpriteComponent>(currentAsset);

                entity.addComponent<MeshComponent>( std::vector<Shape> {
                        { glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
                        { glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
                        { glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0) },
                        { glm::vec2(1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
                }, std::vector<GLuint> {
                        1, 3, 2,
                        0, 3, 2
                } );

                EntityManager::entitiesID.emplace_back(entity.ID(), std::pair(currentAsset, assetIndex));

                layerIndex = 0;
                assetIndex = 0;
                entityName.fill('\0');

                createEntity = !createEntity;
            }

            ImGui::End();
        }
    ImGui::End();
}

void EditorUI::proprietiesPanel() const {
    ImGui::SetNextWindowPos(ImVec2(0, io.DisplaySize.y  * 0.6f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ( io.DisplaySize.y * 0.4f ) ), ImGuiCond_Always);

    ImGui::Begin("Proprieties", nullptr, windowFlags);
        if ( !EntityManager::entitiesID.empty() ) {
            Entity* entity = Editor::entityManager->getEntityByID(EntityManager::entitiesID[EntityManager::entitiesID.size() - 1].first);

            // Entity Sprite
            auto* entitySprite = dynamic_cast<SpriteComponent*>(entity->components[1]);

            int assetIndex = EntityManager::entitiesID[EntityManager::entitiesID.size() - 1].second.second;
            std::string currentAsset = AssetsManager::texturesNames[assetIndex];

            if ( ImGui::BeginCombo("Sprite", &currentAsset[0]) ) {
                for ( int i = 0; i < AssetsManager::texturesNames.size(); i++ ) {
                    const bool isSelected = ( assetIndex == i );

                    if ( ImGui::Selectable(&AssetsManager::texturesNames[i][0], isSelected ) ) {
                        assetIndex = i;
                    }

                    if ( isSelected ) ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            entitySprite->texture = Editor::assetsManager->getTexture(currentAsset);
            EntityManager::entitiesID[EntityManager::entitiesID.size() - 1].second.first = currentAsset;

            ImGui::Image((void*)(intptr_t)entitySprite->texture->getTextureID(), ImVec2(60, 60));

            // Entity Name
            ImGui::InputText("Name", &entity->name[0], 30);

            // Entity Layer
            std::vector<std::string> layerTypes = { "VEGETATION_LAYER", "ENEMY_LAYER", "OBSTACLE_LAYER", "PLAYER_LAYER" };
            static int layerIndex = entity->layer - 1;
            std::string currentLayer = layerTypes[layerIndex];

            if ( ImGui::BeginCombo("Layer", &currentLayer[0]) ) {
                for ( int i = 0; i < layerTypes.size(); i++ ) {
                    const bool isSelected = ( layerIndex == i );

                    if ( ImGui::Selectable(&layerTypes[i][0], isSelected ) ) {
                        layerIndex = i;
                        entity->layer = static_cast<LayerType>(layerIndex + 1);
                    }

                    if ( isSelected )
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            // Entity Transform
            auto* entityTransform = dynamic_cast<TransformComponent*>(entity->components[0]);

            ImGui::InputFloat("X", &entityTransform->translate.x, 1);
            ImGui::InputFloat("Y", &entityTransform->translate.y, 1);
        }
    ImGui::End();
}

void EditorUI::tilesMapPanel() const {
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 200,22), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y - 22), ImGuiCond_Always);

    ImGui::Begin("Tiles Map", nullptr, windowFlags);
        for ( int i = 0; i < 30; i++ ) {
            if ( ( i + 1 ) % 2 == 0 ) ImGui::SameLine();

            ImGui::Image((void*)(intptr_t)Editor::assetsManager->getTexture("tile-" + std::to_string(i + 1))->getTextureID(),
                         ImVec2(60, 60));
        }
    ImGui::End();
}

void EditorUI::getVersions() {
    if ( showInfo ) {
        ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x / 2) - 145, (io.DisplaySize.y / 2) - 80), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(290, 160), ImGuiCond_Always);

        ImGui::Begin("Version of GLFW, GLSL and OpenGL", &showInfo, ImGuiWindowFlags_NoResize);
            ImGui::Text("GLFW version: %d,%d,%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION );
            ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION) );
            ImGui::Text("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION) );
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR) );
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER) );
        ImGui::End();
    }
}