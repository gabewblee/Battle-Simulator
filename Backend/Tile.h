#ifndef TILE
#define TILE

#include "Units/Entity.h"

enum TYPE {
    ROAD,
    SIDEWALK,
    BUILDING,
    PARK
};

class Tile {
public:
    TYPE terrain;
    Entity * occupant;
    Tile(TYPE terrain, Entity * occupant = nullptr) {
        this->terrain = terrain;
        this->occupant = occupant;
    }

    void setOccupant(Entity * occupant) {
        this->occupant = occupant;
    }

    Entity * getOccupant() {
        return this->occupant;
    }

    bool isOccupied() {
        return this->occupant != nullptr;
    }
};

#endif