#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window Manager/ScreenManager.h"

// int main() {
//     sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
//     unsigned int screenWidth = desktop.size.x;
//     unsigned int screenHeight = desktop.size.y;
//     ScreenManager screenManager = ScreenManager(screenWidth, screenHeight);

//     while (screenManager.window.isOpen())
//     {
//         // check all the window's events that were triggered since the last iteration of the loop
//         while (const std::optional event = screenManager.window.pollEvent())
//         {
//             // "close requested" event: we close the window
//             if (event->is<sf::Event::Closed>())
//                 screenManager.window.close();
//         }
//     }
// }
int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.size.x;
    unsigned int screenHeight = desktop.size.y;
    ScreenManager screenManager = ScreenManager(screenWidth, screenHeight);

    sf::Texture droneTexture;
    if (!droneTexture.loadFromFile("Window Manager/images/Drone.png")) {
        return 1;
    }

    sf::Sprite droneSprite(droneTexture);
    droneSprite.setOrigin({droneTexture.getSize().x / 2.f, droneTexture.getSize().y / 2.f});
    droneSprite.setPosition({static_cast<float>(screenWidth) / 2.f, static_cast<float>(screenHeight) / 2.f});


    while (screenManager.window.isOpen()) {
        while (const std::optional<sf::Event> event = screenManager.window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                screenManager.window.close();
            }
        }

        screenManager.window.clear(sf::Color(139, 69, 19));
        screenManager.window.draw(droneSprite);
        screenManager.window.display();
    }

    return 0;
}