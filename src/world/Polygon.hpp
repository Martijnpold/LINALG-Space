#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

#include <vector>

namespace space::world {

    class Polygon {
    private:
        std::vector<Vector> _points;
        bool _isOpenEnded;

    public:
        explicit Polygon(bool isOpenEnded = false);
        explicit Polygon(std::vector<Vector> points, bool isOpenEnded = false);

        void add(const Vector& point);
        [[nodiscard]] const std::vector<Vector>& points() const;
        [[nodiscard]] std::vector<Vector>& points();
        [[nodiscard]] bool isOpenEnded() const;

        [[nodiscard]] Vector center() const;
        void translate(float x, float y, float z);

        void scale(float factor);
        void scale(float xFactor, float yFactor, float zFactor);
        void scale(float xFactor, float yFactor, float zFactor, const Vector& center);
        void scale(float factor, const Vector& center);

        void rotateZ(float angle);
        void rotateZ(float angle, const Vector& c);
    };

}
