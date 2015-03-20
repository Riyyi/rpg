#include "player.h"

Player::Player(EntityManager* entityManager, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->camera = camera;

    this->Load("data/gfx/player.png");
    this->setPosition(x, y);
    this->speed = 1.5f;
}

void Player::Update(sf::RenderWindow* window, InputManager inputManager) {
    // Store currect location of the player for the Camera to use
    sf::Vector2f cameraPosition = sf::Vector2f(this->getPosition().x, this->getPosition().y);

    // Update player velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * this->speed -
                       inputManager.IsPressed(InputManager::Left) * this->speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * this->speed -
                       inputManager.IsPressed(InputManager::Up) * this->speed;

    // Update camera position
    // VERSION 1!
//    if(this->getPosition().x + 16 > window->getSize().x / 2) {
//        this->camera->MoveCamera(window, sf::Vector2f(this->velocity.x, 0));
//    }
//    else {
//        camera->SetCenter(window, sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
//    }

//    if(this->getPosition().y + 16 > window->getSize().y / 2) {
//        this->camera->MoveCamera(window, sf::Vector2f(0, this->velocity.y));
//    }
//    else {
//        camera->SetCenter(window, sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
//    }
    //

    // VERSION 2!
//    if(this->getPosition().x < window->getSize().x / 2
//    && this->getPosition().y < window->getSize().y / 2) {
//        camera->SetCenter(window, sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
//    }

//    if(this->getPosition().x> window->getSize().x / 2
//    && this->getPosition().y> window->getSize().y / 2) {
//        //this->camera->MoveCamera(window, sf::Vector2f(this->velocity.x, this->velocity.y));
//        camera->SetCenter(window, sf::Vector2f(this->getPosition().x, this->getPosition().y));
//    }
//    else if(this->getPosition().x> window->getSize().x / 2) {
//        this->camera->MoveCamera(window, sf::Vector2f(this->velocity.x, 0));
//    }
//    else if(this->getPosition().y> window->getSize().y / 2) {
//        this->camera->MoveCamera(window, sf::Vector2f(0, this->velocity.y));
//    }
    //

    // VERSION 3!
    if(this->getPosition().x < window->getSize().x / 2
    && this->getPosition().y < window->getSize().y / 2) {
        camera->SetCenter(window, sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
    }

    if(this->getPosition().x> window->getSize().x / 2
    && this->getPosition().y> window->getSize().y / 2) {
        //this->camera->MoveCamera(window, sf::Vector2f(this->velocity.x, this->velocity.y));
        camera->SetCenter(window, sf::Vector2f(this->getPosition().x, this->getPosition().y));
    }
    else {
        if(this->getPosition().x> window->getSize().x / 2) {
            this->camera->MoveCamera(window, sf::Vector2f(this->velocity.x, 0));
        }

        if(this->getPosition().y> window->getSize().y / 2) {
            this->camera->MoveCamera(window, sf::Vector2f(0, this->velocity.y));
        }
    }
    //

    // VERSION 4!
        // @Todo
    //

//    sf::Vertex2f tempPlayerLoc;
//    if(playerLoc.x != edge X)
//    {
//        tempPlayerLoc.x = playerLoc.x
//    }
//    if(playerLoc.y != edge Y)
//    {
//        tempPlayerLoc.y = playerLoc.y
//    }
//    view->setCenter(playerLoc)
}

Player::~Player()
{

}
