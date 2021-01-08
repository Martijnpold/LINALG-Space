#include "Color.hpp"

namespace space::sdl {

    Color::Color() : Color(0, 0, 0) {
    }

    Color::Color(int rc, int gc, int bc) : r {rc}, g {gc}, b {bc} {
    }

} // namespace space::sdl