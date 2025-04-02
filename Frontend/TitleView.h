#ifndef TITLE_H
#define TITLE_H

#include "View.h"

class TitleView : public View {
public:
    TitleView(sf::Font& font);

    void draw(sf::RenderWindow& window) override;
    // ViewState handleEvent(const sf::Event& event) override;
    
private:
    sf::Text title;
    sf::Text simulation;
    sf::Text menu;

    void loadTexts();
};

#endif