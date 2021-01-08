#include "Entity.hpp"

#include "world/World.hpp"

namespace space::world {
    Entity::Entity(World& world, std::unique_ptr<Object> model, Vector location)
        : Entity(world, std::move(model), location, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}) {
        update_hitbox();
    }

    Entity::Entity(World& world, std::unique_ptr<Object> model, Vector location, Vector heading, Vector pitch,
                   Vector yaw)
        : _world {world}, _location {location}, _heading {heading}, _pitch {pitch}, _yaw {yaw},
          _model {std::move(model)}, _hitbox {nullptr} {
        update_hitbox();
    }

    void Entity::tick() {
        move(-_velocity);
    }

    void Entity::move_global(const Vector& v) {
        _location += v;
    }

    void Entity::place(const Vector& location) {
        _location = location;
    }

    void Entity::move(float amount) {
        move_global(_heading * amount);
    }

    void Entity::roll(float angle) {
        _model->rotateVec(_heading, angle);

        Matrix rotation = Matrix::createRotationMatrixVec(_heading, angle);
        _pitch *= rotation;
        _yaw *= rotation;

        update_hitbox();
    }

    void Entity::pitch(float angle) {
        _model->rotateVec(_pitch, angle);

        Matrix rotation = Matrix::createRotationMatrixVec(_pitch, angle);
        _heading *= rotation;
        _yaw *= rotation;

        update_hitbox();
    }

    void Entity::yaw(float angle) {
        _model->rotateVec(_yaw, angle);

        Matrix rotation = Matrix::createRotationMatrixVec(_yaw, angle);
        _heading *= rotation;
        _pitch *= rotation;

        update_hitbox();
    }

    void Entity::update_hitbox() {
        if (_model) {
            _hitbox = std::make_unique<AABB>(AABB::from_object(*_model));
        } else {
            _hitbox = nullptr;
        }
    }

    bool Entity::collides_with(const Entity& other) const {
        if (!_hitbox) {
            return false;
        }

        return _hitbox->intersects(_location, other.hitbox(), other.location());
    }

    const Vector& Entity::location() const {
        return _location;
    }

    Object& Entity::model() const {
        return *_model;
    }

    AABB& Entity::hitbox() const {
        return *_hitbox;
    }

    Vector Entity::heading() const {
        return _heading;
    }

    Vector Entity::position() const {
        return _model->center();
    }

    void Entity::setVelocity(float velocity) {
        _velocity = velocity;
    }

    float Entity::getVelocity() const {
        return _velocity;
    }
} // namespace space::world