#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>

#include <GL/glew.h>

class TextureManager {
    public:
        static void loadTexture(const std::string& _filePath, int& _imageWidth, int& _imageHeight, GLuint& _imageTexture);

    private:
};

#endif
