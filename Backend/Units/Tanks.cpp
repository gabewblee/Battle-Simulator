#include "Tanks.h"

Tanks::Tanks(int ID, int team, int x, int y) : Unit(ID, team, x, y, 500, 10, 10, 10) {}

int Tanks::distance(Unit * target) { return Unit::distance(target); }
bool Tanks::inRange(Unit * target) { return Unit::inRange(target); }
int Tanks::attack(Unit * target) { return Unit::attack(target); }