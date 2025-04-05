#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <string>

class View {
public:
    View(sf::Font & font, const unsigned int state, const unsigned int width, const unsigned int height);
    virtual ~View() = default;
    unsigned int state;
    virtual void draw(sf::RenderWindow & window) = 0;
    virtual unsigned int handleEvent(const std::optional<sf::Event> & event, unsigned int currState) = 0;
    
protected:
    sf::Font & font;
    unsigned int width;
    unsigned int height;
    virtual void loadTexts() = 0;
    void loadText(sf::Text& text, const std::string& title, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif