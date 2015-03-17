#ifndef MAPLOAD_H
#define MAPLOAD_H

#include <iostream>
#include <fstream>

#include <rapidjson/document.h>

#include "map.h"

class MapLoad
{
public:
    MapLoad();
    ~MapLoad();

    void GetFile(std::string* content, std::string mapName);
    void Parser(std::string* content, Map* map);
    void Load(Map* map, std::string mapName);
};

#endif // MAPLOAD_H
