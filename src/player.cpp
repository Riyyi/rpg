#include "player.h"

Player::Player(EntityManager* entityManager, Map *map, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->map = map;
    this->camera = camera;

    this->Load("data/gfx/player.png");
    this->setPosition(x, y);
    this->speed = 1.5f;
}

void Player::Update(sf::RenderWindow* window, InputManager inputManager) {
    // Store currect location of the player for the Camera to use
    sf::Vector2f playerPosition = sf::Vector2f(this->getPosition().x, this->getPosition().y);;

    // Update player velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * this->speed -
                       inputManager.IsPressed(InputManager::Left) * this->speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * this->speed -
                       inputManager.IsPressed(InputManager::Up) * this->speed;

    // Update camera position
    //|------------|--------------|------------|
    //|     1      |      2       |     1      |
    //|            |              |            |
    //|------------x--------------|------------|
    //|     3      |      4       |     3      |
    //|            |              |            |
    //|------------|--------------y------------|
    //|     1      |      2       |     1      |
    //|            |              |            |
    //|------------|--------------|------------|

    // Get window center start and end
    // x on map scetch
    sf::Vector2f windowCenterStart = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    // y on map scetch
    sf::Vector2f windowCenterEnd = sf::Vector2f(map->width * map->tilewidth - windowCenterStart.x,
                                                map->height * map->tileheight - windowCenterStart.y);

    // If Player is in the center (4)
    if(playerPosition.x > windowCenterStart.x
    && playerPosition.y > windowCenterStart.y
    && playerPosition.x < windowCenterEnd.x
    && playerPosition.y < windowCenterEnd.y) {
        camera->SetCenter(window, sf::Vector2f(playerPosition.x, playerPosition.y));
    }

    // If Player is in the edge (2,3)
    // Middle Top
    else if(playerPosition.x > windowCenterStart.x
    && playerPosition.x < windowCenterEnd.x
    && playerPosition.y < windowCenterStart.y) {
        camera->SetCenter(window, sf::Vector2f(playerPosition.x, windowCenterStart.y));
    }
    // Middle Bottom
    else if(playerPosition.x > windowCenterStart.x
    && playerPosition.x < windowCenterEnd.x
    && playerPosition.y > windowCenterEnd.y) {
        camera->SetCenter(window, sf::Vector2f(playerPosition.x, windowCenterEnd.y));
    }
    // Middle Left
    else if(playerPosition.y > windowCenterStart.y
    && playerPosition.y < windowCenterEnd.y
    && playerPosition.x < windowCenterStart.x) {
        camera->SetCenter(window, sf::Vector2f(windowCenterStart.x, playerPosition.y));
    }
    // Middle Right
    else if(playerPosition.y > windowCenterStart.y
    && playerPosition.y < windowCenterEnd.y
    && playerPosition.x > windowCenterEnd.x) {
        camera->SetCenter(window, sf::Vector2f(windowCenterEnd.x, playerPosition.y));
    }

    // If Player is in one of the corners (1)
    // Top Left
    else if(playerPosition.x < windowCenterStart.x
    && playerPosition.y < windowCenterStart.y) {
        camera->SetCenter(window, sf::Vector2f(windowCenterStart.x, windowCenterStart.y));
    }
    // Top Right
    else if(playerPosition.x > windowCenterEnd.x
    && playerPosition.y < windowCenterStart.y) {
        camera->SetCenter(window, sf::Vector2f(windowCenterEnd.x, windowCenterStart.y));
    }
    // Bottom Left
    else if(playerPosition.x < windowCenterStart.x
    && playerPosition.y > windowCenterEnd.y) {
        camera->SetCenter(window, sf::Vector2f(windowCenterStart.x, windowCenterEnd.y));
    }
    // Bottom Right
    else if(playerPosition.x > windowCenterEnd.x
    && playerPosition.y > windowCenterEnd.y) {
        camera->SetCenter(window, sf::Vector2f(windowCenterEnd.x, windowCenterEnd.y));
    }
}

Player::~Player()
{

}
