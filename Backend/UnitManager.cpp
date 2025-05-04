#include <iostream>
#include <map>
#include <set>
#include "UnitManager.h"

UnitManager::UnitManager(const FieldProperties & fieldProperties) : fieldProperties(fieldProperties) { 
    loadLogicalField(fieldProperties); 
    loadEnemyUnits();
}

std::vector<std::unique_ptr<Unit>> & UnitManager::getPlayerUnits() { return this->playerUnits; }

std::vector<std::unique_ptr<Unit>> & UnitManager::getEnemyUnits() { return this->enemyUnits; }

void UnitManager::addUnit(unsigned int team, unsigned int x, unsigned int y) {
    if (x >= this->fieldProperties.fieldDimensions.x || y >= this->fieldProperties.fieldDimensions.y) {
        std::cerr << "Invalid coordinates for unit placement" << std::endl;
        return;
    } 
    
    if (!this->logicalField[y][x].canPlace()) {
        std::cerr << "Invalid unit placement coordinates" << std::endl;
        return;
    }

    std::unique_ptr<Unit> newUnit = std::make_unique<Unit>(team, x, y, 100, 5, 10, 2);
    this->logicalField[y][x].setOccupant(newUnit.get());
    if (team == 0) this->playerUnits.push_back(std::move(newUnit));
    else this->enemyUnits.push_back(std::move(newUnit));
}

void UnitManager::removeUnit(Unit * unit) {
    Tile & tile = this->logicalField[unit->y][unit->x];

    if (!tile.isOccupied()) {
        std::cerr << "No unit to remove at the specified coordinates" << std::endl;
        return;
    }

    for (auto & targetingUnit : unit->attackingUnits) {
        targetingUnit->enemy = nullptr;
        targetingUnit->enemyPath.clear();
    }
    unit->attackingUnits.clear(); 

    Entity * deleteUnit = tile.getOccupant();
    std::vector<std::unique_ptr<Unit>> & units = (unit->team == 0) ? this->playerUnits : this->enemyUnits;

    for (int i = 0; i < units.size(); i++) {
        if (units[i].get() == deleteUnit) {
            units.erase(units.begin() + i);
            tile.setOccupant(nullptr);
            return;
        }
    }

    std::cerr << "Could not delete unit from units vector" << std::endl;
}

void UnitManager::moveUnit(unsigned int srcX, unsigned int srcY, unsigned int destX, unsigned int destY) {
    if (srcX >= this->fieldProperties.fieldDimensions.x || srcY >= this->fieldProperties.fieldDimensions.y) {
        std::cerr << "Invalid source coordinates" << std::endl;
        return;
    }

    if (destX >= this->fieldProperties.fieldDimensions.x || destY >= this->fieldProperties.fieldDimensions.y) {
        std::cerr << "Invalid destination coordinates" << std::endl;
        return;
    }

    Tile & srcTile = this->logicalField[srcY][srcX];
    Tile & destTile = this->logicalField[destY][destX];

    if (!srcTile.isOccupied() || destTile.isOccupied()) {
        return;
    }

    Entity * displacedUnit = srcTile.getOccupant();
    srcTile.setOccupant(nullptr);
    destTile.setOccupant(displacedUnit);
    displacedUnit->x = destX;
    displacedUnit->y = destY;
}

void UnitManager::loadLogicalField(const FieldProperties & fieldProperties) {
    unsigned int width = fieldProperties.fieldDimensions.x;
    unsigned int height = fieldProperties.fieldDimensions.y;

    Tile tile(Terrain::EMPTY);
    std::vector<Tile> row(width, tile);
    this->logicalField = std::vector<std::vector<Tile>>(height, row);

    const auto & layers = fieldProperties.battlefield.getLayers();
    for (const auto & layer : layers) {
        std::string layerName = layer->getName();

        Terrain terrain;
        if (layerName == "Road") terrain = Terrain::ROAD;
        else if (layerName == "Side Walk") terrain = Terrain::SIDEWALK;
        else if (layerName == "Tree") terrain = Terrain::TREE;
        else if (layerName == "Building") terrain = Terrain::BUILDING;
        else continue;

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

void UnitManager::loadEnemyUnits() {
    addUnit(1, this->fieldProperties.fieldDimensions.x - 1, this->fieldProperties.fieldDimensions.y - 1);
    addUnit(1, this->fieldProperties.fieldDimensions.x - 1, 0);
    addUnit(1, 0, this->fieldProperties.fieldDimensions.y - 1);
}

std::vector<std::pair<int, int>> UnitManager::reconstructPath(std::map<std::pair<int, int>, std::pair<int, int>> ancestors, std::pair<int, int> curr) {
    std::vector<std::pair<int, int>> path;
    while (curr.first != -1 || curr.second != -1) {
        path.emplace_back(curr.first, curr.second);
        curr = ancestors[curr];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

bool UnitManager::inBounds(unsigned int x, unsigned int y) {
    return 0 <= x && x < this->fieldProperties.fieldDimensions.x && 0 <= y && y < this->fieldProperties.fieldDimensions.y;
}

void UnitManager::BFS(Unit * playerUnit) {
    std::pair<int, int> start = {playerUnit->x, playerUnit->y};
    std::queue<std::pair<int, int>> frontier;
    std::set<std::pair<int, int>> visited;
    std::map<std::pair<int, int>, std::pair<int, int>> ancestors;
    std::vector<std::pair<int, int>> validDirections = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    frontier.push(start);
    visited.insert(start);
    ancestors[start] = {-1, -1};

    while (!frontier.empty()) {
        std::pair<int, int> curr = frontier.front();
        frontier.pop();
        Tile & tile = this->logicalField[curr.second][curr.first];
        if (tile.isOccupied() && tile.getOccupant()->team != playerUnit->team) {
            std::vector<std::pair<int, int>> path = reconstructPath(ancestors, curr);
            Unit * enemy = (Unit *) tile.getOccupant();
            playerUnit->setEnemy(enemy);
            playerUnit->setEnemyPath(path);
            enemy->addAttackingUnit(playerUnit);
            return;
        }

        for (auto [dx, dy] : validDirections) {
            int x = curr.first + dx;
            int y = curr.second + dy;
            if (inBounds(x, y) && this->logicalField[y][x].canPass() && !visited.count({x, y})) {
                visited.insert({x, y});
                frontier.push({x, y});
                ancestors[{x, y}] = curr;
            }
        }
    }
}

void UnitManager::search() {
    for (auto & unit : this->playerUnits) {
        if (!unit->enemyPath.empty()) continue;
        BFS(unit.get());
    }
}

void UnitManager::update() {
    for (auto & unit : this->playerUnits) {
        if (unit->enemyPath.empty()) continue;
        std::pair<int, int> next = unit->enemyPath.front();
        unit->enemyPath.erase(unit->enemyPath.begin());

        if (unit->inRange(unit->enemy)) {
            unit->attack(unit->enemy);
            if (unit->enemy->isDead()) removeUnit(unit->enemy);
        } else {
            moveUnit(unit->x, unit->y, next.first, next.second);
        }
    }
}