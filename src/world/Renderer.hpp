#pragma once

#include "Object.hpp"
#include "OrbitingCamera.hpp"
#include "Polygon.hpp"
#include "math/Vector.hpp"
#include "sdl/SDLWrapper.hpp"

#include <vector>

namespace space::world {

    // TODO: clean up and add render(World&)
    class Renderer {
    private:
        std::shared_ptr<sdl::SDLWrapper> _renderer;

    public:
        explicit Renderer(std::shared_ptr<sdl::SDLWrapper> renderer);

        void renderVector(const Vector& v, const sdl::Color& c, float gridSize);

        void renderGrid(const sdl::Color& c, float gridSize);
        void renderLine(const Vector& from, const Vector& to, const sdl::Color& c, float gridSize);
        void renderPolygon(const Polygon& polygon, const sdl::Color& c, float gridSize);
        void renderObject(const OrbitingCamera& camera, const Object& object, const sdl::Color& color = {0, 0, 255});
    };

} // namespace space::world
