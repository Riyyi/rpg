#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::SetNewView(sf::RenderWindow *window) {
    this->view = sf::View(sf::FloatRect(0, 0, 1280, 720));
    window->setView(view);
}

void Camera::MoveCamera(sf::RenderWindow *window, sf::Vector2f move) {
    this->view.move(move.x, move.y);
    window->setView(view);
}
