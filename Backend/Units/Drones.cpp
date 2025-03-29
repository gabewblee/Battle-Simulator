#include "Unit.h"

class Drones: public Unit {
public:
    int HP;
    int range;
    int damagePoints;
    
    Drones(int ID, int team, int position[2]) : Unit(ID, team, position) {
        this->HP = 10;
        this->range = 10;
        this->damagePoints = 5;
    }
};