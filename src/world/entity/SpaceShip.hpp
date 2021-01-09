#pragma once

#include "Entity.hpp"

namespace space::world {
    class SpaceShip : public Entity {
    public:
        explicit SpaceShip(World& world);

        void shoot();
        void tick() override;
    };
}