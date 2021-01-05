#pragma once

#include <ostream>

namespace space::world {
    class Vector {
    public:
        float x, y, z, w;

        Vector();
        Vector(float x, float y, float z);
        Vector(float x, float y, float z, float w);

        Vector operator*(const Vector& v) const;
        Vector& operator*=(const Vector& v);
        Vector operator+(const Vector& v) const;
        Vector& operator+=(const Vector& v);
        Vector operator-(const Vector& v) const;
        Vector& operator*=(float f);
        Vector operator*(float f) const;
        friend Vector operator*(float i, const Vector& v);

        float length() const;
        Vector& normalize();

        float dot(const Vector& v) const;
        Vector cross(const Vector& v) const;
        float angle(const Vector& v) const;

        [[nodiscard]] std::string to_string() const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Vector& v);
    };
} // namespace space::world