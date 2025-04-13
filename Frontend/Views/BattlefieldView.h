#ifndef BATTLEFIELD_VIEW_H
#define BATTLEFIELD_VIEW_H

#include "View.h"
#include "../../Backend/UnitManager.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <string>
#include <iostream>

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
    void drawField(sf::RenderWindow & window);
    void drawUnits(sf::RenderWindow & window);
    void drawUnitBar(sf::RenderWindow & window);
    std::pair<float, float> getPixelCoordinates(unsigned int x, unsigned int y);
    std::pair<int, int> getTileCoordinates(unsigned int x, unsigned int y);
};

#endif