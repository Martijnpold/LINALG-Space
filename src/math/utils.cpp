#include "utils.hpp"

#include <cmath>

namespace space::math {
    float toRadians(double deg) {
        return ( float ) (deg * (M_PI / 180.0));
    }
} // namespace space::math