#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
    public:
        Entity* owner{};
        virtual ~Component() = default;
        virtual void initialize() {  }
        virtual void render() {  }

    private:
};

#endif
