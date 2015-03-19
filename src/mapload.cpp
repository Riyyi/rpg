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
    map->tileSet->Clear();
    map->tileSet->image = document["tilesets"][0]["image"].GetString();
    map->tileSet->imageHeight = document["tilesets"][0]["imageheight"].GetInt();
    map->tileSet->imageWidth = document["tilesets"][0]["imagewidth"].GetInt();
    map->tileSet->tileHeight = document["tilesets"][0]["tileheight"].GetInt();
    map->tileSet->tileWidth = document["tilesets"][0]["tilewidth"].GetInt();

    int height = map->tileSet->imageHeight / map->tileSet->tileHeight;
    int width = map->tileSet->imageWidth / map->tileSet->tileWidth;

    // Add NULL texture to fill position '0'
    sf::Texture* texture = new sf::Texture();
    map->tileSet->tile.push_back(texture);

    // Load map tilesheet
    std::string tileSheetLocation = map->tileSet->image;
    tileSheetLocation.replace(0, 2, "data");
    sf::Image tileSheet;
    tileSheet.loadFromFile(tileSheetLocation);
    tileSheet.createMaskFromColor(sf::Color::White);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            sf::Texture* texture = new sf::Texture();
            texture->loadFromImage(tileSheet, sf::IntRect(x * map->tileSet->tileWidth,
                                                          y * map->tileSet->tileHeight,
                                                          map->tileSet->tileWidth,
                                                          map->tileSet->tileHeight));
            map->tileSet->tile.push_back(texture);
        }
    }

    // LAYER 1
    map->layer1->data.clear();
    height = document["layers"][0]["height"].GetInt();
    width = document["layers"][0]["width"].GetInt();

    const rapidjson::Value& mapArray = document["layers"][0]["data"];
    assert(mapArray.IsArray());

    int itr = 0;
    for (int y = 0; y < height; y++) {
        std::vector<int> row;

        for (int x = 0; x < width; x++) {
            row.push_back(mapArray[itr].GetInt());
            itr++;
        }

        map->layer1->data.push_back(row);
    }

    map->layer1->height = height;
    map->layer1->visible = document["layers"][0]["visible"].GetBool();
    map->layer1->width = width;
    map->layer1->x = document["layers"][0]["x"].GetInt();
    map->layer1->y = document["layers"][0]["y"].GetInt();

    // MAP
    map->height = document["layers"][0]["height"].GetInt();
    // Layer
    map->tileheight = document["tileheight"].GetInt();
    // TileSet
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
