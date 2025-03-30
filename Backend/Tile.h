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

    int getMovementCost() {
        switch (this->terrain) {
            case TYPE::ROAD:
                return 0;
            case TYPE::SIDEWALK:
                return 1;
            case TYPE::PARK:
                return 2;   
            case TYPE::BUILDING:
                return std::numeric_limits<float>::infinity();
        }
        return std::numeric_limits<float>::infinity(); // Should not get here
    }
};

#endif