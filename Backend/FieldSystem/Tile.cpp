#include "Tile.h"
#include <iostream>

Tile::Tile(Terrain terrain, Entity * occupant) : terrain(terrain), occupant(occupant) {}

void Tile::setOccupant(Entity * occupant) { this->occupant = occupant; }
Entity * Tile::getOccupant() { return this->occupant; }
bool Tile::isOccupied() { return this->occupant != nullptr; }
bool Tile::canPass() { return this->terrain != Terrain::BUILDING; }
bool Tile::canPlace() { return this->terrain != Terrain::BUILDING && !isOccupied(); }
