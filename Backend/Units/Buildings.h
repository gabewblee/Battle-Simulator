#ifndef BUILDING
#define BUILDING

#include "Entity.h"

class Building : public Entity {
public:
    Building(int ID, int team, int x, int y) : Entity(ID, team, x, y) {}

    std::string getType() {
        return "Building";
    }
};

#endif