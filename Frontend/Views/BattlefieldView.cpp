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
    return currState;
}

void BattlefieldView::drawComponents(sf::RenderWindow & window) {
    placeField(window);
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
    this->unitManager = UnitManager(this->properties.battlefield);
}

void BattlefieldView::placeField(sf::RenderWindow & window) {
    float offsetX = (window.getSize().x - this->properties.fieldWidth) / 2.0f;
    float offsetY = (window.getSize().y - this->properties.fieldHeight) / 2.0f;

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

                sprite.setTextureRect(sf::IntRect({textureX, textureY}, {(int) this->properties.tileDimensions.x, (int) this->properties.tileDimensions.y}));
                sprite.setPosition({offsetX + x * this->properties.tileDimensions.x, offsetY + y * this->properties.tileDimensions.y});
                window.draw(sprite);
            }
        }
    }
}