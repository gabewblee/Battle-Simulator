#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    int team;
    int x;
    int y;

    Entity(unsigned int team, unsigned int x, unsigned int y);
    virtual ~Entity() = default;
};

#endif