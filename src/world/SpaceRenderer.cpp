#include "SpaceRenderer.hpp"

namespace space::world {
    SpaceRenderer::SpaceRenderer(std::shared_ptr<sdl::SDLWrapper> renderer) : _renderer{std::move(renderer)} {
    }

    void SpaceRenderer::renderVector(const Vector &v, float gridSize) {

    }

    void SpaceRenderer::renderGrid(float gridSize) {

    }
}