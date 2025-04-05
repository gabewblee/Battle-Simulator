#include "WindowManager.h"

WindowManager::WindowManager(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    this->window.create(sf::VideoMode({width, height}), "My window");

    if (!this->font.openFromFile("Frontend/Fonts/SuperPixel.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->views.emplace_back(std::make_unique<TitleView>(font, 0, width, height));
    this->views.emplace_back(std::make_unique<SelectionView>(font, 1, width, height));
    this->currView = this->views[0].get();
    run();
}

void WindowManager::run() {
    while (this->window.isOpen()) {
        while (const std::optional<sf::Event> event = this->window.pollEvent())
            eventHandler(event);
        this->window.clear();
        this->currView->draw(this->window);
        this->window.display();
    }
}

void WindowManager::eventHandler(const std::optional<sf::Event> event) {
    if (event->is<sf::Event::Closed>()) this->window.close();  

    int newState = currView->handleEvent(event, currView->state);
    if (newState != currView->state) switchView(newState);
}

void WindowManager::switchView(unsigned int newState) {
    this->currView = this->views[newState].get();
}