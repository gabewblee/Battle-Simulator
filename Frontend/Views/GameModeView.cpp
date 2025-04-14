#include "GameModeView.h"
#include <iostream>

GameModeView::GameModeView(sf::Font & font, ViewID state, unsigned int width, unsigned int height) 
    : View(font, state, width, height), titleText(font), urbanFieldText(font), ruralFieldText(font), undergroundFieldText(font) {}

ViewID GameModeView::handleEvent(const std::optional<sf::Event> & event, ViewID currState) {
    if (const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        int x = mouseButtonPressed->position.x;
        int y = mouseButtonPressed->position.y;
        if (this->urbanFieldContainer.getGlobalBounds().contains({(float) x, (float) y})) return ViewID::URBANFIELD;
        else if (this->ruralFieldContainer.getGlobalBounds().contains({(float) x, (float) y})) return ViewID::URBANFIELD;
        else if (this->undergroundFieldContainer.getGlobalBounds().contains({(float) x, (float) y})) return ViewID::URBANFIELD;
        else;
    }
    return currState;
}

void GameModeView::drawComponents(sf::RenderWindow & window) {
    this->titleText.setString("Choose a field");
    this->titleText.setCharacterSize(60);
    this->titleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = this->titleText.getLocalBounds();
    this->titleText.setOrigin({titleBounds.size.x / 2.0f, titleBounds.size.y / 2.0f});
    this->titleText.setPosition({this->width / 2.0f, this->height * 1.0f / 10.0f});
    window.draw(this->titleText);

    this->urbanFieldText.setString("Urban Field");
    this->urbanFieldText.setCharacterSize(36);
    this->urbanFieldText.setFillColor(sf::Color::White);
    sf::FloatRect urbanFieldBounds = this->urbanFieldText.getLocalBounds();
    this->urbanFieldText.setOrigin({urbanFieldBounds.size.x / 2.0f, urbanFieldBounds.size.y / 2.0f});
    this->urbanFieldText.setPosition({this->width * 1.0f / 5.0f, this->height * 2.0f / 3.0f});
    window.draw(this->urbanFieldText);

    auto [urbanFieldX, urbanFieldY] = this->urbanFieldText.getPosition();
    this->urbanFieldContainer.setSize({300.0f, 400.f});
    this->urbanFieldContainer.setOutlineThickness(2.f);
    this->urbanFieldContainer.setFillColor(sf::Color::Black);
    this->urbanFieldContainer.setOutlineColor(sf::Color::White);
    sf::FloatRect urbanFieldContainerBounds = this->urbanFieldContainer.getLocalBounds();
    this->urbanFieldContainer.setOrigin({urbanFieldContainerBounds.size.x / 2.0f, urbanFieldContainerBounds.size.y / 2.0f});
    this->urbanFieldContainer.setPosition({urbanFieldX, urbanFieldY - 250});
    window.draw(this->urbanFieldContainer);

    this->ruralFieldText.setString("Rural Field");
    this->ruralFieldText.setCharacterSize(36);
    this->ruralFieldText.setFillColor(sf::Color::White);
    sf::FloatRect ruralFieldBounds = ruralFieldText.getLocalBounds();
    this->ruralFieldText.setOrigin({ruralFieldBounds.size.x / 2.0f, ruralFieldBounds.size.y / 2.0f});
    this->ruralFieldText.setPosition({this->width * 2.5f / 5.0f, this->height * 2.0f / 3.0f});
    window.draw(this->ruralFieldText);

    auto [ruralFieldX, ruralFieldY] = this->ruralFieldText.getPosition();
    this->ruralFieldContainer.setSize({300.0f, 400.f});
    this->ruralFieldContainer.setOutlineThickness(2.f);
    this->ruralFieldContainer.setFillColor(sf::Color::Black);
    this->ruralFieldContainer.setOutlineColor(sf::Color::White);
    sf::FloatRect ruralFieldContainerBounds = this->ruralFieldContainer.getLocalBounds();
    this->ruralFieldContainer.setOrigin({ruralFieldContainerBounds.size.x / 2.0f, ruralFieldContainerBounds.size.y / 2.0f});
    this->ruralFieldContainer.setPosition({ruralFieldX, ruralFieldY - 250});
    window.draw(this->ruralFieldContainer);

    this->undergroundFieldText.setString("Underground Field");
    this->undergroundFieldText.setCharacterSize(36);
    this->undergroundFieldText.setFillColor(sf::Color::White);
    sf::FloatRect undergroundFieldBounds = this->undergroundFieldText.getLocalBounds();
    this->undergroundFieldText.setOrigin({undergroundFieldBounds.size.x / 2.0f, undergroundFieldBounds.size.y / 2.0f});
    this->undergroundFieldText.setPosition({this->width * 4.0f / 5.0f, this->height * 2.0f / 3.0f});
    window.draw(this->undergroundFieldText);

    auto [undergroundFieldX, undergroundFieldY] = this->undergroundFieldText.getPosition();
    this->undergroundFieldContainer.setSize({300.0f, 400.f});
    this->undergroundFieldContainer.setOutlineThickness(2.f);
    this->undergroundFieldContainer.setFillColor(sf::Color::Black);
    this->undergroundFieldContainer.setOutlineColor(sf::Color::White);
    sf::FloatRect undergroundFieldContainerBounds = this->undergroundFieldContainer.getLocalBounds();
    this->undergroundFieldContainer.setOrigin({undergroundFieldContainerBounds.size.x / 2.0f, undergroundFieldContainerBounds.size.y / 2.0f});
    this->undergroundFieldContainer.setPosition({undergroundFieldX, undergroundFieldY - 250});
    window.draw(this->undergroundFieldContainer);
}