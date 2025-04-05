#include "TitleView.h"

TitleView::TitleView(sf::Font & font, const unsigned int state, unsigned int width, unsigned int height) 
    : View(font, state, width, height), titleText(font), simulateText(font), menuText(font) {
    loadTexts();
}

void TitleView::loadTexts() {
    this->loadText(this->titleText, "Battle Simulator", 48, sf::Color::White, {this->width / 2.0f, this->height * 1.0f / 10.0f});
    this->loadText(this->simulateText, "Simulate", 36, sf::Color::White, {this->width / 2.0f, this->height * 4.0f / 10.0f});
    this->loadText(this->menuText, "Menu", 36, sf::Color::White, {this->width / 2.0f, this->height * 5.0f / 10.0f});
}

unsigned int TitleView::handleEvent(const std::optional<sf::Event> & event, unsigned int currState) {
    if (const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        int x = mouseButtonPressed->position.x;
        int y = mouseButtonPressed->position.y;
        if (this->simulateText.getGlobalBounds().contains({(float) x, (float) y})) {
            return 1;
        }
    }
    return currState;
}

void TitleView::draw(sf::RenderWindow & window) {
    window.draw(this->titleText);
    window.draw(this->simulateText);
    window.draw(this->menuText);
}