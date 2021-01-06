#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
namespace space::world {
    class Camera {
    private:
        Vector _lookat {0, 0, 0};
        Vector _location {0, 0, 10};

        Vector _direction {0, 0, -1};
        Vector _up {0, 1, 0};
        Vector _right {1, 0, 0};

        float _fov {90};
        float _near {0.1};
        float _far {1000};
        float scale() const;

    public:
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