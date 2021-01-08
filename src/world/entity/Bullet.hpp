#pragma once

#include "Entity.hpp"

namespace space::world {
    class Bullet : public Entity {
    public:
        explicit Bullet(World& world, Vector location, Vector heading, Vector pitch, Vector yaw, float velocity);
    };
}