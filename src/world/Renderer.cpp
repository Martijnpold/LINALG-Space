#include "Renderer.hpp"

#include <iostream>

namespace space::world {
    Renderer::Renderer(std::shared_ptr<sdl::SDLWrapper> renderer) : _renderer {std::move(renderer)} {
    }


    void Renderer::show_grid(bool value) {
        _render_grid = value;
    }

    void Renderer::toggle_grid() {
        _render_grid = !_render_grid;
    }

    void Renderer::show_hitboxes(bool value) {
        _render_hitboxes = value;
    }

    void Renderer::toggle_hitboxes() {
        _render_hitboxes = !_render_hitboxes;
    }

    void Renderer::render_world(const OrbitingCamera& camera, World& world) {

        if (_render_grid) {
            render_grid({51, 51, 51}, 25);
        }

        for (const auto& entity : world.entities()) {
            render_object(camera, entity->model());

            if (_render_hitboxes) {
                render_object(camera, entity->hitbox().model(), {255, 0, 0});
            }
        }
    }

    void Renderer::render_grid(const sdl::Color& c, float gridSize) {
        _renderer->setColor(c);
        float width = _renderer->getWidth();
        float height = _renderer->getHeight();
        int rows = width / gridSize;
        int columns = height / gridSize;
        for (int x = 0; x <= rows / 2; x += 1) {
            for (int y = 0; y <= columns / 2; y += 1) {
                _renderer->drawLine(width / 2 + x * gridSize, 0, width / 2 + x * gridSize, height);
                _renderer->drawLine(width / 2 - x * gridSize, 0, width / 2 - x * gridSize, height);
                _renderer->drawLine(0, height / 2 + y * gridSize, width, height / 2 + y * gridSize);
                _renderer->drawLine(0, height / 2 - y * gridSize, width, height / 2 - y * gridSize);
            }
        }
    }

    void Renderer::render_object(const OrbitingCamera& camera, const Object& object, const sdl::Color& color) {
        _renderer->setColor(color);

        Matrix projection {camera.createProjectionMatrix() * camera.createOriginTranslationMatrix()};
        float screenW {( float ) _renderer->getWidth()};
        float screenH {( float ) _renderer->getHeight()};

        for (const auto& polygon : object.surfaces()) {
            for (int i = 0; i < polygon.points().size(); i++) {
                Vector from {polygon.points()[i]};
                from = projection * from;
                Vector to {polygon.points()[(i + 1) % polygon.points().size()]};
                to = projection * to;

                if (from.w <= 0 || to.w <= 0)
                    continue;

                float xFrom = screenW / 2 + (from.x / from.w) * (screenW / 2);
                float yFrom = screenH / 2 + (from.y / from.w) * (screenH / 2);
                float xTo = screenW / 2 + (to.x / to.w) * (screenW / 2);
                float yTo = screenH / 2 + (to.y / to.w) * (screenH / 2);

                _renderer->drawLine(xFrom, ( screenH ) -yFrom, xTo, ( screenH ) -yTo);
            }
            //            spaceRenderer->renderPolygon(p, Color {0, 0, 255}, gridSize);
        }
    }
} // namespace space::world