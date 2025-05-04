#include "ViewManager.h"

ViewManager::ViewManager(unsigned int width, unsigned int height) {
    this->window.create(sf::VideoMode({width, height}), "Battle Simulator");
    this->width = this->window.getSize().x;
    this->height = this->window.getSize().y;
    loadFont("Frontend/Fonts/CallOfOpsDuty.otf");
    loadViews();
    run();
}

void ViewManager::run() {
    while (this->window.isOpen()) {
        while (const std::optional<sf::Event> event = this->window.pollEvent())
            handleEvent(event);
        this->window.clear();
        this->currView->drawComponents(this->window);
        this->window.display();
    }
}

void ViewManager::handleEvent(const std::optional<sf::Event> event) {
    if (event->is<sf::Event::Closed>()) this->window.close();  
    ViewID newState = currView->handleEvent(event, currView->state);
    if (newState != currView->state) switchView(newState);
}

void ViewManager::switchView(ViewID newState) { this->currView = this->views[(int) newState].get(); }

void ViewManager::loadFont(std::string fontPath) {
    if (!this->font.openFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ViewManager::loadViews() {
    // this->views.emplace_back(std::make_unique<TitleView>(this->font, ViewID::TITLE, this->width, this->height));
    // this->views.emplace_back(std::make_unique<GameModeView>(this->font, ViewID::GAMEMODE, this->width, this->height));
    this->views.emplace_back(std::make_unique<BattlefieldView>(this->font, ViewID::URBANFIELD, this->width, this->height));
    this->currView = this->views[0].get();
}