#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <vector>

class Unit : public Entity {
public:
    unsigned int HP;
    unsigned int range;
    unsigned int damagePoints;
    unsigned int movementCost;
    Unit * enemy;
    std::vector<std::pair<int, int>> enemyPath;
    std::vector<Unit *> attackingUnits;

    Unit(unsigned int team, unsigned int x, unsigned int y, unsigned int HP, unsigned int range, unsigned int damagePoints, unsigned int movementCost);
    ~Unit() override = default;

    void setEnemy(Unit * enemy);
    void setEnemyPath(std::vector<std::pair<int, int>> & enemyPath);
    void addAttackingUnit(Unit * unit);
    void removeAttackingUnit(Unit * unit);

    bool inRange(Unit * target);
    void attack(Unit * target);
    bool isDead();
};

#endif