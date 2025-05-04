#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include <vector>
#include "FieldSystem/Tile.h"
#include "Units/Unit.h"
#include "../Constants.h"

class UnitManager {
public:
    UnitManager(const FieldProperties & fieldProperties);
    ~UnitManager() = default;

    std::vector<std::unique_ptr<Unit>> & getPlayerUnits();
    std::vector<std::unique_ptr<Unit>> & getEnemyUnits();
    void addUnit(unsigned int team, unsigned int x, unsigned int y);
    void removeUnit(Unit * unit);
    void moveUnit(unsigned int srcX, unsigned int srcY, unsigned int destX, unsigned int destY);
    void search();
    void update();

private:
    const FieldProperties & fieldProperties;
    std::vector<std::vector<Tile>> logicalField;
    std::vector<std::unique_ptr<Unit>> playerUnits;
    std::vector<std::unique_ptr<Unit>> enemyUnits;

    void loadLogicalField(const FieldProperties & fieldProperties);
    void loadEnemyUnits();
    std::vector<std::pair<int, int>> reconstructPath(std::map<std::pair<int, int>, std::pair<int, int>> ancestors, std::pair<int, int> curr);
    bool inBounds(unsigned int x, unsigned int y);
    void BFS(Unit * playerUnit);
};

#endif