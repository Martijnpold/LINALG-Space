#include "AABB.hpp"

#include <limits>

namespace space::world {

    AABB::AABB(Vector min, Vector max)
        : _min {min}, _max {max}, _model {std::make_unique<Object>(create_model(min, max))} {
    }

    bool AABB::collides_with(const AABB& other) const {
        return false; // TODO
    }

    void AABB::move(const Vector& v) {
        _min += v;
        _max += v;
    }

    AABB AABB::from_object(const Object& object) {
        float float_min = std::numeric_limits<float>::min();
        float float_max = std::numeric_limits<float>::min();

        Vector min {float_max, float_max, float_max};
        Vector max {float_min, float_min, float_min};

        for (const Polygon& surface : object.surfaces()) {
            for (const Vector& point : surface.points()) {
                if (point.x < min.x)
                    min.x = point.x;

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