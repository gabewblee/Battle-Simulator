#ifndef TITLE_VIEW_H
#define TITLE_VIEW_H

#include "View.h"

class TitleView : public View {
public:
    TitleView(sf::Font & font, ViewID state, unsigned int width, unsigned int height);
    ~TitleView() override = default;
    ViewID handleEvent(const std::optional<sf::Event> & event, ViewID currState) override;
    void drawComponents(sf::RenderWindow & window) override;
    
private:
    sf::Text title;
    sf::Text simulate;
    sf::Text menu;
};

#endif