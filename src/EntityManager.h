#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <string>

#include "Component.h"
#include "Constants.h"

class Entity;

class EntityManager {
    public:
        ~EntityManager();
        void render() const;
        Entity& addEntity(const std::string& _entityName, LayerType _layer);
        std::vector<Entity*> getEntities() const;
        std::vector<Entity*> getEntitiesLayer(LayerType _layer) const;
        unsigned int getEntityCount() const;
        Entity* getEntityByName(const std::string& entityName) const;

    private:
        std::vector<Entity*> entities;
};

#endif
