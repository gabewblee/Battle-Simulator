#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Views/View.h"
#include "Views/TitleView.h"
#include "Views/GameModeView.h"
#include "Views/BattlefieldView.h"

class ViewManager {
public:
    ViewManager(unsigned int width, unsigned int height);

private:
    sf::RenderWindow window;
    unsigned int width;
    unsigned int height;
    sf::Font font;
    std::vector<std::unique_ptr<View>> views;
    View * currView;

    void run();
    void eventHandler(const std::optional<sf::Event> event);
    void switchView(ViewID newState);
    void loadFont(std::string fontPath);
    void loadViews();
};

#endif