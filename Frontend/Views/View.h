#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../../Constants.h"

class View {
public:
    sf::Font & font;    
    ViewID state;
    unsigned int width;
    unsigned int height;

    View(sf::Font & font, ViewID state, const unsigned int width, const unsigned int height);
    virtual ~View() = default;

    virtual ViewID handleEvent(const std::optional<sf::Event> & event, ViewID currState) = 0;
    virtual void drawComponents(sf::RenderWindow & window) = 0;
};

#endif