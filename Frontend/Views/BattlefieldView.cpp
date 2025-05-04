#include <iostream>
#include "BattlefieldView.h"

BattlefieldView::BattlefieldView(sf::Font & font, ViewID state, const unsigned int width, const unsigned int height) 
    : View(font, state, width, height) {
    loadFieldProperties("Frontend/Tilesets/Urban Field/Urban Field.tmx");
    this->unitManager = std::make_unique<UnitManager>(this->properties);
}

ViewID BattlefieldView::handleEvent(const std::optional<sf::Event> & event, ViewID currState) {
    if (const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        unsigned int x = mouseButtonPressed->position.x;
        unsigned int y = mouseButtonPressed->position.y;
        addUnit(0, x, y);
    }
    process();
    return currState;
}

void BattlefieldView::drawComponents(sf::RenderWindow & window) {
    drawField(window);
    drawPlayerUnits(window);
    drawEnemyUnits(window);
}

void BattlefieldView::process() {
    UnitManager * playerManager = this->unitManager.get();
    playerManager->search();
    playerManager->update();
}

void BattlefieldView::loadFieldProperties(std::string fieldPath) {
    if (!this->properties.battlefield.load(fieldPath)) {
        std::cerr << "Failed to load map at: " << fieldPath << std::endl;
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

void BattlefieldView::drawPlayerUnits(sf::RenderWindow & window) {
    for (const std::unique_ptr<Unit> & unitPtr : this->unitManager->getPlayerUnits()) {
        Unit * unit = unitPtr.get();
        // Create a rectangle to represent the unit
        sf::RectangleShape unitRect(sf::Vector2f(this->properties.tileDimensions.x, this->properties.tileDimensions.y));

        // Set the rectangle's position based on the unit's tile coordinates
        std::pair<float, float> pixelCoordinates = getPixelCoordinates(unit->x, unit->y);
        unitRect.setPosition({pixelCoordinates.first, pixelCoordinates.second});

        // Set the rectangle's color (e.g., blue for user units)
        unitRect.setFillColor(sf::Color::Blue);

        // Draw the rectangle
        window.draw(unitRect);
    }
}

void BattlefieldView::drawEnemyUnits(sf::RenderWindow & window) {
    for (const std::unique_ptr<Unit> & unitPtr : this->unitManager->getEnemyUnits()) {
        Unit * unit = unitPtr.get();
        // Create a rectangle to represent the unit
        sf::RectangleShape unitRect(sf::Vector2f(this->properties.tileDimensions.x, this->properties.tileDimensions.y));

        // Set the rectangle's position based on the unit's tile coordinates
        std::pair<float, float> pixelCoordinates = getPixelCoordinates(unit->x, unit->y);
        unitRect.setPosition({pixelCoordinates.first, pixelCoordinates.second});

        // Set the rectangle's color (e.g., red for enemy units)
        unitRect.setFillColor(sf::Color::Red);

        // Draw the rectangle
        window.draw(unitRect);
    }
}

void BattlefieldView::addUnit(unsigned int team, float x, float y) {
    std::pair<unsigned int, unsigned int> tileCoordinates = getTileCoordinates(x, y);
    unsigned int tileX = tileCoordinates.first;
    unsigned int tileY = tileCoordinates.second;

    if (tileX >= this->properties.fieldDimensions.x || tileY >= this->properties.fieldDimensions.y) {
        std::cerr << "Invalid coordinates for unit placement" << std::endl;
    } else {
        this->unitManager->addUnit(team, tileX, tileY);
    }
}

std::pair<float, float> BattlefieldView::getPixelCoordinates(unsigned int x, unsigned int y) {
    float pixelX = (x * this->properties.tileDimensions.x) + this->properties.offsetX;
    float pixelY = (y * this->properties.tileDimensions.y) + this->properties.offsetY;
    return {pixelX, pixelY};
}

std::pair<unsigned int, unsigned int> BattlefieldView::getTileCoordinates(float x, float y) {
    unsigned int tileX = (x - this->properties.offsetX) / this->properties.tileDimensions.x;
    unsigned int tileY = (y - this->properties.offsetY) / this->properties.tileDimensions.y;
    return {tileX, tileY};
}