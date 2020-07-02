#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "glm/glm.hpp"

class Entity;

class Map {
    public:
        Map(const glm::vec2& _sizeMap, unsigned int _tileSize);
        ~Map();
        void loadMap();
        void addTile(const glm::vec2& _tilePos, const glm::vec2& _scale, const std::string& _textureID, const std::string& _tileName);

    private:
        std::vector<Entity*> tileMap;
        unsigned int tileSize;
        glm::vec2 sizeMap;
};

#endif
