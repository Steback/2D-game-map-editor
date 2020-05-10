#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Component.h"

#include "../Editor.h"

class TextureManager;

class SpriteComponent : public Component {
    public:
        explicit SpriteComponent(const std::string& textureID) : texture(Editor::assetsManager->getTexture(textureID)) {  }

        void render() override { texture->useTexture(); }

    private:
        TextureManager* texture{};

};

#endif