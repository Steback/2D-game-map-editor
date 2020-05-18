#include "AssetsManager.h"

AssetsManager::AssetsManager() = default;

AssetsManager::~AssetsManager() = default;

void AssetsManager::addTexture(const std::string& _texutreID, const std::string& _filePath) {
    textures.emplace(_texutreID, std::make_shared<TextureManager>(_filePath));
}

std::shared_ptr<TextureManager> AssetsManager::getTexture(const std::string& _texutreID) { return textures[_texutreID]; }