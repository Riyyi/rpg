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
    this->ground2 = new Layer();
    this->ground3 = new Layer();
    this->above1 = new Layer();
    this->above2 = new Layer();
    this->above3 = new Layer();
    this->collision = new Layer();
    this->tileSet = new TileSet();
}

void Map::CheckCollision(Entity *entity) {
    // Get check section
    sf::Vector2f checkWidth = sf::Vector2f(
        (int)entity->getPosition().x / this->tileSet->tileWidth,
        (int)entity->getPosition().x / this->tileSet->tileWidth + 3
    );
    sf::Vector2f checkHeight = sf::Vector2f(
        (int)entity->getPosition().y / this->tileSet->tileWidth,
        (int)entity->getPosition().y / this->tileSet->tileWidth + 3
    );

    // Check collision
    int index;
    bool collided = false;
    for (int y = checkHeight.x; y < checkHeight.y; y++) {
        for (int x = checkWidth.x; x < checkWidth.y; x++) {
            index = this->collision->data[y][x];
            // If collision tile
            if(index != 0) {
                if (entity->getGlobalBounds().intersects(sf::FloatRect(x * this->tileSet->tileWidth,
                                                                       y * this->tileSet->tileHeight,
                                                                       this->tileSet->tileWidth,
                                                                       this->tileSet->tileHeight))) {
                    collided = true;
                }
            }
        }
    }

    // Move back if entity collided)
    if(collided) {
        // DOWN_RIGHT
        if(entity->velocity.x > 0
        && entity->velocity.y > 0) {
            entity->velocity.x -= entity->velocity.x * 2;
            entity->velocity.y = 0;
        }
        // UP_RIGHT
        else if(entity->velocity.x > 0
        && entity->velocity.y < 0) {
            entity->velocity.x = 0;
            entity->velocity.y -= entity->velocity.y * 2;
        }
        // UP_LEFT
        else if(entity->velocity.x < 0
        && entity->velocity.y < 0) {
            entity->velocity.x = 0;
            entity->velocity.y -= entity->velocity.y * 2;
        }
        // DOWN_LEFT
        else if(entity->velocity.x < 0
        && entity->velocity.y > 0) {
            entity->velocity.x -= entity->velocity.x * 2;
            entity->velocity.y = 0;
        }

        // RIGHT
        else if(entity->velocity.x > 0) {
            entity->velocity.x -= entity->velocity.x * 2;
        }
        // LEFT
        else if(entity->velocity.x < 0) {
            entity->velocity.x -= entity->velocity.x * 2;
        }
        // DOWN
        else if(entity->velocity.y > 0) {
            entity->velocity.y -= entity->velocity.y * 2;
        }
        // UP
        else if(entity->velocity.y < 0) {
            entity->velocity.y -= entity->velocity.y * 2;
        }

        entity->move(entity->velocity.x, entity->velocity.y);
    }
}

void Map::RenderGround(sf::RenderWindow *window) {
    Layer* layer = this->ground1;
    this->Render(window, layer);

    layer = this->ground2;
    this->Render(window, layer);

    layer = this->ground3;
    this->Render(window, layer);
}

void Map::RenderAbove(sf::RenderWindow *window) {
    Layer* layer = this->above1;
    this->Render(window, layer);

    layer = this->above2;
    this->Render(window, layer);

    layer = this->above3;
    this->Render(window, layer);
}

void Map::Render(sf::RenderWindow *window, Layer *layer) {
    // Get render section
    sf::Vector2f renderWidth = sf::Vector2f(
        (window->getView().getCenter().x - window->getSize().x / 2) / this->tileWidth,
        (window->getView().getCenter().x + window->getSize().x / 2) / this->tileWidth
    );
    sf::Vector2f renderHeight = sf::Vector2f(
        (window->getView().getCenter().y - window->getSize().y / 2) / this->tileHeight,
        (window->getView().getCenter().y + window->getSize().y / 2) / this->tileHeight
    );

    // Render map
    int index;
    sf::Sprite tile;
    for (int y = renderHeight.x; y < renderHeight.y; y++) {
        for (int x = renderWidth.x; x < renderWidth.y; x++) {
            index = layer->data[y][x];
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
    delete this->ground2;
    delete this->ground3;
    delete this->above1;
    delete this->above2;
    delete this->above3;
    delete this->collision;
}
