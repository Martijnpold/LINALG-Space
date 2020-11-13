#include "Color.hpp"

namespace space::sdl {
    Color::Color() : Color(0, 0, 0) {
    }

    Color::Color(int rc, int bc, int gc) : r {rc}, b {bc}, g {gc} {
    }
} // namespace space::sdl