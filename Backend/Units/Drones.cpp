#include "Unit.h"

class Drones: public Unit {
public:
    int HP;
    int range;
    int damagePoints;

    Drones(int ID, int team, int position[2]) : Unit(ID, team, position, 10, 10, 5, 1) {}

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