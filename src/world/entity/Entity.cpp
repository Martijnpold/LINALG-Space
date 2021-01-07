#include "Entity.hpp"

namespace space::world {

    Entity::Entity(std::unique_ptr<Object>& model) : _model {std::move(model)} {
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