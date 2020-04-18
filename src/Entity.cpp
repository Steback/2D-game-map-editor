#include "Entity.h"

#include "EntityManager.h"

Entity::Entity(EntityManager& _manager) : manager(_manager) {  }

Entity::Entity(EntityManager &_manager, std::string  _name, LayerType _layer) : manager(_manager), name(std::move( _name )), layer(_layer) {  }

Entity::~Entity() {
    for ( auto& component : components ) {
        delete component;
    }
}


void Entity::render() {
    for ( auto& component : components ) {
        component->render();
    }
}


template <typename T, typename... Targs>
T& Entity::addComponent(Targs&&... args) {
    T* newComponent( new T( std::forward<Targs>(args)... ) );

    newComponent->owner = this;
    components.emplace_back(newComponent);
    componentType[&typeid(*newComponent)] = newComponent;
    newComponent->initialize();

    return *newComponent;
}

template <typename T>
bool Entity::hasComponent() const { return componentType.count( &typeid(T) ); };

template <typename T>
T* Entity::getComponent() { return static_cast<T*>(componentType[&typeid(T)]); }