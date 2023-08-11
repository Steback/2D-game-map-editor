#include "EntityManager.h"
#include "Entity.h"

EntityManager::~EntityManager() { destroy(); }

void EntityManager::initialize() {
    for ( auto& entity : entities ) {
        entity->initialize();
    }
}

void EntityManager::update(float deltaTime) {
    for ( auto& entity : entities ) {
        entity->update(deltaTime);
    }
}

void EntityManager::render() const {
    for ( int layerNumber  = 0; layerNumber < NUM_LAYERS; layerNumber++ ) {
        for ( auto& entity : getEntitiesLayer( static_cast<LayerType>(layerNumber) ) ) {
            entity->render();
        }
    }
}

void EntityManager::destroy() {
    for ( auto & entity : entities ) {
        delete entity;
    }

    entities.clear();
}

Entity& EntityManager::addEntity(const unsigned int& id, const std::string& _entityName, LayerType _layer) {
    auto* entity = new Entity(*this, id, _entityName, _layer);
    entities.emplace_back(entity);
    return *entity;
}

Entity *EntityManager::getEntityByID(const unsigned int &id) const {
    if ( !entities.empty() ) {
        return entities[id - 1];
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

unsigned int EntityManager::entitiesCount() const { return entities.size(); }