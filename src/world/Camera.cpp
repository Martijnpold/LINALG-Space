#include "Camera.hpp"

#include <cmath>
#include <iostream>

// TODO: probably clean this up?
float deg_to_rad(double deg) {
    return ( float ) (deg * (M_PI / 180.0));
}

namespace space::world {

    Camera::Camera() {
        _up = {0, 1, 0};
        update_directions();
    }

    void Camera::update_directions() {
        _direction = (_location - _lookat).normalize();
        _right = _up.cross(_direction).normalize(); // this works because '_up' has been initialised correctly
        _up = _direction.cross(_right).normalize();
    }

    Vector Camera::direction() const {
        return _direction;
    }

    Vector Camera::directionRight() const {
        return _right;
    }

    Vector Camera::directionUp() const {
        return _up;
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
        return _near * std::tan(deg_to_rad(_fov) * 0.5f);
    }

    Matrix Camera::createProjectionMatrix() const {
        float scl = scale();
        return Matrix(4, 4,
                      {scl, 0, 0, 0, 0, scl, 0, 0, 0, 0, -_far / (_far - _near), -1, 0, 0,
                       (-_far * _near) / (_far - _near), 0});
    }

    void Camera::move(const Vector& v) {
        Matrix translate {createTranslationMatrix()};
        Vector move {translate * v};
        _location += move;
        _lookat += move;

        update_directions();
    }

    void Camera::rotate(const Vector& v) {
        Matrix rotationX {Matrix::createRotationMatrixVec(directionRight(), v.x)};
        Matrix rotationY {Matrix::createRotationMatrixVec(directionUp(), v.y)};
        Matrix rotationZ {Matrix::createRotationMatrixVec(direction(), v.z)};
        Matrix transform = rotationX * rotationY * rotationZ;
        _location = transform * _location;
        update_directions();
    }
} // namespace space::world