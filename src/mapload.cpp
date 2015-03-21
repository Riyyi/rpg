#include "mapload.h"

MapLoad::MapLoad(Map *map, std::string mapName, int update) {
    std::string content;
    rapidjson::Document document;

    this->GetFile(&content, mapName);
    this->Parser(&content, &document);
    this->LoadLayer(document, map);
    if(!update) {
        this->LoadTileSet(document, map);
    }
    this->LoadMap(document, map);

//    for (int i = 0; i < 100; i++) {
//        for (int j = 0; j < 100; j++) {
//            std::cout << map->collision->data[i][j] << std::endl;
//        }
//    }
}

void MapLoad::GetFile(std::string *content, std::string mapName) {
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

void MapLoad::Parser(std::string *content, rapidjson::Document *document) {
    // 1. Parse a JSON string into DOM.
    document->Parse(content->c_str());
}

void MapLoad::LoadLayer(const rapidjson::Document& document, Map *map) {
    int loopCount = document["layers"].Size();
    Layer* current;
    for(unsigned int i = 0; i < loopCount; i++) {
        current = NULL;
        if(document["layers"][i]["properties"]["name"] == "Ground1") {
            current = map->ground1;
        }
        else if(document["layers"][i]["properties"]["name"] == "Above1") {
            current = map->above1;
        }
        if(document["layers"][i]["properties"]["name"] == "Collision") {
            current = map->collision;
        }

        if(current != NULL) {
            current->data.clear();
            int height = document["layers"][i]["height"].GetInt();
            int width = document["layers"][i]["width"].GetInt();

            const rapidjson::Value& mapArray = document["layers"][i]["data"];
            assert(mapArray.IsArray());

            int itr = 0;
            for (int y = 0; y < height; y++) {
                std::vector<int> row;

                for (int x = 0; x < width; x++) {
                    row.push_back(mapArray[itr].GetInt());
                    itr++;
                }

                current->data.push_back(row);
            }

            current->height = height;
            current->visible = document["layers"][i]["visible"].GetBool();
            current->width = width;
            current->x = document["layers"][i]["x"].GetInt();
            current->y = document["layers"][i]["y"].GetInt();
        }
    }
}

void MapLoad::LoadTileSet(const rapidjson::Document& document, Map *map) {
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
}

void MapLoad::LoadMap(const rapidjson::Document& document, Map *map) {
    // MAP
    map->height = document["layers"][0]["height"].GetInt();
    // Layer
    map->tileheight = document["tileheight"].GetInt();
    // TileSet
    map->tilewidth = document["tilewidth"].GetInt();
    map->width = document["layers"][0]["width"].GetInt();
}

MapLoad::~MapLoad()
{

}
