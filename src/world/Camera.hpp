#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
namespace space::world {
    class Camera {
    private:
        Vector _location;
        Vector _lookat;

        float _fov {90};
        float _near {10};
        float _far {200};
        float scale() const;

    public:
        Vector direction() const;
        Vector directionRight() const;
        Vector directionUp() const;

        Matrix createTranslationMatrix() const;
        Matrix createOriginTranslationMatrix() const;

        Matrix createProjectionMatrix() const;
    };
} // namespace space::world