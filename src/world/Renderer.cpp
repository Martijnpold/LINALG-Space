#include "Renderer.hpp"

#include <iostream>

namespace space::world {
    using namespace sdl;

    Renderer::Renderer(std::shared_ptr<SDLWrapper> renderer) : _renderer {std::move(renderer)} {
    }


    void Renderer::show_coordinate_system(bool value) {
        _show_coordinate_system = value;
    }

    void Renderer::toggle_coordinate_system() {
        _show_coordinate_system = !_show_coordinate_system;
    }

    void Renderer::show_hitboxes(bool value) {
        _show_hitboxes = value;
    }

    void Renderer::toggle_hitboxes() {
        _show_hitboxes = !_show_hitboxes;
    }

    void Renderer::render_world(const OrbitingCamera& camera, World& world) {

        if (_show_coordinate_system) {
            render_coordinate_system(camera, 100);
        }

        for (const auto& entity : world.entities()) {
            render_object(camera, entity->model(), Color {255, 0, 255});

            if (_show_hitboxes) {
                render_object(camera, entity->hitbox().model(), Color {0, 255, 255});
            }
        }
    }

    void Renderer::render_coordinate_system(const OrbitingCamera& camera, float size) {
        float segment_size = 1;
        int segments = size / segment_size;

        Color x_color {255, 0, 0};
        Color y_color {0, 255, 0};
        Color z_color {0, 0, 255};

        Vector x {1, 0, 0};
        Vector y {0, 1, 0};
        Vector z {0, 0, 1};

        for (int i = 0; i < segments; ++i) {
            float start = i * segment_size;
            float end = (i + 1) * segment_size;

            render_line(camera, x * start, x * end, x_color);
            render_line(camera, x * -start, x * -end, x_color);

            render_line(camera, y * start, y * end, y_color);
            render_line(camera, y * -start, y * -end, y_color);

            render_line(camera, z * start, z * end, z_color);
            render_line(camera, z * -start, z * -end, z_color);
        }
    }

    void Renderer::render_grid(const Color& c, float gridSize) {
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

    void Renderer::render_object(const OrbitingCamera& camera, const Object& object, const Color& color) {
        for (const auto& polygon : object.surfaces()) {
            for (int i = 0; i < polygon.points().size(); i++) {
                Vector from {polygon.points()[i]};
                Vector to {polygon.points()[(i + 1) % polygon.points().size()]};

                render_line(camera, from, to, color);
            }
        }
    }

    void Renderer::render_line(const OrbitingCamera& camera, const Vector& from, const Vector& to, const Color& color) {
        Matrix projection {camera.createProjectionMatrix() * camera.createOriginTranslationMatrix()};
        float screenW {( float ) _renderer->getWidth()};
        float screenH {( float ) _renderer->getHeight()};

        _renderer->setColor(color);

        Vector a = projection * from;
        Vector b = projection * to;

        if (a.w <= 0 || b.w <= 0)
            return;

        float xFrom = screenW / 2 + (a.x / a.w) * (screenW / 2);
        float yFrom = screenH / 2 + (a.y / a.w) * (screenH / 2);
        float xTo = screenW / 2 + (b.x / b.w) * (screenW / 2);
        float yTo = screenH / 2 + (b.y / b.w) * (screenH / 2);

        _renderer->drawLine(xFrom, ( screenH ) -yFrom, xTo, ( screenH ) -yTo);
    }

} // namespace space::world