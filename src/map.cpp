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

Map::Map()
{
    this->tileSet = new TileSet();
    this->layer1 = new Layer();
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

Map::~Map()
{
    delete this->tileSet;
    delete this->layer1;
}

//void drawMap(sf::RenderWindow* window)
//{
//	sf::Sprite tile;
//	int itr = 0;
//	int location;
//	int maxWidth = nearbyint((view.getCenter().x + view.getSize().x / 2) / map->tileSet->tileWidth) + 1;
//	int minWidth = nearbyint((view.getCenter().x - view.getSize().x / 2) / map->tileSet->tileWidth) - 1;
//	int maxHeight = nearbyint((view.getCenter().y + view.getSize().y / 2) / map->tileSet->tileHeight) + 1;
//	int minHeight = nearbyint((view.getCenter().y - view.getSize().y / 2) / map->tileSet->tileHeight) - 1;

//	for (int y = minHeight; y < maxHeight && y < map->height; y++)
//	{
//		if (y < 0)
//		{
//			y = 0;
//		}
//		for (int x = minWidth; x < maxWidth && x < map->width; x++)
//		{
//			if (x < 0)
//			{
//				x = 0;
//			}
//			location = map->data[y][x];
//			if (location != 0)
//			{
//				tile.setTexture(*map->tileSet->data[location]);
//				tile.setPosition(sf::Vector2f(x * map->tileSet->tileWidth, y * map->tileSet->tileHeight));
//				window->draw(tile);
//			}
//			itr++;
//		}
//	}
//}
