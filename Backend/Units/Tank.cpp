#include "Tank.h"

Tank::Tank(int team, int x, int y) : Unit(team, x, y, 500, 10, 10, 10) {}

int Tank::distance(Unit * target) { return Unit::distance(target); }
bool Tank::inRange(Unit * target) { return Unit::inRange(target); }
int Tank::attack(Unit * target) { return Unit::attack(target); }