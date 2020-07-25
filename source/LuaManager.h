#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include <string>

class LuaManager {
    public:
        LuaManager();
        ~LuaManager();
        static void loadFile(const std::string& _filePath, std::vector<unsigned int>& entitiesID);
        static void writeFile(const std::string& _fileName);

    private:
};

#endif