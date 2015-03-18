#include "map.h"

//TileSet::~TileSet() {
//    // @Todo remove all tiles from std::vector<sf::Texture*> tile;
//}

Map::Map()
{

}

Map::~Map()
{
    delete this->tileSet;
    delete this->layer1;
}

void Map::Render(sf::RenderWindow* window) {
    sf::Sprite tile;
    int index;
    int width = this->layer1->width;
    int height = this->layer1->height;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            index = this->layer1->data[i][j];
            if(index != 0) {
                tile.setTexture(*this->tileSet->tile[index]);
                tile.setPosition(sf::Vector2f(j * this->tileSet->tileWidth, i * this->tileSet->tileHeight));
                window->draw(tile);
            }
        }
    }
}
