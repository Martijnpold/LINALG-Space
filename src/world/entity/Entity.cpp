#include "Entity.hpp"

#include "world/World.hpp"

namespace space::world {

    Entity::Entity(std::unique_ptr<Object>& model, Vector heading)
        : _heading {heading}, _model {std::move(model)}, _hitbox {nullptr} {
        update_hitbox();
    }

    void Entity::move(const Vector& v) {
        _model->translate(v);
        _hitbox->move(v);
    }

    void Entity::move(float amount) {
        move(_heading * amount);
    }

    void Entity::roll(float angle) {
        _model->rotateVec(_heading, angle);
        update_hitbox();
    }

    void Entity::pitch(float angle) {
        // TODO
        update_hitbox();
    }

    void Entity::yaw(float angle) {
        // TODO
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