#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include <vector>
#include <iostream>
#include <map>
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "Field System/Tile.h"
#include "Units/Unit.h"
#include "Units/Soldier.h"
#include "Units/Drone.h"
#include "Units/Tank.h"
#include "../Constants.h"

class UnitManager {
public:
    UnitManager() = default;
    UnitManager(const FieldProperties & fieldProperties);

    bool addUnit(UnitCard * unitCard, unsigned int team, unsigned int x, unsigned int y);
    const std::vector<std::unique_ptr<Unit>> & getUserUnits() const;
    const std::map<UnitType, int> & getUnitBar() const;

private:
    unsigned int width;
    unsigned int height;
    std::vector<std::vector<Tile>> logicalField;
    std::vector<std::unique_ptr<Unit>> userUnits;
    std::map<UnitType, int> unitBar;

    bool requirementsSatisfied(UnitCard * unitCard, unsigned int x, unsigned int y);
    void initializeLogicalField(const FieldProperties & fieldProperties);
    void makeLogicalField(const FieldProperties & fieldProperties);
    bool withinBounds(unsigned int x, unsigned int y);
    void initializeUnitBar();
};

#endif