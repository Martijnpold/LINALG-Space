#pragma once

#include <ostream>

namespace space::world {
    class Vector {
    public:
        float x, y;

        Vector();

        Vector(float x, float y);

        Vector operator+(const Vector &v) const;

        Vector operator-(const Vector &v) const;

        Vector operator*(float f) const;

        [[nodiscard]] std::string to_string() const;

        friend std::ostream &operator<<(std::ostream &outputStream, const Vector &p);
    };
}