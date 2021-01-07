#pragma once

#include "math/Vector.hpp"
#include "Object.hpp"

using namespace space::math;

namespace space::world {

    class AABB {
    private:
        Vector _min;
        Vector _max;

        std::unique_ptr<Object> _model; // renderable object

    public:
        AABB(Vector min, Vector max);
        static AABB from_object(const Object& object);

        bool collides_with(const AABB& other) const;
        void move(const Vector& v);

        Object& model() const;

    private:
        static Object create_model(const Vector& min, const Vector& max);
    };

}
