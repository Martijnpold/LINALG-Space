#include "Polygon.h"

#include <utility>

namespace space::world {

    Polygon::Polygon(bool isOpenEnded) : _isOpenEnded {isOpenEnded} {
    }

    Polygon::Polygon(std::vector<Vector> points, bool isOpenEnded)
        : _points {std::move(points)}, _isOpenEnded {isOpenEnded} {
    }

    void Polygon::add(const Vector& point) {
        _points.push_back(point);
    }

    bool Polygon::isOpenEnded() const {
        return _isOpenEnded;
    }

    const std::vector<Vector>& Polygon::points() const {
        return _points;
    }

    std::vector<Vector>& Polygon::points() {
        return _points;
    }

} // namespace space::world
