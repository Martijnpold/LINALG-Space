#pragma once

#include "Object.hpp"
#include "math/Vector.hpp"

#include <memory>

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

        bool intersects(const Vector& location, const AABB& other, const Vector& other_location) const;
        bool is_valid() const;

        Object& model() const;

    protected:
        const Vector& min() const;
        const Vector& max() const;

    private:
        static Object create_model(const Vector& min, const Vector& max);
    };

} // namespace space::world
