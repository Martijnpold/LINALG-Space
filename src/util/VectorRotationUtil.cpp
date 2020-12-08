#include "VectorRotationUtil.hpp"

#include <cmath>

namespace space::util {
    Matrix VectorRotationUtil::rotateM1(const Vector& rv, float angle) {
        float sqrtXZ {std::sqrt(rv.x * rv.x + rv.z + rv.z)};
        float xRot {rv.x / sqrtXZ};
        float zRot {rv.z / sqrtXZ};
        return {4, 4, {xRot, 0, zRot, 0, 0, 1, 0, 0, -zRot, 0, xRot, 0, 0, 0, 0, 1}};
    }

    Matrix VectorRotationUtil::rotateM2(const Vector& rv, float angle) {
        float sqrtXZ {std::sqrt(rv.x * rv.x + rv.z + rv.z)};
        float sqrtXYZ {std::sqrt(rv.x * rv.x + rv.y * rv.y + rv.z + rv.z)};
        float xzRot {sqrtXZ / sqrtXYZ};
        float yRot {rv.y / sqrtXYZ};
        return {4, 4, {xzRot, yRot, 0, 0, -yRot, xzRot, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
    }

    Matrix VectorRotationUtil::rotateM3(const Vector& rv, float angle) {
        return Matrix::createRotationMatrixX(angle);
    }

    Matrix VectorRotationUtil::rotateM4(const Vector& rv, float angle) {
        float sqrtXZ {std::sqrt(rv.x * rv.x + rv.z + rv.z)};
        float sqrtXYZ {std::sqrt(rv.x * rv.x + rv.y * rv.y + rv.z + rv.z)};
        float xzRot {sqrtXZ / sqrtXYZ};
        float yRot {rv.y / sqrtXYZ};
        return {4, 4, {xzRot, -yRot, 0, 0, yRot, xzRot, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
    }

    Matrix VectorRotationUtil::rotateM5(const Vector& rv, float angle) {
        float sqrtXZ {std::sqrt(rv.x * rv.x + rv.z + rv.z)};
        float xRot {rv.x / sqrtXZ};
        float zRot {rv.z / sqrtXZ};
        return {4, 4, {xRot, 0, -zRot, 0, 0, 1, 0, 0, zRot, 0, xRot, 0, 0, 0, 0, 1}};
    }
} // namespace space::util