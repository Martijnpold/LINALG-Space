#include "AABB.hpp"

#include <limits>

namespace space::world {

    AABB::AABB(Vector min, Vector max)
        : _min {min}, _max {max}, _model {std::make_unique<Object>(create_model(min, max))} {
        if (!is_valid()) {
            throw std::logic_error {"Invalid min/max for AABB (min: " + _min.to_string() +
                                    ", max: " + _max.to_string() + ")"};
        }
    }

    bool AABB::intersects(const Vector& location, const AABB& other, const Vector& other_location) const {
        Vector min = _min + location;
        Vector max = _max + location;
        Vector other_min = other.min() + other_location;
        Vector other_max = other.max() + other_location;
        
        return (min.x <= other_max.x && max.x >= other_min.x) &&
                (min.y <= other_max.y && max.y >= other_min.y) &&
                (min.z <= other_max.z && max.z >= other_min.z);
    }

    AABB AABB::from_object(const Object& object) {
        float float_min = std::numeric_limits<float>::lowest();
        float float_max = std::numeric_limits<float>::max();

        Vector min {float_max, float_max, float_max};
        Vector max {float_min, float_min, float_min};

        for (const Polygon& surface : object.surfaces()) {
            for (const Vector& point : surface.points()) {
                min.x = std::min(point.x, min.x);
                min.y = std::min(point.y, min.y);
                min.z = std::min(point.z, min.z);
                max.x = std::max(point.x, max.x);
                max.y = std::max(point.y, max.y);
                max.z = std::max(point.z, max.z);
            }
        }

        return AABB(min, max);
    }

    bool AABB::is_valid() const {
        return _min.x < _max.x && _min.y < _max.y && _min.z < _max.z;
    }

    const Vector& AABB::min() const {
        return _min;
    }

    const Vector& AABB::max() const {
        return _max;
    }

    Object& AABB::model() const {
        return *_model;
    }

    Object AABB::create_model(const Vector& min, const Vector& max) {
        Object o;

        // bottom
        o.add(Polygon {{
                {min.x, min.y, min.z},
                {max.x, min.y, min.z},
                {max.x, min.y, max.z},
                {min.x, min.y, max.z},
        }});

        // top
        o.add(Polygon {{
                {min.x, max.y, min.z},
                {max.x, max.y, min.z},
                {max.x, max.y, max.z},
                {min.x, max.y, max.z},
        }});

        // back
        o.add(Polygon {{
                {min.x, min.y, min.z},
                {min.x, max.y, min.z},
                {max.x, max.y, min.z},
                {max.x, min.y, min.z},
        }});

        // front
        o.add(Polygon {{
                {min.x, min.y, max.z},
                {min.x, max.y, max.z},
                {max.x, max.y, max.z},
                {max.x, min.y, max.z},
        }});

        // left side
        o.add(Polygon {{
                {min.x, min.y, min.z},
                {min.x, min.y, max.z},
                {min.x, max.y, max.z},
                {min.x, max.y, min.z},
        }});

        // right side
        o.add(Polygon {{
                {max.x, min.y, min.z},
                {max.x, min.y, max.z},
                {max.x, max.y, max.z},
                {max.x, max.y, min.z},
        }});

        return o;
    }

} // namespace space::world