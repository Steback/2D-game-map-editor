#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "../Component.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component {
    public:
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        glm::vec2 position;

        TileComponent(int _sourceRectX, int _sourceRectY, int _x, int _y, int _tileSize, int _tileScale, const std::string& _assetTextureID) {
            texture = Game::assetManager->getTexture(_assetTextureID);

            sourceRectangle.x = _sourceRectX;
            sourceRectangle.y = _sourceRectY;
            sourceRectangle.w = _tileSize;
            sourceRectangle.h = _tileSize;

            destinationRectangle.x = _x;
            destinationRectangle.y = _y;
            destinationRectangle.w = _tileSize * _tileScale;
            destinationRectangle.h = _tileSize * _tileScale;

            position.x = _x;
            position.y = _y;
        }

        ~TileComponent() override {
                SDL_DestroyTexture(texture);
        }

        void update(float deltatime) override  {
            destinationRectangle.x = static_cast<int>(position.x) - Game::camera.x;
            destinationRectangle.y = static_cast<int>(position.y) - Game::camera.y;
        }

        void render() override {
            TextureManager::draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
};

#endif