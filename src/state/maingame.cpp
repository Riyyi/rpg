#include "maingame.h"

void UpdateCollisions(Entity* entityA, Entity* entityB) {
    std::cout << "Collisions!" << std::endl;
}

void MainGame::Initialize(sf::RenderWindow* window) {
    this->entityManager = new EntityManager();
    this->entityManager->SetCollisionMethod(UpdateCollisions);

    // Add entities
    this->entityManager->AddEntity("test", new Entity("data/gfx/test.png"));
    this->entityManager->AddEntity("test", new Entity("data/gfx/test.png"));
    this->entityManager->Get("test0")->velocity.x = 0.5;
    this->entityManager->Get("test")->setPosition(sf::Vector2f(50, 50));
    this->entityManager->Get("test0")->setPosition(sf::Vector2f(50, 300));

    // Load Map
    this->map = new Map();
    MapLoad mapLoad;
    mapLoad.Load(this->map, "data/map/level1.json");

    // Load Camera
    this->camera = new Camera();
    this->camera->SetNewView(window);

    // Load Player
    this->player = new Player(this->entityManager, this->map, this->camera, 100, 100);
    this->entityManager->AddEntity("Player", this->player);
}

void MainGame::Update(sf::RenderWindow* window) {
    this->player->Update(window, inputManager);
    this->entityManager->Update();

    if(inputManager.IsPressed(InputManager::LoadMap)) {
        std::cout << "Loading Map..." << std::endl;
        MapLoad mapLoad;
        mapLoad.Load(this->map, "data/map/level1.json");
    }
}

void MainGame::Render(sf::RenderWindow* window) {
    this->map->Render(window);
    this->entityManager->Render(window);
}

void MainGame::Destroy(sf::RenderWindow* window) {
    delete this->entityManager;
    delete this->map;
    delete this->camera;
}
