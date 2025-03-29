#ifndef UNIT
#define UNIT

class Unit {
public:
    int ID;
    int team;
    int position[2];
    
    Unit(int ID, int team, int position[2]) {
        this->ID = ID;
        this->team = team;
        this->position[0] = position[0];
        this->position[1] = position[1];
    }

    int attack(Unit target) {

    }
};

#endif