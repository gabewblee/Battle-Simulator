#include "Unit.h"

class Soldiers: public Unit {
public:
    int HP;
    int range;
    int damagePoints;

    Soldiers(int ID, int team, int position[2]) : Unit(ID, team, position, 50, 10, 5, 2) {}

    int distance(Unit * target) {
        return Unit::distance(target);
    }

    bool inRange(Unit * target) {
        return Unit::inRange(target);
    }

    int attack(Unit * target) {
        return Unit::attack(target);
    }
};