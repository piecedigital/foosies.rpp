#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    bool active;

    Entity();
    ~Entity();

    virtual void update();

    virtual void render();
};

#endif
