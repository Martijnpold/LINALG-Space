#include "Vector.hpp"

namespace space::world {
    Vector::Vector(float vx, float vy) : x {vx}, y {vy} {
    }

    Vector::Vector() : Vector(0, 0) {
    }

    Vector Vector::operator+(const Vector& v) const {
        return Vector {x + v.x, y + v.y};
    }

    Vector Vector::operator-(const Vector& v) const {
        return Vector {x - v.x, y - v.y};
    }

    Vector Vector::operator*(float f) const {
        return Vector {x * f, y * f};
    }

    std::string Vector::to_string() const {
        return "Vector{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }

    std::ostream& operator<<(std::ostream& strm, const Vector& v) {
        return strm << v.to_string();
    }

    Vector operator*(float i, const Vector& v) {
        return v * i;
    }
} // namespace space::world