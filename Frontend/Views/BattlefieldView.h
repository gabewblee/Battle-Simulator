#ifndef BATTLEFIELD_VIEW_H
#define BATTLEFIELD_VIEW_H

#include "View.h"
#include "../../Backend/UnitManager.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <string>
#include <iostream>

struct FieldProperties {
    tmx::Map battlefield;
    tmx::Vector2u fieldDimensions;
    tmx::Vector2u tileDimensions;
    float fieldWidth;
    float fieldHeight;
    unsigned int margin;
    unsigned int spacing;
    sf::Texture tileset;
};

class BattlefieldView : public View {
public:
    BattlefieldView(sf::Font & font, ViewID state, unsigned int width, unsigned int height);
    ~BattlefieldView() override = default;

    ViewID handleEvent(const std::optional<sf::Event> & event, ViewID currState) override;
    void drawComponents(sf::RenderWindow & window) override;

private:
    UnitManager unitManager;
    FieldProperties properties;

    void loadProperties(std::string mapPath);
    void placeField(sf::RenderWindow & window);
};

#endif