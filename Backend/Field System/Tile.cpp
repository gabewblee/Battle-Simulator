#include "Tile.h"

Tile::Tile(Terrain terrain, Entity * occupant) : terrain(terrain), occupant(occupant) {}

void Tile::setOccupant(Entity * occupant) {
    this->occupant = occupant;
}

Entity * Tile::getOccupant() { return this->occupant; }

bool Tile::isOccupied() { return this->occupant != nullptr; }

bool Tile::traversible() { return this->terrain != Terrain::BUILDING; }

bool Tile::placeable() { return this->terrain != Terrain::BUILDING; }