#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Component.h"

class SpriteComponent : public Component {
    public:
        explicit SpriteComponent(const std::string& assetTextureID) {
            setTexture(assetTextureID);
        }

        explicit SpriteComponent(const std::string& assetTextureID,  bool _isFixed) {
            setTexture(assetTextureID);
        }

        void setTexture(const std::string& assetTextureID) {

        }

        void render() override {

        }
};

#endif