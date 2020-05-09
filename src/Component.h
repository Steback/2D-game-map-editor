#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
    public:
        Entity* owner{};
        virtual ~Component() = default;
        virtual void initialize() = 0;
        virtual void render() = 0;
};

#endif
