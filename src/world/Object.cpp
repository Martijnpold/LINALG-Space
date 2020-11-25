#include "Object.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>

namespace space::world {
    Object::Object(std::vector<Polygon> surfaces) : _surfaces {std::move(surfaces)} {
    }

    Object Object::operator*(const Matrix& matrix) const {
        std::vector<Polygon> surfaces {};
        std::transform(_surfaces.begin(), _surfaces.end(), std::back_inserter(surfaces), [&matrix](const auto& p) { return p * matrix; });
        return Object(surfaces);
    }

    void Object::multiply(const Matrix& matrix) {
        std::transform(_surfaces.begin(), _surfaces.end(), _surfaces.begin(),
                       [&matrix](const auto& p) { return p * matrix; });
    }

    Vector Object::center() const {
        Vector sum = std::accumulate(_surfaces.begin(), _surfaces.end(), Vector {},
                                     [](Vector s, const Polygon& v) { return s + v.center(); });
        float size = _surfaces.size();
        return Vector {sum.x / size, sum.y / size, sum.z / size};
    }

    void Object::translate(float x, float y, float z) {
        Matrix transform = Matrix::createTranslationMatrix(x, y, z);
        multiply(transform);
    }

    void Object::scale(float factor) {
        scale(factor, factor, factor);
    }

    void Object::scale(float factor, const Vector& center) {
        scale(factor, factor, factor, center);
    }

    void Object::scale(float xFactor, float yFactor, float zFactor) {
        Vector c = center();
        scale(xFactor, yFactor, zFactor, c);
    }

    void Object::scale(float xFactor, float yFactor, float zFactor, const Vector& c) {
        Matrix t1 = Matrix::createTranslationMatrix(-c.x, -c.y, -c.z);
        Matrix s = Matrix::createScalingMatrix(xFactor, yFactor, zFactor);
        Matrix t2 = Matrix::createTranslationMatrix(c.x, c.y, c.z);
        Matrix transform = t2 * (s * t1);
        std::cout << transform << std::endl;
        multiply(transform);
    }

    void Object::add(const Polygon& surface) {
        _surfaces.push_back(surface);
    }

    const std::vector<Polygon>& Object::surfaces() const {
        return _surfaces;
    }

    std::vector<Polygon>& Object::surfaces() {
        return _surfaces;
    }

    void Object::rotateZ(float angle) {
        rotateZ(angle, center());
    }

    void Object::rotateZ(float angle, const Vector& c) {
        Matrix t1 = Matrix::createTranslationMatrix(-c.x, -c.y, -c.z);
        Matrix s = Matrix::createRotationMatrixZ(angle);
        Matrix t2 = Matrix::createTranslationMatrix(c.x, c.y, c.z);
        Matrix transform = t2 * (s * t1);
        multiply(transform);
    }

    void Object::rotateX(float angle) {
        rotateX(angle, center());
    }

    void Object::rotateX(float angle, const Vector& c) {
        Matrix t1 = Matrix::createTranslationMatrix(-c.x, -c.y, -c.z);
        Matrix s = Matrix::createRotationMatrixX(angle);
        Matrix t2 = Matrix::createTranslationMatrix(c.x, c.y, c.z);
        Matrix transform = t2 * (s * t1);
        multiply(transform);
    }
} // namespace space::world
