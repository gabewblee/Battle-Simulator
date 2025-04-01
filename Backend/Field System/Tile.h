#ifndef TILE
#define TILE

#include "Units/Entity.h"
#include <limits>

enum TYPE {
    ROAD,
    SIDEWALK,
    PARK,
    BUILDING
};

class Tile {
public:
    TYPE terrain;
    Entity * occupant;
    Tile(TYPE terrain, Entity * occupant = nullptr);

    void setOccupant(Entity * occupant);
    Entity * getOccupant();
    bool isOccupied();
    int getMovementCost();
    bool traversible();
};

#endif