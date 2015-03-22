#include "camera.h"

Camera::Camera(sf::RenderWindow *window) {
    this->view = sf::View(sf::FloatRect(0, 0, 1280, 720));
    window->setView(view);
}

void Camera::MoveCamera(sf::RenderWindow *window, sf::Vector2f move) {
    this->view.move(move.x, move.y);
    window->setView(view);
}

void Camera::SetCenter(sf::RenderWindow *window, sf::Vector2f position) {
    this->view.setCenter(position.x, position.y);
    window->setView(view);
}

void Camera::Update(sf::RenderWindow *window, Map *map, sf::Vector2f position) {
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
    sf::Vector2f windowCenterEnd = sf::Vector2f(map->width * map->tileWidth - windowCenterStart.x,
                                                map->height * map->tileHeight - windowCenterStart.y);

    // If Player is in the center (4)
    if(position.x > windowCenterStart.x
    && position.y > windowCenterStart.y
    && position.x < windowCenterEnd.x
    && position.y < windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(position.x, position.y));
    }

    // If Player is in the edge (2,3)
    // Middle Top
    else if(position.x > windowCenterStart.x
    && position.x < windowCenterEnd.x
    && position.y < windowCenterStart.y) {
        this->SetCenter(window, sf::Vector2f(position.x, windowCenterStart.y));
    }
    // Middle Bottom
    else if(position.x > windowCenterStart.x
    && position.x < windowCenterEnd.x
    && position.y > windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(position.x, windowCenterEnd.y));
    }
    // Middle Left
    else if(position.y > windowCenterStart.y
    && position.y < windowCenterEnd.y
    && position.x < windowCenterStart.x) {
        this->SetCenter(window, sf::Vector2f(windowCenterStart.x, position.y));
    }
    // Middle Right
    else if(position.y > windowCenterStart.y
    && position.y < windowCenterEnd.y
    && position.x > windowCenterEnd.x) {
        this->SetCenter(window, sf::Vector2f(windowCenterEnd.x, position.y));
    }

    // If Player is in one of the corners (1)
    // Top Left
    else if(position.x < windowCenterStart.x
    && position.y < windowCenterStart.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterStart.x, windowCenterStart.y));
    }
    // Top Right
    else if(position.x > windowCenterEnd.x
    && position.y < windowCenterStart.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterEnd.x, windowCenterStart.y));
    }
    // Bottom Left
    else if(position.x < windowCenterStart.x
    && position.y > windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterStart.x, windowCenterEnd.y));
    }
    // Bottom Right
    else if(position.x > windowCenterEnd.x
    && position.y > windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterEnd.x, windowCenterEnd.y));
    }
}

Camera::~Camera()
{

}
