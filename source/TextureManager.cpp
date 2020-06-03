#include <iostream>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "TextureManager.h"

TextureManager::TextureManager(std::string  _filePath) : filePath(std::move(_filePath)) {  }

TextureManager::~TextureManager() { clearTexture(); };

bool TextureManager::loadTexture() {
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, nullptr, 4);

    if ( !imageData ) {
        std::cerr << "Fail load image" << '\n';
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);

    return true;
}

void TextureManager::useTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint TextureManager::getTextureID() const { return textureID; }

int TextureManager::getWidth() const { return width; }

int TextureManager::getHeight() const { return height; }

void TextureManager::clearTexture() { glDeleteTextures(1, &textureID); }