#include "SelectionView.h"
#include <iostream>

SelectionView::SelectionView(sf::Font & font, const unsigned int state, unsigned int width, unsigned int height) 
    : View(font, state, width, height), fieldOneText(font), fieldTwoText(font), fieldThreeText(font) {
    loadTexts();
}

void SelectionView::loadTexts() {
    this->loadText(this->fieldOneText, "Field One", 24, sf::Color::White, {this->width * 1.0f / 5.0f, this->height * 2.0f / 3.0f});
    this->loadText(this->fieldTwoText, "Field Two", 24, sf::Color::White, {this->width * 2.5f / 5.0f, this->height * 2.0f / 3.0f});
    this->loadText(this->fieldThreeText, "Field Three", 24, sf::Color::White, {this->width * 4.0f / 5.0f, this->height * 2.0f / 3.0f});
}

unsigned int SelectionView::handleEvent(const std::optional<sf::Event> & event, unsigned int currState) {
    return currState;
}

void SelectionView::draw(sf::RenderWindow & window) {
    window.draw(this->fieldOneText);
    window.draw(this->fieldTwoText);
    window.draw(this->fieldThreeText);
}