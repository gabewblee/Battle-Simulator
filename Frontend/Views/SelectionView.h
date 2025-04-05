#ifndef SELECTION_VIEW_H
#define SELECTION_VIEW_H

#include "View.h"

class SelectionView : public View {
public:
    SelectionView(sf::Font & font, const unsigned int state, unsigned int width, unsigned int height);
    ~SelectionView() override = default;
    unsigned int handleEvent(const std::optional<sf::Event> & event, unsigned int currState) override;
    void draw(sf::RenderWindow& window) override;
    
private:
    sf::Text fieldOneText;
    sf::Text fieldTwoText;
    sf::Text fieldThreeText;

    void loadTexts() override;
};

#endif