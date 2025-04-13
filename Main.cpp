#include <SFML/Graphics.hpp>
#include "Frontend/ViewManager.h"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    ViewManager viewManager = ViewManager(desktop.size.x, desktop.size.y);
}