#include <fstream>
#include <utility>

#include "Map.h"
#include "Editor.h"
#include "Entity.h"
#include "components/TileComponent.h"

Map::Map(std::string _textureID)
    : textureID(std::move(_textureID)) {  }

Map::~Map() = default;

void Map::loadMap(const std::string& _filePath, const glm::vec2& _mapSize) {
    std::fstream mapFile;
    mapFile.open(_filePath);

    for ( int y = 0; y < static_cast<int>(_mapSize.y); y++ ) {
        for ( int x = 0; x < static_cast<int>(_mapSize.x); x++ ) {
            char ch;
            glm::vec3 source;

            mapFile.get(ch);
            source.y = atoi(&ch);
            std::cout << source.y << ' ';

            mapFile.get(ch);
            source.x = atoi(&ch);
            std::cout << source.x << ' ';

            mapFile.ignore();
        }

        std::cout << '\n';
    }

    mapFile.close();
}

void Map::addTile(const glm::vec3& _tilePosition, const glm::vec3& _position) {

}