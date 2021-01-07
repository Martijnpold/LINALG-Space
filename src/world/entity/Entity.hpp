#pragma once

#include "math/Vector.hpp"
#include "world/Object.hpp"

using namespace space::math;

namespace space::world {

    class Entity {
    private:
        Vector _heading {0, 1 ,0};
        std::unique_ptr<Object> _model;

    public:
        explicit Entity(std::unique_ptr<Object>& model);

        Object& model() const;
        /// The center point of the underlying model
        Vector position() const;
        Vector heading() const;
    };

}
