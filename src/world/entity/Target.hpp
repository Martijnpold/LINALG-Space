#pragma once

#include "Entity.hpp"

namespace space::world {
    class Target : public Entity {
    public:
        explicit Target(World& world);
    };
}