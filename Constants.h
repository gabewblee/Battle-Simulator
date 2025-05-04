#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

enum class ViewID {
    TITLE,
    GAMEMODE,
    URBANFIELD,
    RURALFIELD,
    UNDERGROUNDFIELD
};

enum class Terrain {
    EMPTY,
    ROAD,
    SIDEWALK,
    TREE,
    BUILDING
};

enum class UnitType {
    NONE,
    SOLDIER,
    DRONE,
    TANK
};

struct FieldProperties {
    tmx::Map battlefield;
    tmx::Vector2u fieldDimensions;
    tmx::Vector2u tileDimensions;
    float fieldWidth;
    float fieldHeight;
    float offsetX;
    float offsetY;
    unsigned int margin;
    unsigned int spacing;
    sf::Texture tileset;
};



// static const std::vector<std::string> unitLabels = {"Soldier", "Drone", "Tank"};
// static const std::unordered_map<std::string, UnitType> unitLabelToType= {{"Soldier", UnitType::SOLDIER}, {"Drone", UnitType::DRONE}, {"Tank", UnitType::TANK}};
// static const std::unordered_map<std::string, Terrain> layerToTerrain = {{"Road", Terrain::ROAD}, {"Side Walk", Terrain::SIDEWALK}, {"Tree", Terrain::TREE}, {"Building", Terrain::BUILDING}};
// static const std::string fontPath = "Frontend/Fonts/CallOfOpsDuty.otf";

#endif