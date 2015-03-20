#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <unordered_map>
#include <vector>

#include "entity.h"

typedef void CollisionUpdateEvent(Entity* entityA, Entity* entityB);

class EntityManager
{
public:
    EntityManager();
    void SetCollisionMethod(CollisionUpdateEvent collisionsEvent);
    void AddEntity(std::string name, Entity* entity);
    Entity* Get(std::string name);
    void Update();
    void Render(sf::RenderWindow* window);
    ~EntityManager();

private:
    std::unordered_map<std::string, Entity*> entities;
    CollisionUpdateEvent* collisionsEvent;
};

#endif // ENTITYMANAGER

