#include "Unit.h"
#include <iostream>
    
Unit::Unit(int team, int x, int y, int HP, int range, int damagePoints, int movementCost) : Entity(team, x, y) {
    this->HP = HP;
    this->range = range;
    this->damagePoints = damagePoints;
    this->movementCost = movementCost;
}

int Unit::distance(Unit * target) {
    int horDiff = std::abs(this->x - target->x);
    int verDiff = std::abs(this->y - target->y);
    return horDiff + verDiff;
}

bool Unit::inRange(Unit * target) {
    return distance(target) <= this->range;
}

int Unit::attack(Unit * target) {
    int damage = std::min(this->damagePoints, target->HP);
    if (inRange(target)) {
        target->HP -= damage;
    }
    return damage;
}

std::string Unit::getType() const {
    return "Unit";
}