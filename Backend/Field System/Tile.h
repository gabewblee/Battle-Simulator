#ifndef TILE
#define TILE

#include "../Units/Entity.h"
#include "../../Constants.h"
#include <limits>

class Tile {
public:
    Terrain terrain;
    Entity * occupant;
    Tile(Terrain terrain, Entity * occupant = nullptr);

    void setOccupant(Entity * occupant);
    Entity * getOccupant();
    bool isOccupied();
    bool traversible();
    bool placeable();
};

#endif