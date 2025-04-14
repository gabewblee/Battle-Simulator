#include "BattlefieldView.h"

BattlefieldView::BattlefieldView(sf::Font & font, ViewID state, unsigned int width, unsigned int height) 
    : View(font, state, width, height) {
    auto iter = viewPaths.find(state);
    if (iter == viewPaths.end()) {
        std::cerr << "Invalid ViewID state for battlefield" << std::endl;
        exit(EXIT_FAILURE);
    }
    loadFieldProperties(iter->second);
    loadUnitCards();
    this->selectedCard = nullptr;
    this->unitManager = UnitManager(this->properties);
}

ViewID BattlefieldView::handleEvent(const std::optional<sf::Event> & event, ViewID currState) {
    if (const auto * mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        unsigned int x = mouseButtonPressed->position.x;
        unsigned int y = mouseButtonPressed->position.y;
        handleUnitCardClicked(x, y);
        handleAddUnit(x, y);
    }
    return currState;
}

void BattlefieldView::drawComponents(sf::RenderWindow & window) {
    drawField(window);
    drawUnits(window);
    drawUnitCards(window);
}

void BattlefieldView::loadFieldProperties(std::string mapPath) {
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
    this->properties.offsetX = 0;
    this->properties.offsetY = (this->height - this->properties.fieldHeight) / 2.0f;
}

void BattlefieldView::loadUnitCards() {
    float cardStart = this->properties.fieldWidth;
    float cardEnd = cardStart + ((this->width - this->properties.fieldWidth) / unitLabels.size());
    float cardWidth = cardEnd - cardStart;
    float cardHeight = cardEnd - cardStart;

    for (int i = 0 ; i < unitLabels.size() ; i++) {
        UnitCard unitCard(this->font);
        auto iter = unitLabelToType.find(unitLabels[i]);
        if (iter == unitLabelToType.end()) {
            std::cerr << "No matching type for the requested label" << std::endl;
            exit(EXIT_FAILURE);
        }
        unitCard.type = iter->second;

        unitCard.image.setSize({cardWidth, cardHeight});
        unitCard.image.setPosition({cardStart, 0.f});
        unitCard.image.setOutlineThickness(1.f);
        unitCard.image.setOutlineColor(sf::Color(105, 105, 105));
        unitCard.image.setFillColor(sf::Color::Black);

        unitCard.label.setString(unitLabels[i]);
        unitCard.label.setCharacterSize(16);
        unitCard.label.setFillColor(sf::Color::White);
        sf::FloatRect unitCardBounds = unitCard.label.getLocalBounds();
        unitCard.label.setOrigin({unitCardBounds.size.x / 2.0f, unitCardBounds.size.y / 2.0f});
        unitCard.label.setPosition({cardStart + cardWidth / 2.0f, cardHeight * 0.9f});
        this->unitCards.emplace_back(unitCard);
        
        cardStart += cardWidth;
    }
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

void BattlefieldView::drawUnitCards(sf::RenderWindow & window) {
    for (UnitCard unitCard : this->unitCards) {
        window.draw(unitCard.image);
        window.draw(unitCard.label);
    }
}

void BattlefieldView::handleUnitCardClicked(unsigned int x, unsigned int y) {
    for (UnitCard & unitCard : this->unitCards) {
        if (unitCard.image.getGlobalBounds().contains({(float) x, (float) y})) {
            if (this->selectedCard && this->selectedCard == &unitCard) {
                unitCard.image.setFillColor(sf::Color::Black);
                this->selectedCard = nullptr;
            } else {
                if (this->selectedCard) this->selectedCard->image.setFillColor(sf::Color::Black);
                this->selectedCard = &unitCard;
                unitCard.image.setFillColor(sf::Color(105, 105, 105));
            }
            break;
        }
    }
}

void BattlefieldView::handleAddUnit(unsigned int x, unsigned int y) {
    if (this->selectedCard) { 
        std::pair<int, int> tileCoordinates = getTileCoordinates(x, y);
        int tileX = tileCoordinates.first;
        int tileY = tileCoordinates.second;
        this->unitManager.addUnit(this->selectedCard, 1, tileX, tileY);
    }
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