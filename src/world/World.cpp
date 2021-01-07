#include "World.hpp"

#include <algorithm>

namespace space::world {

    void World::add(std::unique_ptr<Entity>& entity) {
        entity->link_world(this);
        _entities.push_back(std::move(entity));
    }

    std::vector<std::unique_ptr<Entity>>& World::entities() {
        return _entities;
    }

} // namespace space::world