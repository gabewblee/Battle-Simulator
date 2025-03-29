#include "Unit.h"

class Soldiers: public Unit {
public:
    int HP;
    int range;
    int damagePoints;
    
    Soldiers(int ID, int team, int position[2]) : Unit(ID, team, position) {
        this->HP = 50;
        this->range = 10;
        this->damagePoints = 5;
    }
};