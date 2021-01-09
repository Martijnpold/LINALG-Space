#pragma once

#include "Entity.hpp"

namespace space::world {
    class Target : public Entity {
    private:
        inline static const float SCALE_ADJUSTMENT {0.01};
        inline static const float MAX_SCALE {2};
        inline static const float MIN_SCALE {1};

        float _scale {MIN_SCALE};
        bool _scaling_up {true};

    public:
        explicit Target(World& world);

        void tick() override;
    };
}