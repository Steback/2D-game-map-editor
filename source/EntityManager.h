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
        void destroy();
        Entity& addEntity(const unsigned int& id, const std::string& _entityName, LayerType _layer);
        std::vector<Entity*> getEntitiesLayer(LayerType _layer) const;
        Entity* getEntityByID(const unsigned int& id) const;
        unsigned int entitiesCount() const;

private:
        std::vector<Entity*> entities;
};

#endif
