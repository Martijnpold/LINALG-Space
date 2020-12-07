#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

#include <vector>

namespace space::world {
    class Polygon {
    private:
        std::vector<Vector> _points;

    public:
        explicit Polygon() = default;
        explicit Polygon(std::vector<Vector> points);

        Polygon operator*(const Matrix& matrix) const;
        Polygon& operator*=(const Matrix& matrix);

        void add(const Vector& point);
        [[nodiscard]] const std::vector<Vector>& points() const;
        [[nodiscard]] std::vector<Vector>& points();

        [[nodiscard]] Vector center() const;
        void translate(float x, float y, float z);

        void scale(float factor);
        void scale(float xFactor, float yFactor, float zFactor);
        void scale(float xFactor, float yFactor, float zFactor, const Vector& center);
        void scale(float factor, const Vector& center);

        void rotateX(float angle);
        void rotateX(float angle, const Vector& c);
        void rotateY(float angle);
        void rotateY(float angle, const Vector& c);
        void rotateZ(float angle);
        void rotateZ(float angle, const Vector& c);
    };
} // namespace space::world
