#include "Tile.h"

Tile::Tile(TYPE terrain, Entity * occupant) {
    this->terrain = terrain;
    this->occupant = occupant;
}

void Tile::setOccupant(Entity * occupant) {
    this->occupant = occupant;
}

Entity * Tile::getOccupant() {
    return this->occupant;
}

bool Tile::isOccupied() {
    return this->occupant != nullptr;
}

int Tile::getMovementCost() {
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

bool Tile::traversible() { return this->terrain != TYPE::BUILDING; }