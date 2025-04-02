#include <SFML/Graphics.hpp>
#include "Frontend/WindowManager.h"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int width = desktop.size.x;
    int height = desktop.size.y;
    WindowManager windowManager = WindowManager(width, height);
}