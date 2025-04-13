#include "Soldier.h"

Soldier::Soldier(int team, int x, int y) : Unit(team, x, y, 50, 10, 5, 2) {}

int Soldier::distance(Unit * target) { return Unit::distance(target); }

bool Soldier::inRange(Unit * target) { return Unit::inRange(target); }

int Soldier::attack(Unit * target) { return Unit::attack(target); }