#include "map.h"

void TileSet::Clear() {
    while (this->tile.size() > 0) {
        delete this->tile[this->tile.size() - 1];
        this->tile.pop_back();
    }
}

TileSet::~TileSet() {
    this->Clear();
}

Map::Map() {
    this->ground1 = new Layer();
    this->above1 = new Layer();
    this->collision = new Layer();
    this->tileSet = new TileSet();
}

void Map::Render(sf::RenderWindow* window) {
    // Get render section
    sf::Vector2f renderWidth = sf::Vector2f((window->getView().getCenter().x - window->getSize().x / 2) / this->tilewidth,
                                       (window->getView().getCenter().x + window->getSize().x / 2) / this->tilewidth);
    sf::Vector2f renderHeight = sf::Vector2f((window->getView().getCenter().y - window->getSize().y / 2) / this->tileheight,
                                       (window->getView().getCenter().y + window->getSize().y / 2) / this->tileheight);

    // Render map
    int index;
    sf::Sprite tile;
    for (int y = renderHeight.x; y < renderHeight.y; y++) {
        for (int x = renderWidth.x; x < renderWidth.y; x++) {
            index = this->ground1->data[y][x];
            if(index != 0) {
                tile.setTexture(*this->tileSet->tile[index]);
                tile.setPosition(sf::Vector2f(x * this->tileSet->tileWidth, y * this->tileSet->tileHeight));
                window->draw(tile);
            }
        }
    }
}

Map::~Map() {
    delete this->tileSet;
    delete this->ground1;
    delete this->above1;
    delete this->collision;
}
