#ifndef ENTITY
#define ENTITY

#include <string>
#include <algorithm>

class Entity {
public:
    int ID;
    int team;
    int x;
    int y;
    Entity(int ID, int team, int x, int y) {
        this->ID = ID;
        this->team = team;
        this->x = x;
        this->y = y;
    }
    virtual ~Entity() {}
    virtual std::string getType() const = 0;
};

#endif