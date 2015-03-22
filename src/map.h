#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "entity.h"

class Layer
{
public:
    //Layer();
    //~Layer();

    std::vector<std::vector<int>> data;
    int height;
//    name
//    opacity
//    properties
//    type
    bool visible;
    int width;
    int x;
    int y;
};

class TileSet
{
public:
    //TileSet();
    void Clear();
    ~TileSet();

//            "firstgid":1,
    std::string image;
    int imageHeight;
    int imageWidth;
//            "margin":0,
//            "name":"Tilesheet",
//            "properties":
//               {

//               },
//            "spacing":0,
    int tileHeight;
    int tileWidth;
//            "transparentcolor":"#ffffff"
    // @Todo save all tile textures with pointers
    // map->tileSet.tile[1];
    std::vector<sf::Texture*> tile;
};

class Map
{
public:
    Map();
    void CheckCollision(sf::RenderWindow *window, Entity *entity);
    void RenderGround(sf::RenderWindow *window);
    void RenderAbove(sf::RenderWindow *window);
    ~Map();

    int height;
    Layer* ground1;
    Layer* above1;
    Layer* collision;
//    "nextobjectid":1,
//    "orientation":"orthogonal",
//    "properties":
//       {

//       },
//    "renderorder":"right-down",
    int tileHeight;
    TileSet* tileSet;
    int tileWidth;
//    "version":1,
    int width;

private:
    void Render(sf::RenderWindow *window, Layer *layer);
};

//sf::Sprite* sprite;
//for()
//{
//    Sprite sf::Texture = tile.texture
//    sprire->setPosition(sf:vector2i);    5 * 32, 4 * 32
//    window->draw(*sprite);
//}

#endif // MAP_H
