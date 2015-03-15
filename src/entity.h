#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
public:
    Entity() {
        this->active = 1;
        this->texture = new sf::Texture();
    }

    Entity(std::string fileName) {
        this->active = 1;
        this->texture = new sf::Texture;
        this->Load(fileName);
    }

    Entity(std::string fileName, sf::IntRect rect) {
        this->active = 1;
        this->texture = new sf::Texture();
        this->Load(fileName, rect);
    }

    void Load(std::string fileName) {
        this->texture->loadFromFile(fileName, sf::IntRect());
        this->setTexture(*this->texture);
    }

    void Load(std::string fileName, sf::IntRect rect) {
        this->texture->loadFromFile(fileName, rect);
        this->setTexture(*this->texture);
    }

    bool Collision(Entity *entity) {
        if(entity != NULL) {
            return this->getGlobalBounds().intersects(entity->getGlobalBounds());
        }

        return false;
    }

    void SetActive(int active) {
        this->active = active;
    }

    int Active() {
        return this->active;
    }

    int Group() {
        return this->groupId;
    }

    virtual void Update() {
        this->move(this->velocity);
    }

    ~Entity() {
        delete this->texture;
    }

    sf::Vector2f velocity;

protected:
    int active, groupId;

private:
    sf::Texture* texture;
};

#endif // ENTITY_H
