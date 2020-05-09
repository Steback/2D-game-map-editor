#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Component.h"


class SpriteComponent : public Component {
    public:
        explicit SpriteComponent(const std::string& assetTextureID) {
            setTexture(assetTextureID);
        }

        void setTexture(const std::string& assetTextureID) {

        }

        void render() override {

        }

    private:
        GLuint textureID;
};

#endif