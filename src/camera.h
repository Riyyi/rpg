#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    void SetNewView(sf::RenderWindow *window);
    void MoveCamera(sf::RenderWindow *window, sf::Vector2f move);
    void SetCenter(sf::RenderWindow *window, sf::Vector2f position);

private:
    //sf::Vector2f position;
    sf::View view;
};

#endif // CAMERA_H
