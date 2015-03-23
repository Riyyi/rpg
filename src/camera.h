#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

#include "map.h"

class Camera
{
public:
    Camera(sf::RenderWindow *window);
    void MoveCamera(sf::RenderWindow *window, sf::Vector2f move);
    void SetCenter(sf::RenderWindow *window, sf::Vector2f position);
    void Update(sf::RenderWindow *window, Map *map, sf::Vector2f position);
    bool IsOnScreen(sf::RenderWindow *window, Entity *entity);
    ~Camera();

private:
    //sf::Vector2f position;
    sf::View view;
};

#endif // CAMERA_H
