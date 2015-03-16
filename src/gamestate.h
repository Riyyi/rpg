#ifndef GAMESTATE
#define GAMESTATE

#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual void Initialize(sf::RenderWindow* window) {
    }

    virtual void Update(sf::RenderWindow* window) {
    }

    virtual void Render(sf::RenderWindow* window) {
    }

    virtual void Destroy(sf::RenderWindow* window) {
    }
};

class GameStateParent
{
public:
    GameStateParent() {
        this->state = NULL;
    }

    void SetWindow(sf::RenderWindow* window) {
        this->window = window;
    }

    void SetState(GameState* state) {
        if(this->state != NULL) {
            this->state->Destroy(this->window);
        }

        this->state = state;
        if(this->state != NULL) {
            this->state->Initialize(this->window);
        }
    }

    void Update() {
        if(this->state != NULL) {
            this->state->Update(this->window);
        }
    }

    void Render() {
        if(this->state != NULL) {
            this->state->Render(this->window);
        }
    }

    ~GameStateParent() {
        if(this->state != NULL) {
            this->state->Destroy(this->window);
        }
    }


private:
    sf::RenderWindow* window;
    GameState* state;
};

extern GameStateParent gameState;

#endif // GAMESTATE

