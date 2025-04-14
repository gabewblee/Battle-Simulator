#include "UnitManager.h"

UnitManager::UnitManager(const FieldProperties & fieldProperties) 
: width(fieldProperties.fieldDimensions.x), height(fieldProperties.fieldDimensions.y) { 
    initializeLogicalField(fieldProperties);
    makeLogicalField(fieldProperties); 
    initializeUnitBar();
}

bool UnitManager::addUnit(UnitCard * unitCard, unsigned int team, unsigned int x, unsigned int y) {
    if (!requirementsSatisfied(unitCard, x, y)) return false;

    std::unique_ptr<Unit> unit;
    switch(unitCard->type) {
        case UnitType::SOLDIER:
            unit = std::make_unique<Soldier>(team, x, y);
            break;
        case UnitType::DRONE:
            unit = std::make_unique<Drone>(team, x, y);
            break;
        case UnitType::TANK:
            unit = std::make_unique<Tank>(team, x, y);
            break;
        default:
            std::cerr << "Invalid unit type\n";
            return false;
    }
    this->logicalField[y][x].setOccupant(unit.get());
    userUnits.emplace_back(std::move(unit));
    this->unitBar[unitCard->type]--;
    return true;
}

const std::vector<std::unique_ptr<Unit>> & UnitManager::getUserUnits() const { return this->userUnits; }

const std::map<UnitType, int> & UnitManager::getUnitBar() const { return this->unitBar; }

bool UnitManager::requirementsSatisfied(UnitCard * unitCard, unsigned int x, unsigned int y) {
    if (!withinBounds(x, y)) return false;
    Tile & tile = this->logicalField[y][x];
    return !tile.isOccupied() && tile.placeable() && this->unitBar[unitCard->type] != 0;
}

void UnitManager::initializeLogicalField(const FieldProperties & fieldProperties) {
    unsigned int width = fieldProperties.fieldDimensions.x;
    unsigned int height = fieldProperties.fieldDimensions.y;
    Tile tile(Terrain::NONE);
    std::vector<Tile> row(width, tile);
    this->logicalField = std::vector<std::vector<Tile>>(height, row);
}

void UnitManager::makeLogicalField(const FieldProperties & fieldProperties) {
    const auto & layers = fieldProperties.battlefield.getLayers();
    for (const auto & layer : layers) {
        std::string layerName = layer->getName();

        auto iter = layerToTerrain.find(layerName);
        if (iter == layerToTerrain.end()) continue;
        Terrain terrain = iter->second;

        const auto & tileLayer = layer->getLayerAs<tmx::TileLayer>();
        const auto & tiles = tileLayer.getTiles();

        for (unsigned int y = 0; y < fieldProperties.fieldDimensions.y; y++) {
            for (unsigned int x = 0; x < fieldProperties.fieldDimensions.x; x++) {
                std::size_t idx = x + y * fieldProperties.fieldDimensions.x;
                if (tiles[idx].ID == 0) continue;
                this->logicalField[y][x] = Tile(terrain);
            }
        }
    }
}

bool UnitManager::withinBounds(unsigned int x, unsigned int y) { return (0 <= x && x < this->width) && (0 <= y && y < this->height); }

void UnitManager::initializeUnitBar() {
    this->unitBar[UnitType::SOLDIER] = 10;
    this->unitBar[UnitType::DRONE] = 5;
    this->unitBar[UnitType::TANK] = 2;
}