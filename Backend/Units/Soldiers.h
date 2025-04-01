#ifndef SOLDIERS
#define SOLDIERS

#include "Unit.h"

class Soldiers : public Unit {
public:
    int HP;
    int range;
    int damagePoints;

    Soldiers(int ID, int team, int x, int y);

    int distance(Unit * target);
    bool inRange(Unit * target);
    int attack(Unit * target);
};

#endif
