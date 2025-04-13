#include "Buildings.h"

Building::Building(int team, int x, int y) : Entity(team, x, y) {}

std::string Building::getType() const { return "Building"; }