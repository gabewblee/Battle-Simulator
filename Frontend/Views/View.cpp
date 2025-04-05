#include "View.h"

View::View(sf::Font & font, const unsigned int state, const unsigned int width, const unsigned int height) : font(font), state(state), width(width), height(height) {}

void View::loadText(sf::Text & text, const std::string & title, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setString(title);
    text.setCharacterSize(size);
    text.setFillColor(color);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    text.setPosition(position);
}