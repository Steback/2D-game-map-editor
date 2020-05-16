#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Component.h"
#include "../Editor.h"
#include "../TextureManager.h"
#include "../AssetsManager.h"

class SpriteComponent : public Component {
    public:
        explicit SpriteComponent(const std::string& textureID) : texture(Editor::assetsManager->getTexture(textureID)) {  }

        void initialize() override { texture->loadTexture(); }

        void update(float deltaTime) override {  }

        void render() override { texture->useTexture(); }

    private:
        TextureManager* texture{};

};

#endif