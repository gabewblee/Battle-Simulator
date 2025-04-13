#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <algorithm>

class Entity {
public:
    int team;
    int x;
    int y;
    Entity(int team, int x, int y) {
        this->team = team;
        this->x = x;
        this->y = y;
    }
    virtual ~Entity() {}
    virtual std::string getType() const = 0;
};

#endif