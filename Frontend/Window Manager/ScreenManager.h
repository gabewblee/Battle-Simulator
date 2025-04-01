#include <SFML/Graphics.hpp>
#include <string>

class ScreenManager {
public:
    sf::RenderWindow window;
    ScreenManager(unsigned int width, unsigned int height);
};