#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>

#include "Constants.h"

class EntityManager;
class Component;

class Entity {
    public:
        explicit Entity(EntityManager& _manager);
        Entity(EntityManager& _manager, std::string  _name, LayerType _layer);
        ~Entity();
        void render();
        void destroy();
        void listAllComponents() const;

        template <typename T, typename... Targs>
        T& addComponent(Targs&&... args);

        template <typename T>
        bool hasComponent() const;

        template <typename T>
        T* getComponent();

        std::string name;
        LayerType layer;

    private:
        EntityManager& manager;
        std::map<const std::type_info*, Component*> componentType;
        std::vector<Component*> components;
};

#endif
