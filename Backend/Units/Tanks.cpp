#include "Unit.h"

class Tanks: public Unit {
public:
    int HP;
    int range;
    int damagePoints;
    
    Tanks(int ID, int team, int position[2]) : Unit(ID, team, position) {
        this->HP = 500;
        this->range = 10;
        this->damagePoints = 10;
    }
};