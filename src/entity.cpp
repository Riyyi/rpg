#include "entity.h"

Entity::Entity() {
    this->active = 1;
    this->texture = new sf::Texture();
}

Entity::Entity(std::string fileName) {
    this->active = 1;
    this->texture = new sf::Texture;
    this->Load(fileName);
    this->setOrigin((this->texture->getSize().x / 2), (this->texture->getSize().y / 2));
}

Entity::Entity(std::string fileName, sf::IntRect rect) {
    this->active = 1;
    this->texture = new sf::Texture();
    this->Load(fileName, rect);
    this->setOrigin((this->texture->getSize().x / 2), (this->texture->getSize().y / 2));
}

void Entity::Load(std::string fileName) {
    this->texture->loadFromFile(fileName, sf::IntRect());
    this->setTexture(*this->texture);
}

void Entity::Load(std::string fileName, sf::IntRect rect) {
    this->texture->loadFromFile(fileName, rect);
    this->setTexture(*this->texture);
}

bool Entity::Collision(Entity *entity) {
    if(entity != NULL) {
        return this->getGlobalBounds().intersects(entity->getGlobalBounds());
    }

    return false;
}

void Entity::SetActive(int active) {
    this->active = active;
}

int Entity::Active() {
    return this->active;
}

int Entity::Group() {
    return this->groupId;
}

void Entity::Update() {
    this->move(this->velocity);
}

Entity::~Entity() {
    delete this->texture;
}
