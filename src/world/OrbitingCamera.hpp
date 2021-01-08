#pragma once

#include "math/Matrix.hpp"
#include "math/Vector.hpp"

using namespace space::math;

namespace space::world {

    class OrbitingCamera {
    private:
        Vector _lookat {0, 0, 0};
        Vector _location {0, 0, 10};

        Vector _direction;
        Vector _up;
        Vector _right;

        float _fov {60};
        float _near {0.1};
        float _far {1000};
        float scale() const;

    public:
        OrbitingCamera();

        Vector direction() const;
        Vector directionRight() const;
        Vector directionUp() const;

        Matrix createTranslationMatrix() const;
        Matrix createInverseTranslationMatrix() const;
        Matrix createOriginTranslationMatrix() const;

        Matrix createProjectionMatrix() const;

        void zoom(float zoom);
        void move(const Vector& v);
        void rotate(const Vector& v);

    private:
        void update_directions();
    };

} // namespace space::world