#include "SpaceRenderer.hpp"

namespace space::world {
    SpaceRenderer::SpaceRenderer(std::shared_ptr<sdl::SDLWrapper> renderer) : _renderer {std::move(renderer)} {
    }

    void SpaceRenderer::renderVector(const Vector& v, const sdl::Color& c, float gridSize) {
        _renderer->setColor(c);
        float width = _renderer->getWidth();
        float height = _renderer->getHeight();
        _renderer->drawLine(width / 2, height / 2, width / 2 + v.x * gridSize, height / 2 - v.y * gridSize);
    }

    void SpaceRenderer::renderLine(const Vector& from, const Vector& to, const sdl::Color& c, float gridSize) {
        _renderer->setColor(c);
        float width = _renderer->getWidth();
        float height = _renderer->getHeight();
        _renderer->drawLine(width / 2 + from.x * gridSize, height / 2 - from.y * gridSize, width / 2 + to.x * gridSize,
                            height / 2 - to.y * gridSize);

//        _renderer->drawLine(width / 2 + 175 + from.z * gridSize, height / 2 - from.y * gridSize,
//                            width / 2 + 175 + to.z * gridSize, height / 2 - to.y * gridSize);
//
//        _renderer->drawLine(width / 2 + from.x * gridSize, height / 2 + 175 - from.z * gridSize,
//                            width / 2 + to.x * gridSize, height / 2 + 175 - to.z * gridSize);
    }

    void SpaceRenderer::renderPolygon(const Polygon& polygon, const sdl::Color& c, float gridSize) {
        for (int i = 0; i < polygon.points().size(); i++) {
            renderLine(polygon.points()[i], polygon.points()[(i + 1) % polygon.points().size()], c, gridSize);
        }
    }

    void SpaceRenderer::renderGrid(const sdl::Color& c, float gridSize) {
        _renderer->setColor(c);
        float width = _renderer->getWidth();
        float height = _renderer->getHeight();
        int rows = width / gridSize;
        int columns = height / gridSize;
        for (int x = 0; x <= rows / 2; x += 1) {
            for (int y = 0; y <= columns / 2; y += 1) {
                if (x == 0 || y == 0) {
                    _renderer->setColor(150, 255, 150);
                } else {
                    _renderer->setColor(51, 51, 51);
                }

                _renderer->drawLine(width / 2 + x * gridSize, 0, width / 2 + x * gridSize, height);
                _renderer->drawLine(width / 2 - x * gridSize, 0, width / 2 - x * gridSize, height);
                _renderer->drawLine(0, height / 2 + y * gridSize, width, height / 2 + y * gridSize);
                _renderer->drawLine(0, height / 2 - y * gridSize, width, height / 2 - y * gridSize);
            }
        }
    }
} // namespace space::world