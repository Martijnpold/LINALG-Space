#include "Entity.hpp"

#include "world/World.hpp"

namespace space::world {

    Entity::Entity(std::unique_ptr<Object>& model) : Entity(model, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}) {
        update_hitbox();
    }

    Entity::Entity(std::unique_ptr<Object>& model, Vector heading, Vector pitch, Vector yaw)
        : _heading {heading}, _pitch {pitch}, _yaw {yaw}, _model {std::move(model)}, _hitbox {nullptr} {
        update_hitbox();
    }

    void Entity::move(const Vector& v) {
        // TODO: don't move the model, instead do this when rendering?
        _model->translate(v);
        _hitbox->move(v);
    }

    void Entity::move(float amount) {
        move(_heading * amount);
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
        _hitbox = std::make_unique<AABB>(AABB::from_object(*_model));
    }

    void Entity::link_world(World* world) {
        _world = world;
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

} // namespace space::world