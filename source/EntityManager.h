#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <string>

#include "Component.h"
#include "Constants.h"

class Entity;

class EntityManager {
    public:
        ~EntityManager();
        void initialize();
        void update(float deltaTime);
        void render() const;
        void destory();
        Entity& addEntity(const std::string& _entityName, LayerType _layer);
        std::vector<Entity*> getEntities() const;
        std::vector<Entity*> getEntitiesLayer(LayerType _layer) const;
        unsigned int getEntityCount() const;
        Entity* getEntityByName(const std::string& entityName) const;

    private:
        std::vector<Entity*> entities;
};

#endif
