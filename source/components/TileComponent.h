#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "glm/glm.hpp"

#include "../Component.h"
#include "../TextureManager.h"
#include "../Editor.h"

class TileComponent : public Component {
    public:
        glm::mat4 model;
        glm::vec2 tilePos;
        glm::vec2 tileSize;
        std::shared_ptr<TextureManager> tileTexture;

        TileComponent(glm::vec2 _tilePos, glm::vec2 _tileSize, const std::string& _textureID)
            : tilePos(_tilePos), tileSize(_tileSize) {
            tileTexture = Editor::assetsManager->getTexture(_textureID);
        }

        void initialize() override {

        }

        void update(float deltaTime) override {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-tilePos, 0.0f));
            model = glm::scale(model, glm::vec3(tileSize, 1.0f));
        }

        void render() override {
            glUniformMatrix4fv(Editor::shaders[0]->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
            tileTexture->useTexture();
        }
};

#endif
