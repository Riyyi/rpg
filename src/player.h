#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "entitymanager.h"
#include "inputmanager.h"
#include "map.h"

class Player : public Entity
{
public:
    Player(EntityManager* entityManager, Map* map, Camera* camera, float x = 0, float y = 0);
    void Update(sf::RenderWindow *window, InputManager inputManager, int elapsedTime);
    float SetSpeed();
    int GetHealth();
    int GetMaxHealth();
    ~Player();

private:
    EntityManager* entityManager;
    Map* map;
    Camera* camera;
    int health;
    int maxHealth;
    float speed;
    //float direction;
};

#endif // PLAYER_H
