#include "Buildings.h"

Building::Building(int ID, int team, int x, int y) : Entity(ID, team, x, y) {}

std::string Building::getType() const { return "Building"; }