#include "BattlefieldView.h"

BattlefieldView::BattlefieldView(sf::Font & font, ViewID state, unsigned int width, unsigned int height) 
    : View(font, state, width, height) {
    switch (state) {
        case ViewID::URBANFIELD:
            loadProperties("Frontend/Tilesets/Urban Field/Urban Field.tmx");
            break;
        default:
            std::cerr << "Invalid ViewID state for battlefield" << std::endl;
            exit(EXIT_FAILURE);
    }
}

ViewID BattlefieldView::handleEvent(const std::optional<sf::Event> & event, ViewID currState) {
    if (const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        int x = mouseButtonPressed->position.x;
        int y = mouseButtonPressed->position.y;
        std::pair<int, int> tileCoordinates = getTileCoordinates(x, y);
        unitManager.addUnit(UnitType::SOLDIER, 1, tileCoordinates.first, tileCoordinates.second);
    }
    return currState;
}

void BattlefieldView::drawComponents(sf::RenderWindow & window) {
    drawField(window);
    drawUnits(window);
    drawUnitBar(window);
}

void BattlefieldView::loadProperties(std::string mapPath) {
    if (!this->properties.battlefield.load(mapPath)) {
        std::cerr << "Failed to load map at: " << mapPath << std::endl;
        exit(EXIT_FAILURE);
    }

    this->properties.fieldDimensions = this->properties.battlefield.getTileCount();
    this->properties.tileDimensions = this->properties.battlefield.getTileSize();
    this->properties.fieldWidth = this->properties.fieldDimensions.x * this->properties.tileDimensions.x;
    this->properties.fieldHeight = this->properties.fieldDimensions.y * this->properties.tileDimensions.y;

    const auto & tilesets = this->properties.battlefield.getTilesets();
    if (tilesets.empty()) {
        std::cerr << "No tilesets found" << std::endl;
        exit(EXIT_FAILURE);
    }

    const auto & tileset = tilesets[0];
    std::string tilesetPath = tileset.getImagePath();
    
    if (!this->properties.tileset.loadFromFile(tilesetPath)) {
        std::cerr << "Failed to load tileset texture from: " << tilesetPath << std::endl;
        exit(EXIT_FAILURE);
    }

    this->properties.margin = tileset.getMargin();
    this->properties.spacing = tileset.getSpacing();
    this->properties.offsetX = (this->width - this->properties.fieldWidth) / 2.0f;
    this->properties.offsetY = (this->height - this->properties.fieldHeight) / 2.0f;
    this->unitManager = UnitManager(this->properties);
}

void BattlefieldView::drawField(sf::RenderWindow & window) {
    sf::Sprite sprite(this->properties.tileset);
    
    const auto & tileset = this->properties.battlefield.getTilesets()[0];
    unsigned int numColumns = tileset.getColumnCount();

    const auto & layers = this->properties.battlefield.getLayers();
    for (const auto & layer : layers) {
        const auto & tileLayer = layer->getLayerAs<tmx::TileLayer>();
        const auto & tiles = tileLayer.getTiles();

        for (unsigned int y = 0; y < this->properties.fieldDimensions.y; y++) {
            for (unsigned int x = 0; x < this->properties.fieldDimensions.x; x++) {
                std::size_t idx = x + y * this->properties.fieldDimensions.x;
                std::uint32_t tileID = tiles[idx].ID;
                
                if (tileID == 0) continue;
                
                tileID -= tileset.getFirstGID();
                
                unsigned int tilesetX = tileID % numColumns;
                unsigned int tilesetY = tileID / numColumns;
                
                int textureX = this->properties.margin + (tilesetX * (this->properties.tileDimensions.x + this->properties.spacing));
                int textureY = this->properties.margin + (tilesetY * (this->properties.tileDimensions.y + this->properties.spacing));
                std::pair<float, float> pixelCoordinates = getPixelCoordinates(x, y);

                sprite.setTextureRect(sf::IntRect({textureX, textureY}, {(int) this->properties.tileDimensions.x, (int) this->properties.tileDimensions.y}));
                sprite.setPosition({pixelCoordinates.first, pixelCoordinates.second});
                window.draw(sprite);
            }
        }
    }
}

void BattlefieldView::drawUnits(sf::RenderWindow & window) {
    const std::vector<std::unique_ptr<Unit>> & userUnits = unitManager.getUserUnits();
    for (const std::unique_ptr<Unit> & unit : userUnits) {
        sf::RectangleShape rect;
        rect.setSize({(float) this->properties.tileDimensions.x, (float) this->properties.tileDimensions.y});
        rect.setFillColor(sf::Color::Green);
        rect.setPosition({unit->x * this->properties.tileDimensions.x + this->properties.offsetX, unit->y * this->properties.tileDimensions.y + this->properties.offsetY});
        window.draw(rect);
    }
}

void BattlefieldView::drawUnitBar(sf::RenderWindow & window) {
    const std::map<UnitType, int> unitBar = this->unitManager.getUnitBar();

    sf::Text soldierBar(this->font);
    soldierBar.setString("Soldiers: " + std::to_string(unitBar.at(UnitType::SOLDIER)));
    soldierBar.setCharacterSize(16);
    soldierBar.setFillColor(sf::Color::White);
    soldierBar.setPosition({(float) this->width - 300, (float) 20});
    window.draw(soldierBar);

    sf::Text droneBar(this->font);
    droneBar.setString("Drones: " + std::to_string(unitBar.at(UnitType::DRONE)));
    droneBar.setCharacterSize(16);
    droneBar.setFillColor(sf::Color::White);
    droneBar.setPosition({(float) this->width - 300, (float) 45});
    window.draw(droneBar);

    sf::Text tankBar(this->font);
    tankBar.setString("Tanks: " + std::to_string(unitBar.at(UnitType::TANK)));
    tankBar.setCharacterSize(16);
    tankBar.setFillColor(sf::Color::White);
    tankBar.setPosition({(float) this->width - 300, (float) 70});
    window.draw(tankBar);
}

std::pair<float, float> BattlefieldView::getPixelCoordinates(unsigned int x, unsigned int y) {
    float pixelX = (x * this->properties.tileDimensions.x) + this->properties.offsetX;
    float pixelY = (y * this->properties.tileDimensions.y) + this->properties.offsetY;
    return {pixelX, pixelY};
}

std::pair<int, int> BattlefieldView::getTileCoordinates(unsigned int x, unsigned int y) {
    int tileX = (x - this->properties.offsetX) / this->properties.tileDimensions.x;
    int tileY = (y - this->properties.offsetY) / this->properties.tileDimensions.y;
    return {tileX, tileY};
}