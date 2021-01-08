#include "World.hpp"

#include <algorithm>

namespace space::world {
    void World::tick() {
        for(auto& e : _entities) {
            e->tick();
        }
    }

    std::vector<std::unique_ptr<Entity>>& World::entities() {
        return _entities;
    }

    SpaceShip* World::spaceship() {
        return _spaceShip;
    }

    std::vector<Bullet*> World::bullets() {
        return _bullets;
    }

    std::vector<Target*> World::targets() {
        return _targets;
    }
} // namespace space::world