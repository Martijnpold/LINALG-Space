#pragma once

#include "world/Matrix.hpp"

using namespace space::world;

namespace space::util {
    class VectorRotationUtil {
    public:
        static Matrix rotateM1(const Vector& rotationVec, float angle);
        static Matrix rotateM2(const Vector& rotationVec, float angle);
        static Matrix rotateM3(const Vector& rotationVec, float angle);
        static Matrix rotateM4(const Vector& rotationVec, float angle);
        static Matrix rotateM5(const Vector& rotationVec, float angle);
    };
} // namespace space::util