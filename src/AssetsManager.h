#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>

#include "TextureManager.h"

class AssetsManager {
    public:
        AssetsManager();
        ~AssetsManager();
        void addTexture(const std::string& _texutreID, const std::string& _filePath);
        TextureManager* getTexture(const std::string& _texutreID);

    private:
        std::map<std::string, TextureManager*> textures;
};

#endif
