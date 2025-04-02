#include "TitleView.h"

TitleView::TitleView(sf::Font& font) : View(font), title(font), simulation(font), menu(font) {
    loadTexts();
}

void TitleView::loadTexts() {
    title.setString("Battle Simulator");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition({100, 100});

    simulation.setString("Simulation");
    simulation.setCharacterSize(24);
    simulation.setFillColor(sf::Color::Green);
    simulation.setPosition({100, 200});

    menu.setString("Menu");
    menu.setCharacterSize(24);
    menu.setFillColor(sf::Color::Cyan);
    menu.setPosition({100, 270});
}

void TitleView::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(simulation);
    window.draw(menu);
}

// ViewState TitleView::handleEvent(const sf::Event& event) {
//     ;
// }
