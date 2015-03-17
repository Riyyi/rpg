#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

class TileSet
{
public:
    //TileSet();
    //~TileSet();

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
    std::vector<int> tile;
};

class Layer
{
public:
    //Layer();
    //~Layer();

    std::vector<std::vector<int>> data;
    int height;
//    name
//    opacity
//    type
    bool visible;
    int width;
    int x;
    int y;
};

class Map
{
public:
    Map();
    ~Map();

    // Global
    int height;
    Layer* layer1;
//    "nextobjectid":1,
//    "orientation":"orthogonal",
//    "properties":
//       {

//       },
//    "renderorder":"right-down",
    int tileheight;
    TileSet* tileSet;
    int tilewidth;
//    "version":1,
    int width;
};

//sf::Sprite* sprite;
//for()
//{
//    Sprite sf::Texture = tile.texture
//    sprire->setPosition(sf:vector2i);    5 * 32, 4 * 32
//    window->draw(*sprite);
//}

#endif // MAP_H
