#ifndef SOLDIER_H
#define SOLDIER_H

#include "Unit.h"

class Soldier : public Unit {
public:
    Soldier(int team, int x, int y);

    int distance(Unit * target);
    bool inRange(Unit * target);
    int attack(Unit * target);
};

#endif
