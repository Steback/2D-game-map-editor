#include "EntityManager.h"
#include "Entity.h"

EntityManager::~EntityManager() {
    for ( auto & entity : entities ) {
        delete entity;
    }

    entities.clear();
}

void EntityManager::render() const {
    for ( int layerNumber  = 0; layerNumber < NUM_LAYERS; layerNumber++ ) {
        for ( auto& entity : getEntitiesLayer( static_cast<LayerType>(layerNumber) ) ) {
            entity->render();
        }
    }
}

Entity& EntityManager::addEntity(const std::string& _entityName, LayerType _layer) {
    auto* entity = new Entity(*this, _entityName, _layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const { return entities; }

unsigned int EntityManager::getEntityCount() const { return entities.size(); }

Entity* EntityManager::getEntityByName(const std::string& entityName) const {
    for ( auto* entity: entities ) {
        if ( entity->name == entityName ) {
            return entity;
        }
    }

    return nullptr;
}

std::vector<Entity *> EntityManager::getEntitiesLayer(LayerType _layer) const {
    std::vector<Entity*> selectedEntities;

    for ( auto& entity : entities ) {
        if ( entity->layer == _layer) {
            selectedEntities.emplace_back(entity);
        }
    }

    return selectedEntities;
}