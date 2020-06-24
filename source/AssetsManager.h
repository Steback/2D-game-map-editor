#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <map>
#include <memory>
#include <vector>

#include "TextureManager.h"

class AssetsManager {
    public:
        AssetsManager();
        ~AssetsManager();
        void addTexture(const std::string& _textureID, const std::string& _filePath);
        std::shared_ptr<TextureManager> getTexture(const std::string& _textureID);
        static std::vector<std::string> texturesNames;

    private:
        std::map<std::string, std::shared_ptr<TextureManager> > textures;
};

#endif
