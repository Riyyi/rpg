#ifndef MAPLOAD_H
#define MAPLOAD_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <rapidjson/document.h>

#include "map.h"

class MapLoad
{
public:
    MapLoad(Map *map, std::string mapName, int update = 0);
    void GetFile(std::string *content, std::string mapName);
    void Parser(std::string *content, rapidjson::Document *document);
    void LoadLayer(const rapidjson::Document &document, Map *map);
    void LoadTileSet(const rapidjson::Document& document, Map *map);
    void LoadMap(const rapidjson::Document& document, Map *map);
    ~MapLoad();
};

#endif // MAPLOAD_H
