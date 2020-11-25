#pragma once

#include <ostream>

namespace space::world {
    class Vector {
    public:
        float x, y, z;

        Vector();
        Vector(float x, float y, float z);

        Vector operator+(const Vector& v) const;
        Vector operator-(const Vector& v) const;
        Vector operator*(float f) const;
        friend Vector operator*(float i, const Vector& v);

        [[nodiscard]] std::string to_string() const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Vector& v);
    };
} // namespace space::world