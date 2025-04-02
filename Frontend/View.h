#ifndef VIEW
#define VIEW

#include <SFML/Graphics.hpp>
#include "../Constants.h"

class View {
public:
    View(const sf::Font& font) : font(font) {}
    virtual ~View() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    // virtual ViewState handleEvent(const sf::Event& event) = 0;
    // virtual void update() = 0;

protected:
    const sf::Font& font;
};


#endif