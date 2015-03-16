#include "maingame.h"

void UpdateCollisions(Entity* entityA, Entity* entityB) {
    std::cout << "Collisions!" << std::endl;
}

void MainGame::Initialize(sf::RenderWindow* window) {
    entityManager = new EntityManager();
    entityManager->SetCollisionMethod(UpdateCollisions);

    this->entityManager->AddEntity("test", new Entity("data\\gfx\\test.png"));
    this->entityManager->AddEntity("test", new Entity("data\\gfx\\test.png"));
    this->entityManager->Get("test0")->velocity.x = 0.5;
    this->entityManager->Get("test")->setPosition(sf::Vector2f(50, 50));
}

void MainGame::Update(sf::RenderWindow* window) {
    if(inputManager.IsPressed(InputManager::Left)) {
        std::cout << "LEFT" << std::endl;
    }

    if(inputManager.IsPressed(InputManager::Down)) {
        std::cout << "DOWN" << std::endl;
    }

    this->entityManager->Update();
}

void MainGame::Render(sf::RenderWindow* window) {
    this->entityManager->Render(window);
}

void MainGame::Destroy(sf::RenderWindow* window) {
    delete this->entityManager;
}
