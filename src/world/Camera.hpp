#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
namespace space::world {
    class Camera {
    private:
        Vector _location;
        Vector _lookat;

        float _fov {50};
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
    };
} // namespace space::world