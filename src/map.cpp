#include "map.h"

Map::Map()
{

}

Map::~Map()
{
    delete this->tileSet;
    delete this->layer1;
}

