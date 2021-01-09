#pragma once

#include "math/Matrix.hpp"
#include "math/Vector.hpp"

using namespace space::math;

namespace space::world {

    class OrbitingCamera {
    private:
        Vector _location;
        Vector _lookat;

        Vector _direction;
        Vector _up;
        Vector _right;

        float _fov;
        float _near;
        float _far;

    public:
        OrbitingCamera(const Vector& location, const Vector& lookat, float fov = 60, float near = 0.1, float far = 100);

        Vector direction() const;
        Vector directionRight() const;
        Vector directionUp() const;

        Matrix createTranslationMatrix() const;
        Matrix createInverseTranslationMatrix() const;
        Matrix createOriginTranslationMatrix() const;

        Matrix createProjectionMatrix() const;

        void zoom(float zoom);
        void move(const Vector& v);
        void moveGlobal(const Vector& v);
        void rotate(const Vector& v);

    private:
        float scale() const;
        void update_directions();
    };

} // namespace space::world