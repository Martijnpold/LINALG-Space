#pragma once

#include "entity/Entity.hpp"

#include <vector>

namespace space::world {

    class World {
    private:
        std::vector<std::unique_ptr<Entity>> _entities;

    public:
        void add(std::unique_ptr<Entity>& entity);
        std::vector<std::unique_ptr<Entity>> entities() const;
    };

} // namespace space::world
