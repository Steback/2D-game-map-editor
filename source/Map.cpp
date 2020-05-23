#include "Map.h"
#include "Game.h"
#include "components/TileComponent.h"
#include <fstream>

extern EntityManager manager;

Map::Map(std::string _textureID, int _scale, int _tileSize) {
    textureID = std::move(_textureID);
    scale = _scale;
    tilesize = _tileSize;
}

Map::~Map() = default;

void Map::loadMap(const std::string& _filePath, int _mapSizeX, int _mapSizeY) {
    std::fstream mapFile;
    mapFile.open(_filePath);

    for ( int y = 0; y < _mapSizeY; y++ ) {
        for ( int x = 0; x < _mapSizeX; x++ ) {
            char ch;

            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tilesize;

            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tilesize;

            addTile(sourceRectX, sourceRectY, x * (scale * tilesize), y * (scale * tilesize));

            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::addTile(int _sourceRectX, int _sourceRectY, int _x, int _y) {
    Entity& newTile(manager.addEntity("Tile", TILEMAP_LAYER));
    newTile.addComponent<TileComponent>(_sourceRectX, _sourceRectY, _x, _y, tilesize, scale, textureID);
    tilemap.emplace_back(newTile);
}