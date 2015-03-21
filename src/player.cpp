#include "player.h"

Player::Player(EntityManager* entityManager, Map *map, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->map = map;
    this->camera = camera;

    this->Load("data/gfx/player.png");
    this->setPosition(x, y);
    this->speed = 0.00015f;
}

void Player::Update(sf::RenderWindow* window, InputManager inputManager, int elapsedTime) {
    float speed = this->speed * elapsedTime;
    // Update player velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * speed -
                       inputManager.IsPressed(InputManager::Left) * speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * speed -
                       inputManager.IsPressed(InputManager::Up) * speed;

    // Set correct speed on diagonal movement
    if((this->velocity.x == speed || this->velocity.x == -speed)
    && (this->velocity.y == speed || this->velocity.y == -speed)) {
        this->velocity.x *= .75;
        this->velocity.y *= .75;
    }
}

Player::~Player()
{

}
