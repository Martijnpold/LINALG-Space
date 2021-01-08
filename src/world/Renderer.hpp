#pragma once

#include "Object.hpp"
#include "OrbitingCamera.hpp"
#include "Polygon.hpp"
#include "math/Vector.hpp"
#include "sdl/SDLWrapper.hpp"
#include "world/World.hpp"

#include <vector>

namespace space::world {

    // TODO: clean up and add render(World&)
    class Renderer {
    private:
        std::shared_ptr<sdl::SDLWrapper> _renderer;

        bool _render_grid {true};
        bool _render_hitboxes {false};

    public:
        explicit Renderer(std::shared_ptr<sdl::SDLWrapper> renderer);

        void render_world(const OrbitingCamera& camera, World& world);

        void show_hitboxes(bool value = true);
        void toggle_hitboxes();
        void show_grid(bool value = true);
        void toggle_grid();

    private:
        void render_grid(const sdl::Color& c, float gridSize);
        void render_object(const OrbitingCamera& camera, const Object& object, const sdl::Color& color = {0, 0, 255});
    };

} // namespace space::world
