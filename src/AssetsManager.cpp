#include "AssetsManager.h"

AssetsManager::AssetsManager() = default;

AssetsManager::~AssetsManager() {
    for ( auto& texture : textures ) {
        delete texture.second;
    }
}

void AssetsManager::addTexture(const std::string& _texutreID, const std::string& _filePath) {
    auto* texture = new TextureManager(_filePath);
    textures.emplace(_texutreID, texture);
}

TextureManager* AssetsManager::getTexture(const std::string& _texutreID) { return textures[_texutreID]; }