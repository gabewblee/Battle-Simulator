#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
public:
    int HP;
    int range;
    int damagePoints;
    int movementCost;

    Unit(int team, int x, int y, int HP, int range, int damagePoints, int movementCost);

    int distance(Unit * target);
    bool inRange(Unit * target);
    virtual int attack(Unit * target);
    virtual std::string getType() const override;
};

#endif