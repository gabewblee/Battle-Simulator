#ifndef TITLE_VIEW_H
#define TITLE_VIEW_H

#include "View.h"

class TitleView : public View {
public:
    TitleView(sf::Font & font, const unsigned int state, unsigned int width, unsigned int height);
    ~TitleView() override = default;
    unsigned int handleEvent(const std::optional<sf::Event> & event, unsigned int currState) override;
    void draw(sf::RenderWindow & window) override;
    
private:
    sf::Text titleText;
    sf::Text simulateText;
    sf::Text menuText;
    
    void loadTexts() override;
};

#endif