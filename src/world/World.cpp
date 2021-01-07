#include "World.h"

namespace space::world {

    void World::add(std::unique_ptr<Entity>& entity) {
        _entities.push_back(std::move(entity));
    }

    std::vector<std::unique_ptr<Entity>> World::entities() const {
        return _entities;
    }

} // namespace space::world