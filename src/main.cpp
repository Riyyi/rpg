#include <iostream>
#include <SFML/Graphics.hpp>

#include "inputmanager.h"
#include "entitymanager.h"

InputManager inputManager;

void UpdateCollisions(Entity* entityA, Entity* entityB) {
    std::cout << "Collisions!" << std::endl;
}

int main()
{
    std::cout << "Hello World!" << std::endl;

    std::string gameName = "rpg";
    unsigned int windowStyle = sf::Style::Titlebar | sf::Style::Close;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(1280, 720), gameName, windowStyle, settings);
    window.setVerticalSyncEnabled(true);

    sf::Clock fpsTimer;
    sf::Clock timer;
    sf::Time timeElapsed;

    EntityManager entityManager;
    entityManager.AddEntity("test", new Entity("data\\gfx\\test.png"));
    entityManager.AddEntity("test", new Entity("data\\gfx\\test.png"));
    entityManager.SetCollisionMethod(UpdateCollisions);

//    Entity entity;
//    entity.Load("data\\gfx\\test.png");

//    Entity entity2;
//    entity2.Load("data\\gfx\\test.png");

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            // Enter fullscreen mode : key combination : Alt+Enter
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
                        if (windowStyle == sf::Style::Fullscreen) {
                            windowStyle = sf::Style::Titlebar | sf::Style::Close;
                        }
                        else {
                            windowStyle = sf::Style::Fullscreen;
                        }

                        window.create(sf::VideoMode(1280, 720), gameName, windowStyle, settings);
                        window.setVerticalSyncEnabled(true);
                    }
                }
            }

            if(inputManager.IsPressed(InputManager::Left)) {
                std::cout << "LEFT" << std::endl;
            }

            if(inputManager.IsPressed(InputManager::Down)) {
                std::cout << "DOWN" << std::endl;
            }
        }

//        if(entity.Collision(&entity2)) {
//            std::cout << "COLLISION!" << std::endl;
//        }

        window.clear(sf::Color(72, 152, 72));

//        window.draw(entity);
//        window.draw(entity2);

        entityManager.Render(&window);

        window.display();

        timeElapsed = timer.getElapsedTime();
        if (timeElapsed.asSeconds() > 1)
        {
            // Display current FPS in window title
            timeElapsed = fpsTimer.getElapsedTime();
            int fps = 1000000 / timeElapsed.asMicroseconds();
            window.setTitle(gameName + " - fps: " + std::to_string(fps));

            timer.restart();
        }

        fpsTimer.restart();
    }

    return 0;
}

