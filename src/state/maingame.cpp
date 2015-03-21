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
    MapLoad(this->map, "data/map/level1.json");

    // Load Camera
    this->camera = new Camera(window);

    // Load Player
    this->player = new Player(this->entityManager, this->map, this->camera, 100, 100);
    this->entityManager->AddEntity("Player", this->player);
}

void MainGame::Update(sf::RenderWindow* window) {
    this->time = this->clock.getElapsedTime();
    int timeElapsed = this->time.asMicroseconds();
    this->clock.restart();

    this->player->Update(window, inputManager, timeElapsed);
    this->entityManager->Update();
    this->camera->Update(window, this->map, sf::Vector2f(this->player->getPosition().x, this->player->getPosition().y));

    if(inputManager.IsPressed(InputManager::LoadMap)) {
        std::cout << "Loading Map..." << std::endl;
        MapLoad(this->map, "data/map/level1.json", 1);
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
