#pragma once

#include "Entity.hpp"

namespace space::world {
    class SpaceShip : public Entity {
    public:
        using Entity::Entity;

        void shoot();
    };
}