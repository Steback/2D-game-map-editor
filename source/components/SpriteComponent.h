#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Component.h"
#include "../Editor.h"
#include "../TextureManager.h"
#include "../AssetsManager.h"

class SpriteComponent : public Component {
    public:
        std::shared_ptr<TextureManager> texture{};

        explicit SpriteComponent(const std::string& textureID) : texture(Editor::assetsManager->getTexture(textureID)) {  }

        void initialize() override { texture->loadTexture(); }

        void update(float deltaTime) override {  }

        void render() override { texture->useTexture(); }
};

#endif