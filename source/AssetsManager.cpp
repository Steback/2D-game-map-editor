#include "AssetsManager.h"

std::vector<std::string> AssetsManager::texturesNames;

AssetsManager::AssetsManager() = default;

AssetsManager::~AssetsManager() = default;

void AssetsManager::addTexture(const std::string& _textureID, const std::string& _filePath) {
    textures.emplace(_textureID, std::make_shared<TextureManager>(_filePath));
}

std::shared_ptr<TextureManager> AssetsManager::getTexture(const std::string& _textureID) { return textures[_textureID]; }

void AssetsManager::loadTextures() {
    for ( auto& texture : textures ) {
        texture.second->loadTexture();
    }
}