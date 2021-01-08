#pragma once

#include "Object.hpp"
#include "OrbitingCamera.hpp"
#include "Polygon.hpp"
#include "math/Vector.hpp"
#include "sdl/SDLWrapper.hpp"
#include "world/World.hpp"

#include <vector>

namespace space::world {

    class Renderer {
    private:
        std::shared_ptr<sdl::SDLWrapper> _renderer;

        bool _show_coordinate_system {true};
        bool _show_hitboxes {false};

    public:
        explicit Renderer(std::shared_ptr<sdl::SDLWrapper> renderer);

        void render_world(const OrbitingCamera& camera, World& world);
        void render_object(const OrbitingCamera& camera, const Vector& location, const Object& object, const sdl::Color& color = {0, 0, 255});

        void show_hitboxes(bool value = true);
        void toggle_hitboxes();
        void show_coordinate_system(bool value = true);
        void toggle_coordinate_system();

    private:
        void render_coordinate_system(const OrbitingCamera& camera, float size);

        void render_line(const OrbitingCamera& camera, const Vector& from, const Vector& to, const sdl::Color& color);
    };

} // namespace space::world
