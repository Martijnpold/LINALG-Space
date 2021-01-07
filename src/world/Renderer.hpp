#pragma once

#include "Camera.hpp"
#include "Object.hpp"
#include "Polygon.hpp"
#include "math/Vector.hpp"
#include "sdl/SDLWrapper.hpp"

#include <vector>

namespace space::world {

    class Renderer {
    private:
        std::shared_ptr<sdl::SDLWrapper> _renderer;

    public:
        explicit Renderer(std::shared_ptr<sdl::SDLWrapper> renderer);

        void renderVector(const Vector& v, const sdl::Color& c, float gridSize);

        void renderGrid(const sdl::Color& c, float gridSize);
        void renderLine(const Vector& from, const Vector& to, const sdl::Color& c, float gridSize);
        void renderPolygon(const Polygon& polygon, const sdl::Color& c, float gridSize);
        void renderObject(const Camera& camera, const Object& object);
    };

} // namespace space::world
