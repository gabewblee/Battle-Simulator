#include "View.h"
#include "../Backend/UnitManager.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>

class BattlefieldView : public View {
public:
    BattlefieldView(sf::Font & font, ViewID state, const unsigned int width, const unsigned int height);
    ~BattlefieldView() override = default;

    ViewID handleEvent(const std::optional<sf::Event> & event, ViewID currState) override;
    void drawComponents(sf::RenderWindow & window) override;

private:
    FieldProperties properties;
    std::unique_ptr<UnitManager> unitManager;
    void process();
    void loadFieldProperties(std::string fieldPath);
    void drawField(sf::RenderWindow & window);
    void drawPlayerUnits(sf::RenderWindow & window);
    void drawEnemyUnits(sf::RenderWindow & window);
    void addUnit(unsigned int team, float x, float y);
    std::pair<float, float> getPixelCoordinates(unsigned int x, unsigned int y);
    std::pair<unsigned int, unsigned int> getTileCoordinates(float x, float y);
};