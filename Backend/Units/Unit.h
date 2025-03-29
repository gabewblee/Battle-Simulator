#ifndef UNIT
#define UNIT

#include <algorithm>
#include <iostream>

class Unit {
public:
    int ID;
    int team;
    int position[2];
    int HP;
    int range;
    int damagePoints;

    Unit(int ID, int team, int position[2], int HP, int range, int damagePoints) {
        this->ID = ID;
        this->team = team;
        this->position[0] = position[0];
        this->position[1] = position[1];
        this->HP = HP;
        this->range = range;
        this->damagePoints = damagePoints;
    }

    int distance(Unit * target) {
        int horDiff = std::abs(this->position[0] - target->position[0]);
        int verDiff = std::abs(this->position[1] - target->position[1]);
        return horDiff + verDiff;
    }

    bool inRange(Unit * target) {
        if (distance(target) <= this->range) {
            return true;
        }
        return false;
    }

    int attack(Unit * target) {
        int damage = std::min(this->damagePoints, target->HP);
        if (inRange(target)) {
            target->HP -= damage;
        }
        return damage;
    }
};

#endif