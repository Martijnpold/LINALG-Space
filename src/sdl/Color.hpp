#pragma once

namespace space::sdl {
    class Color {
    public:
        int r, g, b;

        Color();

        Color(int rc, int bc, int gc);
    };
} // namespace space::sdl