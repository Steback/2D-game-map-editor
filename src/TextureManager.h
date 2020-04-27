#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>

#include <GL/glew.h>

class TextureManager {
    public:
        explicit TextureManager(const std::string& _filePath);
        ~TextureManager();
        GLuint& getTexture();
        int getWidth() const;
        int getHeight() const;
        void clearTexture();

    private:
        int width{};
        int height{};
        GLuint textureID{};

        void loadTexture(const std::string& _filePath);
};

#endif
