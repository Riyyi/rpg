#include "mapload.h"

MapLoad::MapLoad()
{

}

MapLoad::~MapLoad()
{

}

void MapLoad::GetFile(std::string* content, std::string mapName) {
    // Get the content of the map file and append it to content
    std::ifstream openFile(mapName);
    if (openFile.is_open())
    {
        std::string ifStream;
        while (!openFile.eof())
        {
            openFile >> ifStream;

            *content += ifStream;
        }

        openFile.close();
    }
    else {
        std::cout << "MapLoad:GetFile | Couldn't open file: " << mapName << std::endl;
    }
}

void MapLoad::Parser(std::string* content, Map* map) {
    // 1. Parse a JSON string into DOM.
    rapidjson::Document document;
    document.Parse(content->c_str());

    // Process map
    // TILESET
    TileSet* tileSet = new TileSet();
    tileSet->image = document["tilesets"][0]["image"].GetString();
    tileSet->imageHeight = document["tilesets"][0]["imageheight"].GetInt();
    tileSet->imageWidth = document["tilesets"][0]["imagewidth"].GetInt();
    tileSet->tileHeight = document["tilesets"][0]["tileheight"].GetInt();
    tileSet->tileWidth = document["tilesets"][0]["tilewidth"].GetInt();

    int height = document["layers"][0]["height"].GetInt();
    int width = document["layers"][0]["width"].GetInt();

    // LAYER 1
    Layer* layer = new Layer();

    const rapidjson::Value& mapArray = document["layers"][0]["data"];
    assert(mapArray.IsArray());

    int y = 0;
    for (int i = 0; i < height; i++) {
        std::vector<int> row;

        for (int j = 0; j < width; j++) {
            row.push_back(mapArray[y].GetInt());
            y++;
        }

        layer->data.push_back(row);
    }

    layer->height = height;
    layer->visible = document["layers"][0]["visible"].GetBool();
    layer->width = width;
    layer->x = document["layers"][0]["x"].GetInt();
    layer->y = document["layers"][0]["y"].GetInt();

    // MAP
    map->height = document["layers"][0]["height"].GetInt();
    map->layer1 = layer;
    map->tileheight = document["tileheight"].GetInt();
    map->tileSet = tileSet;
    map->tilewidth = document["tilewidth"].GetInt();
    map->width = document["layers"][0]["width"].GetInt();

//    for (int i = 0; i < map->data1.size(); i++) {
//        for (int j = 0; j < width; j++) {
//            std::cout << map->data1[i][j] << std::endl;
//        }
//    }
}

void MapLoad::Load(Map* map, std::string mapName) {
    std::string content;
    GetFile(&content, mapName);
    Parser(&content, map);
}
