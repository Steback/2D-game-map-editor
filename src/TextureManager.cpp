#include <iostream>

#include "../lib/stb/stb_image.h"

#include "TextureManager.h"

void TextureManager::loadTexture(const std::string &_filePath, int &_imageWidth, int &_imageHeight, GLuint &_imageTexture) {
    int imageWidth = 0;
    int imageHeight = 0;
    unsigned char* imageData = stbi_load("assets/images/chopper-single.png", &imageWidth, &imageHeight, nullptr, 4);

    if ( imageData == nullptr ) {
        std::cerr << "Fail load image" << std::endl;
    }

    // Create a OpenGL texture identifer
    GLuint imageTexture;
    glGenTextures(1, &imageTexture);
    glBindTexture(GL_TEXTURE_2D, imageTexture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);

    _imageWidth = imageWidth;
    _imageHeight = imageHeight;
    _imageTexture = imageTexture;
}
