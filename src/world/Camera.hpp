#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
namespace space::world {
    class Camera {
    private:
        Vector _lookat {0, 0, 0};
        Vector _location {0, 0, 10};

        Vector _direction;
        Vector _up;
        Vector _right;

        float _fov {90};
        float _near {0.1};
        float _far {1000};
        float scale() const;

    public:
        Camera();

        Vector direction() const;
        Vector directionRight() const;
        Vector directionUp() const;

        Matrix createTranslationMatrix() const;
        Matrix createOriginTranslationMatrix() const;

        Matrix createProjectionMatrix() const;

        void move(const Vector& v);
        void rotate(const Vector& v);

    private:
        void update_directions();
    };
} // namespace space::world