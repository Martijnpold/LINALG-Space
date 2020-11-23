#pragma once

#include "Polygon.hpp"
#include "Vector.hpp"
#include "sdl/SDLWrapper.hpp"

#include <vector>

namespace space::world {
    class SpaceRenderer {
    private:
        std::shared_ptr<sdl::SDLWrapper> _renderer;

    public:
        explicit SpaceRenderer(std::shared_ptr<sdl::SDLWrapper> renderer);

        void renderVector(const Vector& v, const sdl::Color& c, float gridSize);

        void renderGrid(const sdl::Color& c, float gridSize);
        void renderLine(const Vector& from, const Vector& to, const sdl::Color& c, float gridSize);
        void renderPolygon(const Polygon& polygon, const sdl::Color& c, float gridSize);
    };
} // namespace space::world
