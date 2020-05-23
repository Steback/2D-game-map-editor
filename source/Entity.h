#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>

#include "Constants.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"

class EntityManager;
class Component;

class Entity {
    public:
        explicit Entity(EntityManager& _manager);
        Entity(EntityManager& _manager, std::string  _name, LayerType _layer);
        ~Entity();
        void initialize();
        void update(float deltaTime);
        void render();
        void destroy();

        template <typename T, typename... Targs>
        T& addComponent(Targs&&... args) {
            T* newComponent = new T( std::forward<Targs>(args)... );

            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentType[&typeid(*newComponent)] = newComponent;
            newComponent->initialize();

            return *newComponent;
        }

        std::string name{};
        LayerType layer{};

    private:
        EntityManager& manager;
        std::map<const std::type_info*, Component*> componentType;
        std::vector<Component*> components;
};

#endif
