#include <fstream>
#include <utility>

#include "Map.h"
#include "Entity.h"
#include "Editor.h"
#include "components/TileComponent.h"
#include "components/MeshComponent.h"

Map::Map(const glm::vec2& _sizeMap, unsigned int _tileSize, std::string _filePath)
    : sizeMap(_sizeMap), tileSize(_tileSize), filePath(std::move(_filePath)) {  }

Map::~Map() = default;

void Map::loadMap() {
    std::fstream mapFile;
    mapFile.open(filePath);

    int x = 1;

    for ( int i = 0; i < static_cast<int>(sizeMap.y); i++ ) {
        for ( int j = 0; j < static_cast<int>(sizeMap.x); j++ ) {
            char ch[2];

            mapFile.get(ch[0]);

            mapFile.get(ch[1]);

            int tileID = std::atoi(ch) + 1;

            glm::vec2 tPos;

            tPos.x = -( ( sizeMap.x * static_cast<float>(tileSize) * 2 ) / 2 );
            tPos.y = ( ( sizeMap.y * static_cast<float>(tileSize) * 2) / 2 );

            tPos.x += static_cast<float>( j * tileSize * 2);
            tPos.y -= static_cast<float>( i * tileSize * 2);

            addTile(tPos,glm::vec2(tileSize, tileSize), std::string("tile-" + std::to_string(tileID)),
                    "Tile-" + std::to_string(tileMap.size() + 1));

            tilesID.push_back(1);

            x++;
            mapFile.ignore();
        }
    }
}

void Map::addTile(const glm::vec2& _tilePos, const glm::vec2& _scale, const std::string& _textureID, const std::string& _tileName) {
    Entity& entity = Editor::tileManager->addEntity(Editor::tileManager->entitiesCount() + 1, _tileName, TILEMAP_LAYER);

    entity.addComponent<TileComponent>(_tilePos, _scale, _textureID);

    // Texture coords Inverse, for bug in textures
    entity.addComponent<MeshComponent>( std::vector<Shape> {
            { glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, 1.0) },
            { glm::vec2(1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );

    tileMap.emplace_back(&entity);
}

void Map::createMapFile() {
    std::ofstream mapFile;
    mapFile.open(filePath, std::ios::out);

    for ( int i = 0; i < Editor::tileManager->entitiesCount(); i++ ) {
        if ( tilesID[i] < 10 ) mapFile << 0;

        mapFile << tilesID[i];

        if ( (i + 1) % static_cast<int>(sizeMap.x) == 0 ) {
            mapFile << '\n';
        } else {
            mapFile << ',';
        }
    }

    mapFile << '\n';

    for ( int i = 0; i < static_cast<int>(sizeMap.y); i++ ) {
        for ( int j = 0; j < static_cast<int>(sizeMap.x); j++ ) {
            if ( i == 0 || i == static_cast<int>(sizeMap.y) - 1 ) {
                mapFile << '1';
            } else if ( j == 0 || j == static_cast<int>(sizeMap.x) - 1 ) {
                mapFile << '1';
            } else {
                mapFile << '0';
            }

            if ( j + 1 != static_cast<int>(sizeMap.x) ) mapFile << ',';
        }

        mapFile << '\n';
    }

    mapFile.close();
}

std::string Map::getFilePath() const { return filePath; }

unsigned int Map::getTileSize() const { return tileSize; }

glm::vec2 Map::getMapSize() const { return sizeMap; }
