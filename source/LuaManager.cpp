#include <fstream>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"
#include "fmt/core.h"

#include "LuaManager.h"
#include "Editor.h"
#include "EntityManager.h"
#include "Map.h"
#include "Entity.h"

LuaManager::LuaManager() = default;

LuaManager::~LuaManager() = default;

void LuaManager::loadFile(const std::string &_filePath, std::vector<unsigned int>& entitiesID) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    // Level Name
    int idx = _filePath.rfind('/');
    std::string levelName = _filePath.substr(idx + 1);

    // Remove .lua
    idx = levelName.rfind('.');
    int stringSize = levelName.size();

    while ( stringSize > idx ) {
        levelName.pop_back();
        stringSize--;
    }

    lua.script_file(_filePath);

    sol::table levelData = lua[levelName];

    // LOADS MAP FORM LUA CONFIG FILE
    sol::table levelMap = levelData["map"];
    std::string mapTextureID = levelMap["textureAssetId"];

    Editor::map = std::make_unique<Map>();

    Editor::map->loadMap(glm::vec2(static_cast<float>( levelMap["mapSizeX"]),
            static_cast<float>( levelMap["mapSizeY"])),static_cast<unsigned int>(levelMap["scale"]) + 2,
                    levelMap["file"]);

    // LOADS ENITITES FORM LUA CONFIG FILE
    sol::table levelEntities = levelData["entities"];

    unsigned int entityIndex = 0;

    while ( true ) {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];

        if ( existsEntityIndexNode == sol::nullopt ) {
            break;
        } else {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Add entity
            int entityID = Editor::entityManager->entitiesCount() + 1;

            auto &newEntity = Editor::entityManager->addEntity(entityID, entityName, entityLayerType);

            entitiesID.emplace_back(entityID);

            // Add Transform component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];

            if ( existsTransformComponent != sol::nullopt ) {
                glm::vec2 entityPos = glm::vec2(static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                                               static_cast<int>(entity["components"]["transform"]["position"]["y"]));

                entityPos.x -= 750;
                entityPos.y -= 500;

                entityPos /= 10;

                newEntity.addComponent<TransformComponent>(
                        entityPos, glm::vec2(2.0f, 2.0f), 0.0f, glm::vec2(0.0f, 0.0f)
                );
            }

            // Add Sprite Component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];

            if ( existsSpriteComponent != sol::nullopt ) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];

                for (int i = 0; i < Editor::assetsManager->texturesNames.size(); i++) {
                    if (textureId == Editor::assetsManager->texturesNames[i]) {
                        newEntity.addComponent<SpriteComponent>(textureId, i);
                        break;
                    }
                }
            }

            newEntity.addComponent<MeshComponent>(std::vector<Shape>{
                    {glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
                    {glm::vec2(1.0f, 1.0f),   glm::vec2(1.0f, 1.0f)},
                    {glm::vec2(-1.0f, 1.0f),  glm::vec2(0.0f, 1.0)},
                    {glm::vec2(1.0f, -1.0f),  glm::vec2(1.0f, 0.0f)},
            }, std::vector<GLuint>{
                    1, 3, 2,
                    0, 3, 2
            });

            entityIndex++;
        }
    }
}

