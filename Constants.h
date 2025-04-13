#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <unordered_map>

enum ViewID {
    TITLE = 0,
    GAMEMODE = 1,
    URBANFIELD = 2,
    RURALFIELD = 2,
    UNDERGROUNDFIELD = 2
};

enum Terrain {
    NONE,
    ROAD,
    SIDEWALK,
    TREE,
    BUILDING
};

enum UnitType {
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

static const std::unordered_map<std::string, Terrain> TerrainLayers = {{"Road", Terrain::ROAD}, {"Side Walk", Terrain::SIDEWALK}, {"Tree", Terrain::TREE}, {"Building", Terrain::BUILDING}};

#endif