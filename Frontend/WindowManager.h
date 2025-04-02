#ifndef WINDOWMANAGER
#define WINDOWMANAGER

#include <SFML/Graphics.hpp>
#include <vector>
#include "View.h"
#include "TitleView.h"
#include "../Constants.h"

class WindowManager {
public:
    WindowManager(unsigned int width, unsigned int height);
    
    void run();
    void eventHandler(const std::optional<sf::Event> event);

private:
    unsigned int width;
    unsigned int height;
    ViewState currState;
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::unique_ptr<View>> views;
    View * currView;

    void switchView(ViewState newState);
};

#endif