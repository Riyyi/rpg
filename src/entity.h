#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
public:
    Entity();
    Entity(std::string fileName);
    Entity(std::string fileName, sf::IntRect rect);
    void Load(std::string fileName);
    void Load(std::string fileName, sf::IntRect rect);
    bool Collision(Entity *entity);
    void SetActive(int active);
    int Active();
    int Group();
    virtual void Update();
    ~Entity();

    sf::Vector2f velocity;

protected:
    int active, groupId;

private:
    sf::Texture* texture;
};

#endif // ENTITY_H
