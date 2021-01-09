#include "World.hpp"

#include <algorithm>

namespace space::world {
    void World::tick() {
        for (auto& e : _entities) {
            e->tick();
        }

        for (Entity* ent : _toRemove) {
            _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [&ent](auto i) { return i && (i == ent); }),
                           _bullets.end());
            _targets.erase(std::remove_if(_targets.begin(), _targets.end(), [&ent](auto i) { return i && (i == ent); }),
                           _targets.end());
            _entities.erase(std::remove_if(_entities.begin(), _entities.end(),
                                           [&ent](auto& i) { return i && (i.get() == ent); }),
                            _entities.end());
        }
        _toRemove.clear();
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

    void World::remove(Entity& ent) {
        _toRemove.emplace_back(&ent);
    }
} // namespace space::world