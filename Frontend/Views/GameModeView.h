#ifndef GAME_MODE_VIEW_H
#define GAME_MODE_VIEW_H

#include "View.h"

class GameModeView : public View {
public:
    GameModeView(sf::Font & font, ViewID state, unsigned int width, unsigned int height);
    ~GameModeView() override = default;

    ViewID handleEvent(const std::optional<sf::Event> & event, ViewID currState) override;
    void drawComponents(sf::RenderWindow& window) override;
    
private:
    sf::Text titleText;
    sf::Text urbanFieldText;
    sf::RectangleShape urbanFieldContainer;
    sf::Text ruralFieldText;
    sf::RectangleShape ruralFieldContainer;
    sf::Text undergroundFieldText;
    sf::RectangleShape undergroundFieldContainer;
};

#endif