void LuaManager::writeFile(const std::string &_fileName) {
    std::fstream luaFile;
    luaFile.open(_fileName, std::ios::out);

    // Remove levels/
    int idx = _fileName.rfind('/');
    std::string fileName = _fileName.substr(idx + 1);

    // Remove .lua
    idx = fileName.rfind('.');
    int stringSize = fileName.size();

    while ( stringSize > idx ) {
        fileName.pop_back();
        stringSize--;
    }

    // Begin file
    luaFile << fileName << " =  {\n";

    // Write map info
    luaFile << "\tmap = {\n";
    luaFile << "\t\ttextureAssetId = \"terrain-texture-day\",\n";
    luaFile << "\t\tfile = \"" << Editor::map->getFilePath() << "\",\n";
    luaFile << "\t\tscale = " << Editor::map->getTileSize() - 2 << ",\n";
    luaFile << "\t\ttileSize = 32,\n";
    luaFile << "\t\tmapSizeX = " << Editor::map->getMapSize().x << ",\n";
    luaFile << "\t\tmapSizeY = " << Editor::map->getMapSize().y << ",\n";
    luaFile << "\t},\n";

    luaFile << '\n';

    // Write entities info
    luaFile << "\tentities = {\n";

    if ( Editor::entityManager->entitiesCount() > 0 ) {
        for ( int i = 0; i < Editor::entityManager->entitiesCount(); i++ ) {
            auto* entity = Editor::entityManager->getEntityByID(i + 1);
            luaFile << "\t\t[" << i << "] = {\n";

            // Entity name
            luaFile << "\t\t\tname = \"" << entity->name << "\",\n";

            // Entity layer
            luaFile << "\t\t\tlayer = " << static_cast<int>(entity->layer) << ",\n";

            // Entity Components
            luaFile << "\t\t\tcomponents = {\n";

            // Transform component
            auto* entityTransform = dynamic_cast<TransformComponent*>(entity->components[0]);

            luaFile << "\t\t\t\ttransform = {\n";

            // Position
            luaFile << "\t\t\t\t\tposition = {\n";
            luaFile << "\t\t\t\t\t\tx = " << entityTransform->translate.x << ",\n";
            luaFile << "\t\t\t\t\t\ty = " << entityTransform->translate.y << "\n";
            luaFile << "\t\t\t\t\t},\n";

            // Velocity
            luaFile << "\t\t\t\t\tvelocity = {\n";
            luaFile << "\t\t\t\t\t\tx = 0,\n";
            luaFile << "\t\t\t\t\t\ty = 0\n";
            luaFile << "\t\t\t\t\t},\n";

            luaFile << "\t\t\t\t\twidth = 32,\n";
            luaFile << "\t\t\t\t\theight = 32,\n";
            luaFile << "\t\t\t\t\tscale = 1,\n";
            luaFile << "\t\t\t\t\trotation = 0\n";

            // End Transform component
            luaFile << "\t\t\t\t},\n";

            // Sprite component
            auto* entitySprite = dynamic_cast<SpriteComponent*>(entity->components[1]);

            luaFile << "\t\t\t\tsprite = {\n";
            luaFile << "\t\t\t\t\ttextureAssetId = \"" << entitySprite->textureID << "\",\n";

            if ( entity->layer == PLAYER_LAYER ) {
                luaFile << "\t\t\t\t\tanimated = true,\n";
                luaFile << "\t\t\t\t\tframeCount = 2,\n";
                luaFile << "\t\t\t\t\tanimationSpeed = 90,\n";
                luaFile << "\t\t\t\t\thasDirections = true,\n";
                luaFile << "\t\t\t\t\tfixed = false\n";
            } else {
                luaFile << "\t\t\t\t\tanimated = false\n";
            }

            // End Sprite component
            luaFile << "\t\t\t\t},\n";

            // Collider component
            luaFile << "\t\t\t\tcollider = {\n";

            if ( entity->layer == PLAYER_LAYER ) {
                luaFile << "\t\t\t\t\ttag = \"PLAYER\"\n";
            } else if ( entity->layer == ENEMY_LAYER ) {
                luaFile << "\t\t\t\t\ttag = \"ENEMY\"\n";
            } else if ( entity->layer == VEGETATION_LAYER || entity->layer == OBSTACLE_LAYER ) {
                luaFile << "\t\t\t\t\ttag = \"VEGETATION\"\n";
            } else {
                luaFile << "\t\t\t\t\ttag = \"LEVEL_COMPLETE\"\n";
            }

            // End Collider component
            luaFile << "\t\t\t\t}" << ( entity->layer == PLAYER_LAYER ? "," : "" ) << "\n";

            // Input component
            if ( entity->layer == PLAYER_LAYER ) {
                luaFile << "\t\t\t\tinput = {\n";

                luaFile << "\t\t\t\t\tkeyboard = {\n";
                luaFile << "\t\t\t\t\t\tup = \"w\",\n";
                luaFile << "\t\t\t\t\t\tleft = \"a\",\n";
                luaFile << "\t\t\t\t\t\tdown = \"s\",\n";
                luaFile << "\t\t\t\t\t\tright = \"d\",\n";
                luaFile << "\t\t\t\t\t\tshoot = \"space\"\n";
                luaFile << "\t\t\t\t\t}\n";

                // End Input component
                luaFile << "\t\t\t\t}\n";
            }

            // End Entity Components
            luaFile << "\t\t\t}\n";

            luaFile << "\t\t}" << ( i == Editor::entityManager->entitiesCount() - 1 ? "" : "," ) << "\n";
        }
    }

    luaFile << "\t}\n";

    // End file
    luaFile << "}\n";

    luaFile.close();
}
