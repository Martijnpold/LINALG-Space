#pragma once

#include "math/Vector.hpp"
#include "world/Object.hpp"
#include "world/AABB.hpp"

#include <memory>

using namespace space::math;

namespace space::world {

    class World; // forward declare

    class Entity {
    private:
        Vector _heading;

        std::unique_ptr<Object> _model;
        std::unique_ptr<AABB> _hitbox;

        World* _world {nullptr}; // TODO: no raw pointer?

    public:
        explicit Entity(std::unique_ptr<Object>& model, Vector heading = {0, 1, 0});

        /// Move the entity in global space
        void move(const Vector& v);
        /// Move the entity in the direction of its heading
        void move(float amount);

        /**
         * Rotate around heading
         * @param angle (in radians)
         */
        void roll(float angle);

        /**
         * Rotate up/down
         * @param angle
         */
        void pitch(float angle);

        /**
         * Rotate left/right
         * @param angle
         */
        void yaw(float angle);

        void link_world(World* world);

        Object& model() const;
        AABB& hitbox() const;
        /// The center point of the underlying model
        Vector position() const;
        Vector heading() const;

    private:
        void update_hitbox();
    };

} // namespace space::world
