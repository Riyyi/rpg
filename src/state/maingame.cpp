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

    // Load map
    this->map = new Map();
    MapLoad mapLoad;
    mapLoad.Load(this->map, "data/map/level1.json");

    this->camera = new Camera();
    this->camera->SetNewView(window);
}

void MainGame::Update(sf::RenderWindow* window) {
    this->entityManager->Get("test0")->velocity.x = 0;
    this->entityManager->Get("test0")->velocity.y = 0;

    if(inputManager.IsPressed(InputManager::Left)) {
        std::cout << "LEFT" << std::endl;

        this->entityManager->Get("test0")->velocity.x = -1.5;
        this->camera->MoveCamera(window, sf::Vector2f(-1.5, 0));
    }

    if(inputManager.IsPressed(InputManager::Right)) {
        std::cout << "RIGHT" << std::endl;

        this->entityManager->Get("test0")->velocity.x = 1.5;
        this->camera->MoveCamera(window, sf::Vector2f(1.5, 0));
    }

    if(inputManager.IsPressed(InputManager::Up)) {
        std::cout << "UP" << std::endl;

        this->entityManager->Get("test0")->velocity.y = -1.5;
        this->camera->MoveCamera(window, sf::Vector2f(0, -1.5));
    }

    if(inputManager.IsPressed(InputManager::Down)) {
        std::cout << "DOWN" << std::endl;

        this->entityManager->Get("test0")->velocity.y = 1.5;
        this->camera->MoveCamera(window, sf::Vector2f(0, 1.5));
    }

    if(inputManager.IsPressed(InputManager::Up)
    && inputManager.IsPressed(InputManager::Down)) {
        this->entityManager->Get("test0")->velocity.x = 0;
        this->entityManager->Get("test0")->velocity.y = 0;
    }

    if(inputManager.IsPressed(InputManager::Left)
    && inputManager.IsPressed(InputManager::Right)) {
        this->entityManager->Get("test0")->velocity.x = 0;
        this->entityManager->Get("test0")->velocity.y = 0;
    }

//    if(inputManager.IsPressed(InputManager::Up)
//    && inputManager.IsPressed(InputManager::Right)) {
//        this->entityManager->Get("test0")->velocity.y = -1.125;
//        this->entityManager->Get("test0")->velocity.x = 1.125;
//    }

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
}
