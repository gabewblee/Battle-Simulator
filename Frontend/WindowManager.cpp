#include "WindowManager.h"

WindowManager::WindowManager(unsigned int width, unsigned int height) : width(width), height(width), currState(ViewState::TITLE), window(sf::VideoMode({width, height}), "Battle Simulator") {
    if (!font.openFromFile("Frontend/Fonts/SuperPixel.ttf")) {
        exit(0);
    }
    views.emplace_back(std::make_unique<TitleView>(font));
    currView = views[currState].get();
    run();
}

void WindowManager::run() {
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent())
            eventHandler(event);
        window.clear();
        currView->draw(window);
        window.display();
    }
}

void WindowManager::eventHandler(const std::optional<sf::Event> event) {
    if (event->is<sf::Event::Closed>()) {
        window.close();  
    } else {
        // ViewState newState = currView->handleEvent(event);
        // if (newState != currState) switchView(newState);
    }
}

void WindowManager::switchView(ViewState newState) {
    currState = newState;
    currView = views[newState].get();
}