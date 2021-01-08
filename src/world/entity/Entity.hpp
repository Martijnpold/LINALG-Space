#pragma once

#include "math/Vector.hpp"
#include "world/AABB.hpp"
#include "world/Object.hpp"

#include <memory>

using namespace space::math;

namespace space::world {

    class World; // forward declare

    class Entity {
    protected:
        Vector _heading;
        Vector _pitch;
        Vector _yaw;
        float _velocity {0};

        Vector _location;

        std::unique_ptr<Object> _model;
        std::unique_ptr<AABB> _hitbox;

        World& _world;

        void update_hitbox();

    public:
        explicit Entity(World& world, std::unique_ptr<Object> model, Vector location = {0, 0, 0});
        Entity(World& world, std::unique_ptr<Object> model, Vector location, Vector heading, Vector pitch, Vector yaw);

        void tick();

        /// Move the entity in the direction of its heading
        void move(float amount);

        void place(const Vector& location);
        void move_global(const Vector& v);

        /// Rotate around heading (angle in radians)
        void roll(float angle);
        /// Rotate up/down (angle in radians)
        void pitch(float angle);
        ///Rotate left/right (angle in radians)
        void yaw(float angle);

        const Vector& location() const;
        Object& model() const;
        AABB& hitbox() const;
        /// The center point of the underlying model
        Vector position() const;
        Vector heading() const;

        void setVelocity(float velocity);
        float getVelocity() const;
    };

} // namespace space::world
