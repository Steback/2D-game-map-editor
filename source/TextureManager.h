#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>

#include "GL/glew.h"

class TextureManager {
    public:
        explicit TextureManager(std::string  _filePath);
        ~TextureManager();
        bool loadTexture();
        void useTexture() const;
        GLuint getTextureID() const;
        int getWidth() const;
        int getHeight() const;
        void clearTexture();

    private:
        int width{};
        int height{};
        GLuint textureID{};
        std::string filePath;
};

#endif
