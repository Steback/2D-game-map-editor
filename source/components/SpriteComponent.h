#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Component.h"
#include "../Editor.h"
#include "../TextureManager.h"
#include "../AssetsManager.h"

class SpriteComponent : public Component {
    public:
        std::shared_ptr<TextureManager> texture{};
        std::string textureID;
        int spriteIndex;

        explicit SpriteComponent(const std::string& _textureID, int _spriteIndex)
            : texture(Editor::assetsManager->getTexture(_textureID)), spriteIndex(_spriteIndex), textureID(_textureID) {  }

        void initialize() override {

        }

        void update(float deltaTime) override {

        }

        void render() override {
            texture->useTexture();
        }
};

#endif