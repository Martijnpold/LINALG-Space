#pragma once

#include "math/Vector.hpp"
#include "world/AABB.hpp"
#include "world/Object.hpp"

#include <memory>

using namespace space::math;

namespace space::world {

    class World; // forward declare

    class Entity {
    private:
        Vector _heading;
        Vector _pitch;
        Vector _yaw;

        std::unique_ptr<Object> _model;
        std::unique_ptr<AABB> _hitbox;

        World& _world;

    public:
        explicit Entity(World& world, std::unique_ptr<Object>& model);
        Entity(World& world, std::unique_ptr<Object>& model, Vector heading, Vector pitch, Vector yaw);

        /// Move the entity in global space
        void move(const Vector& v);
        /// Move the entity in the direction of its heading
        void move(float amount);

        /// Rotate around heading (angle in radians)
        void roll(float angle);
        /// Rotate up/down (angle in radians)
        void pitch(float angle);
        ///Rotate left/right (angle in radians)
        void yaw(float angle);

        Object& model() const;
        AABB& hitbox() const;
        /// The center point of the underlying model
        Vector position() const;
        Vector heading() const;

    private:
        void update_hitbox();
    };

} // namespace space::world
