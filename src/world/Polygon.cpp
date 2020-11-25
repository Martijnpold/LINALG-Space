#include "Polygon.hpp"

#include <algorithm>
#include <numeric>
#include <utility>

namespace space::world {

    Polygon::Polygon(bool isOpenEnded) : _isOpenEnded {isOpenEnded} {
    }

    Polygon::Polygon(std::vector<Vector> points, bool isOpenEnded)
        : _points {std::move(points)}, _isOpenEnded {isOpenEnded} {
    }


    Vector Polygon::center() const {
        float xSum =
                std::accumulate(_points.begin(), _points.end(), 0.0f, [](float s, const auto& v) { return s + v.x; });
        float ySum =
                std::accumulate(_points.begin(), _points.end(), 0.0f, [](float s, const auto& v) { return s + v.y; });
        float zSum =
                std::accumulate(_points.begin(), _points.end(), 0.0f, [](float s, const auto& v) { return s + v.z; });
        float size = _points.size();
        return Vector {xSum / size, ySum / size, zSum / size};
    }

    void Polygon::translate(float x, float y, float z) {
        Matrix transform = Matrix::createTranslationMatrix(x, y, z);
        std::transform(_points.begin(), _points.end(), _points.begin(),
                       [&transform](const auto& p) { return transform * p; });
    }

    void Polygon::scale(float factor) {
        scale(factor, factor, factor);
    }

    void Polygon::scale(float factor, const Vector& center) {
        scale(factor, factor, factor, center);
    }

    void Polygon::scale(float xFactor, float yFactor, float zFactor) {
        Vector c = center();
        scale(xFactor, yFactor, zFactor, c);
    }

    void Polygon::scale(float xFactor, float yFactor, float zFactor, const Vector& c) {
        Matrix t1 = Matrix::createTranslationMatrix(-c.x, -c.y, -c.z);
        Matrix s = Matrix::createScalingMatrix(xFactor, yFactor, zFactor);
        Matrix t2 = Matrix::createTranslationMatrix(c.x, c.y, c.z);
        Matrix transform = t2 * (s * t1);

        std::transform(_points.begin(), _points.end(), _points.begin(),
                       [&transform](const auto& p) { return transform * p; });
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

    void Polygon::rotateZ(float angle) {
        rotateZ(angle, center());
    }

    void Polygon::rotateZ(float angle, const Vector& c) {
        Matrix t1 = Matrix::createTranslationMatrix(-c.x, -c.y, -c.z);
        Matrix s = Matrix::createRotationMatrixZ(angle);
        Matrix t2 = Matrix::createTranslationMatrix(c.x, c.y, c.z);
        Matrix transform = t2 * (s * t1);

        std::transform(_points.begin(), _points.end(), _points.begin(),
                       [&transform](const auto& p) { return transform * p; });
    }
} // namespace space::world
