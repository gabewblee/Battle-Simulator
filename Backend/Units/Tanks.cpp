#include "Unit.h"

class Tanks: public Unit {
public:
    int HP;
    int range;
    int damagePoints;

    Tanks(int ID, int team, int x, int y) : Unit(ID, team, x, y, 500, 10, 10, 10) {}

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