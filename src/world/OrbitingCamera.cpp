#include "OrbitingCamera.hpp"

#include "math/utils.hpp"

namespace space::world {

    OrbitingCamera::OrbitingCamera(const Vector& location, const Vector& lookat, float fov, float near, float far)
        : _location {location}, _lookat {lookat}, _fov {fov}, _near {near}, _far {far} {
        _up = {0, 1, 0};
        update_directions();
    }

    void OrbitingCamera::update_directions() {
        _direction = (_location - _lookat).normalize();
        _right = _up.cross(_direction).normalize(); // this works because '_up' has been initialised correctly
        _up = _direction.cross(_right).normalize();
    }

    Vector OrbitingCamera::direction() const {
        return _direction;
    }

    Vector OrbitingCamera::directionRight() const {
        return _right;
    }

    Vector OrbitingCamera::directionUp() const {
        return _up;
    }

    Matrix OrbitingCamera::createTranslationMatrix() const {
        Vector d {direction()};
        Vector r {directionRight()};
        Vector u {directionUp()};
        return {4, 4, {r.x, u.x, d.x, 0, r.y, u.y, d.y, 0, r.z, u.z, d.z, 0, 0, 0, 0, 1}};
    }

    Matrix OrbitingCamera::createInverseTranslationMatrix() const {
        Vector d {direction()};
        Vector r {directionRight()};
        Vector u {directionUp()};
        return {4, 4, {r.x, r.y, r.z, 0, u.x, u.y, u.z, 0, d.x, d.y, d.z, 0, 0, 0, 0, 1}};
    }

    Matrix OrbitingCamera::createOriginTranslationMatrix() const {
        return createInverseTranslationMatrix() * Matrix::createTranslationMatrix(_location * -1);
    }

    float OrbitingCamera::scale() const {
        return _near * std::tan(math::toRadians(_fov) * 0.5f);
    }

    Matrix OrbitingCamera::createProjectionMatrix() const {
        float scl = scale();
        return Matrix(4, 4,
                      {scl, 0, 0, 0, 0, scl, 0, 0, 0, 0, -_far / (_far - _near), -1, 0, 0,
                       (-_far * _near) / (_far - _near), 0});
    }

    void OrbitingCamera::zoom(float zoom) {
        Matrix translate {createTranslationMatrix()};
        Vector move {translate * Vector {0, 0, zoom}};
        _location += move;
    }

    void OrbitingCamera::move(const Vector& v) {
        Matrix translate {createTranslationMatrix()};
        Vector move {translate * v};
        _location += move;
        _lookat += move;
        update_directions();
    }

    void OrbitingCamera::rotate(const Vector& v) {
        Matrix rotationX {Matrix::createRotationMatrixVec(directionRight(), v.x)};
        Matrix rotationY {Matrix::createRotationMatrixVec(directionUp(), v.y)};
        Matrix rotationZ {Matrix::createRotationMatrixVec(direction(), v.z)};
        Matrix transform = rotationX * rotationY * rotationZ;
        _location = transform * _location;
        update_directions();
    }
} // namespace space::world