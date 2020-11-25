#include "Polygon.hpp"

#include <algorithm>
#include <numeric>
#include <utility>

namespace space::world {
    Polygon::Polygon(std::vector<Vector> points) : _points {std::move(points)} {
    }

    Polygon Polygon::operator*(const Matrix& matrix) const {
        std::vector<Vector> points {};
        points.reserve(_points.size());
        std::transform(_points.begin(), _points.end(), std::back_inserter(points),
                       [&matrix](const Vector& v) { return matrix * v; });
        return Polygon(points);
    }

    void Polygon::multiply(const Matrix& matrix) {
        std::transform(_points.begin(), _points.end(), _points.begin(),
                       [&matrix](const Vector& v) { return matrix * v; });
    }

    Vector Polygon::center() const {
        Vector sum = std::accumulate(_points.begin(), _points.end(), Vector {},
                                     [](Vector s, const Vector& v) { return s + v; });
        float size = _points.size();
        return Vector {sum.x / size, sum.y / size, sum.z / size};
    }

    void Polygon::translate(float x, float y, float z) {
        Matrix transform = Matrix::createTranslationMatrix(x, y, z);
        multiply(transform);
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
        multiply(transform);
    }

    void Polygon::add(const Vector& point) {
        _points.push_back(point);
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
        multiply(transform);
    }
} // namespace space::world
