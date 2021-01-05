#include "Camera.hpp"

#include <cmath>

// TODO: probably clean this up?
float deg_to_rad(float deg) {
    return deg * (M_PI / 180);
}

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
        return _near * std::tan(deg_to_rad(_fov) * 0.5f);
    }

    Matrix Camera::createProjectionMatrix() const {
        float scl = scale();
        return Matrix(4, 4,
                      {scl, 0, 0, 0, 0, scl, 0, 0, 0, 0, -_far / (_far - _near), -1, 0, 0,
                       (-_far * _near) / (_far - _near), 0});
    }

    void Camera::move(const Vector& v) {
        //        Vector lookAtDiff {_location - _lookat};

        //        Vector dRight {directionRight()};
        //        _location *= (dRight * v.x);
        //        Vector dUp {directionUp()};
        //        _location *= (dUp * v.y);
        //        Vector dForward {direction()};
        //        _location *= (dForward * v.z);

        Matrix translate {createTranslationMatrix()};
        Vector move {translate * v};
        _location += move;
        _lookat += move;
    }

    void Camera::rotate(const Vector& v) {
        Matrix rotationX {Matrix::createRotationMatrixVec(directionRight(), v.x)};
        Matrix rotationY {Matrix::createRotationMatrixVec(directionUp(), v.y)};
        Matrix rotationZ {Matrix::createRotationMatrixVec(direction(), v.z)};
        Matrix transform = rotationX * rotationY * rotationZ;
        _location = transform * _location;
        _lookat = transform * _lookat;
    }
} // namespace space::world