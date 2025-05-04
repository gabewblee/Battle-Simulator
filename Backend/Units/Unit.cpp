#include <iostream>
#include "Unit.h"
    
Unit::Unit(unsigned int team, unsigned int x, unsigned int y, unsigned int HP, unsigned int range, unsigned int damagePoints, unsigned int movementCost) 
    : HP(HP), range(range), damagePoints(damagePoints), movementCost(movementCost), enemy(nullptr), Entity(team, x, y) {}

void Unit::setEnemy(Unit * enemy) { this->enemy = enemy; }

void Unit::setEnemyPath(std::vector<std::pair<int, int>> & enemyPath) { this->enemyPath = enemyPath; }

void Unit::addAttackingUnit(Unit * unit) { this->attackingUnits.push_back(unit); }

void Unit::removeAttackingUnit(Unit * unit) { this->attackingUnits.erase(std::remove(this->attackingUnits.begin(), this->attackingUnits.end(), unit), this->attackingUnits.end());}

bool Unit::inRange(Unit * target) {
    unsigned int manhattanDistance = abs((int) this->x - (int) target->x) + abs((int) this->y - (int) target->y);
    return manhattanDistance <= this->range;
}

void Unit::attack(Unit * target) { target->HP -= this->damagePoints; }

bool Unit::isDead() { return this->HP <= 0; }