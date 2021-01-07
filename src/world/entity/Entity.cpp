#include "Entity.hpp"

#include "world/World.hpp"

namespace space::world {

    Entity::Entity(std::unique_ptr<Object>& model, Vector heading) : _heading {heading}, _model {std::move(model)} {
    }

    void Entity::move(const Vector& v) {
        _model->translate(v);
        // TODO: move hitbox
    }

    void Entity::move(float amount) {
        move(_heading * amount);
    }

    void Entity::roll(float angle) {
        _model->rotateVec(_heading, angle);
        // TODO: update hitbox
    }

    void Entity::pitch(float angle) {
        // TODO
    }

    void Entity::yaw(float angle) {
        // TODO
    }

    void Entity::link_world(World* world) {
        _world = world;
    }

    Object& Entity::model() const {
        return *_model;
    }

    Vector Entity::heading() const {
        return _heading;
    }

    Vector Entity::position() const {
        return _model->center();
    }

} // namespace space::world