#ifndef TANK_H
#define TANK_H

#include "Unit.h"

class Tank : public Unit {
public:
    Tank(int team, int x, int y);

    int distance(Unit * target);
    bool inRange(Unit * target);
    int attack(Unit * target);
};

#endif