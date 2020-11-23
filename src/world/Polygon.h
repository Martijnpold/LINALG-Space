#pragma once

#include "Vector.hpp"

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
    };

}
