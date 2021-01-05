#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
namespace space::world {
    class Camera {
    private:
        Vector _location {0, 0, 0};
        Vector _lookat {0, 0, 1};

        float _fov {90};
        float _near {0.1};
        float _far {100};
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
    };
} // namespace space::world