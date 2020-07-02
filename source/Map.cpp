#include "Map.h"
#include "Entity.h"
#include "Editor.h"
#include "components/TileComponent.h"
#include "components/MeshComponent.h"

Map::Map(const glm::vec2& _sizeMap, unsigned int _tileSize)
    : sizeMap(_sizeMap), tileSize(_tileSize) {  }

Map::~Map() = default;

void Map::loadMap() {
    for ( int i = 0; i < sizeMap.y; i++ ) {
        for ( int j = 0; j < sizeMap.x; j++ ) {
            glm::vec2 tPos;

            tPos.x = -( ( sizeMap.x * static_cast<float>(tileSize) ) / 2 );
            tPos.y = ( ( sizeMap.y * static_cast<float>(tileSize) ) / 2 );

            tPos.x += static_cast<float>( j * tileSize );
            tPos.y -= static_cast<float>( i * tileSize );

            addTile(tPos,glm::vec2(tileSize, tileSize), "tile-1",
                    "Tile-" + std::to_string(tileMap.size() + 1));
        }
    }
}

void Map::addTile(const glm::vec2& _tilePos, const glm::vec2& _scale, const std::string& _textureID, const std::string& _tileName) {
    Entity& entity = Editor::tileManager->addEntity(Editor::tileManager->entitiesCount() + 1, _tileName, TILEMAP_LAYER);

    entity.addComponent<TileComponent>(_tilePos, _scale, _textureID);

    entity.addComponent<MeshComponent>( std::vector<Shape> {
            { glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0) },
            { glm::vec2(1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );

    tileMap.emplace_back(&entity);
}
