#ifndef MAINGAME_H
#define MAINGAME_H

#include <iostream>

#include "gamestate.h"
#include "entitymanager.h"
#include "inputmanager.h"

class MainGame : public GameState
{
public:
    void Initialize(sf::RenderWindow* window);
    void Update(sf::RenderWindow* window);
    void Render(sf::RenderWindow* window);
    void Destroy(sf::RenderWindow* window);

private:
    EntityManager* entityManager;
};

#endif // MAINGAME_H
