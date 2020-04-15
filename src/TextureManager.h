#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>

#include <GL/glew.h>

class TextureManager {
    public:
        explicit TextureManager(const std::string& _filePath);
        ~TextureManager();
        GLuint getTexture() const;
        int getWidth() const;
        int getHeight() const;

    private:
        int imageWidth{};
        int imageHeight{};
        GLuint imageTexture{};
        unsigned char* imageData{};

        void loadTexture(const std::string& _filePath);
};

#endif
