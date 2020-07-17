#include <fstream>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"
#include "fmt/core.h"

#include "LuaManager.h"
#include "Editor.h"
#include "EntityManager.h"
#include "Map.h"

LuaManager::LuaManager() = default;

LuaManager::~LuaManager() = default;

void LuaManager::loadFile(const std::string &_filePath) {

}

void LuaManager::writeFile(const std::string &_fileName) {
    std::fstream luaFile;
    luaFile.open(_fileName, std::ios::out);

    // Remove levels/
    int idx = _fileName.rfind('/');
    std::string fileName = _fileName.substr(idx + 1);

    // Remove .lua
    idx = fileName.rfind('.');
    int stringSize = fileName.size();

    while ( stringSize > idx ) {
        fileName.pop_back();
        stringSize--;
    }

    // Begin file
    luaFile << fileName << " =  {\n";

    // Write map info
    luaFile << "\tmap = {\n";
    luaFile << "\t\ttextureAssetId = mapTextureAssetId,\n";
    luaFile << "\t\tfile = \"" << Editor::map->getFilePath() << "\",\n";
    luaFile << "\t\tscale = " << Editor::map->getTileSize() << ",\n";
    luaFile << "\t\ttileSize = 32,\n";
    luaFile << "\t\tmapSizeX = " << Editor::map->getMapSize().x << ",\n";
    luaFile << "\t\tmapSizeY = " << Editor::map->getMapSize().y << ",\n";
    luaFile << "\t},\n";

    // End file
    luaFile << "}\n";

    luaFile.close();
}
