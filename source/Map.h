#ifndef MAP_H
#define MAP_H

#include "glm/glm.hpp"

#include <string>
#include <vector>

class Entity;

class Map {
    public:
        explicit Map(std::string _textureID);
        ~Map();
        void loadMap(const std::string& _filePath, const glm::vec2& _mapSize);
        void addTile(const glm::vec3& _tilePosition, const glm::vec3& _position);

    private:
        std::string textureID;
        std::vector<Entity> tilemap;
};

#endif