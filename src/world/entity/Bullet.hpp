#pragma once

#include "Entity.hpp"

namespace space::world {
    class Bullet : public Entity {
    private:
        int _ticksRemaining {100};

    public:
        explicit Bullet(World& world, Vector location, Vector heading, Vector pitch, Vector yaw, float velocity);
        void tick() override;
    };
} // namespace space::world