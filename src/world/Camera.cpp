#include "Camera.hpp"

#include <cmath>

namespace space::world {
    Vector Camera::direction() const {
        return (_location - _lookat).normalize();
    }

    Vector Camera::directionRight() const {
        Vector up {0, 1, 0};
        return up.cross(direction()).normalize();
    }

    Vector Camera::directionUp() const {
        return direction().cross(directionRight()).normalize();
    }

    Matrix Camera::createTranslationMatrix() const {
        Vector d {direction()};
        Vector r {directionRight()};
        Vector u {directionUp()};
        return Matrix(4, 4, {r.x, r.y, r.z, 0, u.x, u.y, u.z, 0, d.x, d.y, d.z, 0, 0, 0, 0, 1});
    }

    Matrix Camera::createOriginTranslationMatrix() const {
        return createTranslationMatrix() * Matrix::createTranslationMatrix(_location * -1);
    }

    float Camera::scale() const {
        return _near * std::tan(_fov * 0.5f);
    }

    Matrix Camera::createProjectionMatrix() const {
        float scl = scale();
        return Matrix(4, 4,
                      {scl, 0, 0, 0, 0, scl, 0, 0, 0, 0, -_far / (_far - _near), -1, 0, 0,
                       (-_far * _near) / (_far - _near), 0});
    }
} // namespace space::world