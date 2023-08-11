#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(EntityManager& _manager) : manager(_manager) {  }

Entity::Entity(EntityManager &_manager, unsigned int _id, std::string  _name, LayerType _layer)
    : manager(_manager), id(_id), name(std::move( _name )), layer(_layer) {  }

Entity::~Entity() { destroy(); }

void Entity::initialize() {
    for ( auto& component : components ) {
        component->initialize();
    }
}

void Entity::update(float deltaTime) {
    for ( auto& component : components ) {
        component->update(deltaTime);
    }
}

void Entity::render() {
    for ( auto& component : components ) {
        component->render();
    }
}

void Entity::destroy() {
    for ( auto& component : components ) {
        delete component;
    }
}

unsigned int Entity::ID() const { return id; }
