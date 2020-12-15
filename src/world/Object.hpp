#pragma once

#include "Matrix.hpp"
#include "Polygon.hpp"
#include "Vector.hpp"

#include <vector>

namespace space::world {
    class Object {
    private:
        std::vector<Polygon> _surfaces;

    public:
        explicit Object() = default;
        explicit Object(std::vector<Polygon> surfaces);

        Object operator*(const Matrix& matrix) const;
        Object& operator*=(const Matrix& matrix);

        void add(const Polygon& surface);
        [[nodiscard]] const std::vector<Polygon>& surfaces() const;
        [[nodiscard]] std::vector<Polygon>& surfaces();

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
        void rotateVec(const Vector& vec, float angle);
        void rotateVec(const Vector& vec, float angle, const Vector& c);
    };
} // namespace space::world
