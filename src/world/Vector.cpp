#include "Vector.hpp"

#include <cmath>

namespace space::world {
    Vector::Vector(float vx, float vy, float vz) : x {vx}, y {vy}, z {vz} {
    }

    Vector::Vector() : Vector(0, 0, 0) {
    }

    Vector Vector::operator+(const Vector& v) const {
        return Vector {x + v.x, y + v.y, z + v.z};
    }

    Vector Vector::operator-(const Vector& v) const {
        return Vector {x - v.x, y - v.y, z - v.z};
    }

    Vector & Vector::operator*=(float f) {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
    }

    Vector Vector::operator*(float f) const {
        return Vector {x * f, y * f, z * f};
    }

    float Vector::length() const {
            return std::sqrt((x * x) + (y * y) + (z * z));
    }

    std::string Vector::to_string() const {
        return "Vector(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    std::ostream& operator<<(std::ostream& strm, const Vector& v) {
        return strm << v.to_string();
    }

    Vector operator*(float i, const Vector& v) {
        return v * i;
    }
} // namespace space::world