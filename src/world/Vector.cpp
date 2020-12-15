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

    Vector& Vector::operator*=(float f) {
        this->x *= f;
        this->y *= f;
        this->z *= f;
        return *this;
    }

    Vector Vector::operator*(float f) const {
        return Vector {x * f, y * f, z * f};
    }

    Vector operator*(float i, const Vector& v) {
        return v * i;
    }

    float Vector::length() const {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    float Vector::dot(const Vector& v) const {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    Vector Vector::cross(const Vector& v) const {
        return Vector {
                (y * v.z) - (z * v.y),
                (z * v.x) - (x * v.z),
                (x * v.y) - (y * v.x),
        };
    }

    std::string Vector::to_string() const {
        return "Vector(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    std::ostream& operator<<(std::ostream& strm, const Vector& v) {
        return strm << v.to_string();
    }
} // namespace space::world