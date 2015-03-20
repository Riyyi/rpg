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

void Camera::SetCenter(sf::RenderWindow *window, sf::Vector2f position) {
    this->view.setCenter(position.x, position.y);
    window->setView(view);
}
