#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Views/View.h"
#include "Views/TitleView.h"
#include "Views/SelectionView.h"

class WindowManager {
public:
    WindowManager(unsigned int width, unsigned int height);
    
    void run();
    void eventHandler(const std::optional<sf::Event> event);

private:
    unsigned int width;
    unsigned int height;

    sf::RenderWindow window;

    sf::Font font;
    View * currView;
    std::vector<std::unique_ptr<View>> views;

    void switchView(unsigned int newState);
};

#endif