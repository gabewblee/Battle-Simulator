#include "Unit.h"

class Tanks: public Unit {
public:
    int HP;
    int range;
    int damagePoints;

    Tanks(int ID, int team, int x, int y);

    int distance(Unit * target);
    bool inRange(Unit * target);
    int attack(Unit * target);
};