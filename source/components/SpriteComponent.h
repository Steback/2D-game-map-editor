#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Component.h"
#include "../Editor.h"
#include "../TextureManager.h"
#include "../AssetsManager.h"

class SpriteComponent : public Component {
    public:
        std::shared_ptr<TextureManager> texture{};
        int spriteIndex;

        explicit SpriteComponent(const std::string& textureID, int _spriteIndex)
            : texture(Editor::assetsManager->getTexture(textureID)), spriteIndex(_spriteIndex) {  }

        void initialize() override {

        }

        void update(float deltaTime) override {

        }

        void render() override {
            texture->useTexture();
        }
};

#endif