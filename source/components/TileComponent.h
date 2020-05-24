#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Editor.h"
#include "../Component.h"

class TileComponent : public Component {
    public:
        std::shared_ptr<TextureManager> texture{};
        glm::mat4 model;
        glm::vec3 position;
        int scale;

        TileComponent(const glm::vec2& _texCoords, const glm::vec3& _position, int _scale, const std::string& _textureID)
            : position(_position), scale(_scale), texture(Editor::assetsManager->getTexture(_textureID)) {  }

        void initialize() override {
        }

        void update(float deltatime) override  {
        }

        void render() override {
        }
};

#endif