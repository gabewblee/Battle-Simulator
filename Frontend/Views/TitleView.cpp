#include "TitleView.h"

TitleView::TitleView(sf::Font & font, ViewID state, unsigned int width, unsigned int height) 
    : View(font, state, width, height), title(font), simulate(font), menu(font) {
}
    
ViewID TitleView::handleEvent(const std::optional<sf::Event> & event, ViewID currState) {
    if (const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        int x = mouseButtonPressed->position.x;
        int y = mouseButtonPressed->position.y;
        if (this->simulate.getGlobalBounds().contains({(float) x, (float) y})) return ViewID::GAMEMODE;
    }
    return currState;
}

void TitleView::drawComponents(sf::RenderWindow & window) {
    this->title.setString("Battle Simulator");
    this->title.setCharacterSize(100);
    this->title.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = this->title.getLocalBounds();
    this->title.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
    this->title.setPosition({this->width / 2.0f, this->height / 10.0f});
    window.draw(this->title);

    this->simulate.setString("Simulate");
    this->simulate.setCharacterSize(60);
    this->simulate.setFillColor(sf::Color::White);
    sf::FloatRect simulateBounds = this->simulate.getLocalBounds();
    this->simulate.setOrigin({simulateBounds.size.x / 2.0f, simulateBounds.size.y / 2.0f});
    this->simulate.setPosition({this->width / 2.0f, this->height * 4.0f / 10.0f});
    window.draw(this->simulate);

    this->menu.setString("Menu");
    this->menu.setCharacterSize(60);
    this->menu.setFillColor(sf::Color::White);
    sf::FloatRect menuBounds = menu.getLocalBounds();
    this->menu.setOrigin({menuBounds.size.x / 2.0f, menuBounds.size.y / 2.0f});
    this->menu.setPosition({this->width / 2.0f, this->height * 5.0f / 10.0f});
    window.draw(this->menu);
}
