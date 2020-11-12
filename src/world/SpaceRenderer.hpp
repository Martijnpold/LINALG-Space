#pragma once

#include "sdl/SDLWrapper.hpp"
#include "Vector.hpp"

namespace space::world {
    class SpaceRenderer {
    private:
        std::shared_ptr<sdl::SDLWrapper> _renderer;

    public:
        explicit SpaceRenderer(std::shared_ptr<sdl::SDLWrapper> renderer);

        void renderVector(const Vector &v, float gridSize);

        void renderGrid(float gridSize);
    };
}
