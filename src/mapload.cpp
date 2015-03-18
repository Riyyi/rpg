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

    int height = tileSet->imageHeight / tileSet->tileHeight;
    int width = tileSet->imageWidth / tileSet->tileWidth;

    // Add NULL texture to fill position '0'
    sf::Texture* texture = new sf::Texture();
    tileSet->tile.push_back(texture);

    // Load map tilesheet
    std::string tileSheetLocation = tileSet->image;
    tileSheetLocation.replace(0, 2, "data");
    sf::Image tileSheet;
    tileSheet.loadFromFile(tileSheetLocation);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            sf::Texture* texture = new sf::Texture();
            texture->loadFromImage(tileSheet, sf::IntRect(x * tileSet->tileWidth,  y * tileSet->tileHeight, tileSet->tileWidth, tileSet->tileHeight));
            tileSet->tile.push_back(texture);
        }
    }

    // LAYER 1
    height = document["layers"][0]["height"].GetInt();
    width = document["layers"][0]["width"].GetInt();

    Layer* layer = new Layer();

    const rapidjson::Value& mapArray = document["layers"][0]["data"];
    assert(mapArray.IsArray());

    int itr = 0;
    for (int y = 0; y < height; y++) {
        std::vector<int> row;

        for (int x = 0; x < width; x++) {
            row.push_back(mapArray[itr].GetInt());
            itr++;
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
