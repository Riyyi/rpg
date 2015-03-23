#include "entitymanager.h"

EntityManager::EntityManager() {
}

void EntityManager::SetCollisionMethod(CollisionUpdateEvent collisionsEvent) {
    this->collisionsEvent = collisionsEvent;
}

void EntityManager::AddEntity(std::string name, Entity* entity) {
    std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
    while(found != this->entities.end()) {
        name += "0";
        found = this->entities.find(name);
    }

    this->entities.insert(std::make_pair(name, entity));
}

Entity* EntityManager::Get(std::string name) {
    std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
    if(found != this->entities.end()) {
        return found->second;
    }

    return NULL;
}

void EntityManager::Update() {
    std::vector<std::string> toRemove;

    for (auto& iterator : this->entities) {
        if (iterator.second != NULL) {
            if (this->collisionsEvent != NULL) {
                for (auto& iterator2 : this->entities) {
                    if (iterator != iterator2) {
                        if(iterator.second->Collision(iterator2.second)) {
                            this->collisionsEvent(iterator.second, iterator2.second);
                        }
                    }
                }
            }

            if (iterator.second->Active()) {
                iterator.second->Update();
            }
            else {
                toRemove.push_back(iterator.first);
            }
        }
    }

    while (toRemove.size() > 0) {
        this->entities.erase(toRemove[toRemove.size() - 1]);
        toRemove.pop_back();
    }

    toRemove.clear();
}


void EntityManager::Render(sf::RenderWindow* window, Camera *camera) {
    for(auto& iterator : this->entities) {
        if(iterator.second != NULL
        && iterator.second->Active()
        && camera->IsOnScreen(window, iterator.second)) {
            window->draw(*iterator.second);
        }
    }
}

EntityManager::~EntityManager() {
    for (auto& iterator : this->entities) {
        delete iterator.second;
    }

    this->entities.clear();
}
