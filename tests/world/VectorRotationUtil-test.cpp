#include "util/VectorRotationUtil.hpp"

#include <catch.hpp>

using namespace space::util;

TEST_CASE("Vector rotation values", "[VectorRotationUtil]") {
    SECTION("Matrix M1") {
        Vector v {1, 2, 3};
        float angle {4};
        Matrix m = VectorRotationUtil::rotateM1(v, angle);

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(0, 0) == v.x / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(0, 1) == 0);
            REQUIRE(m(0, 2) == -v.z / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(0, 3) == 0);

            REQUIRE(m(1, 0) == 0);
            REQUIRE(m(1, 1) == 1);
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(1, 3) == 0);

            REQUIRE(m(2, 0) == v.z / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(2, 2) == v.x / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(2, 3) == 0);

            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(3, 3) == 1);
        }
    }

    SECTION("Matrix M2") {
        Vector v {1, 2, 3};
        float angle {4};
        Matrix m = VectorRotationUtil::rotateM2(v, angle);

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(0, 0) == std::sqrt(v.x * v.x + v.z * v.z) / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(0, 1) == -v.y / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(0, 2) == 0);
            REQUIRE(m(0, 3) == 0);

            REQUIRE(m(1, 0) == v.y / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(1, 1) == std::sqrt(v.x * v.x + v.z * v.z) / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(1, 3) == 0);

            REQUIRE(m(2, 0) == 0);
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(2, 2) == 1);
            REQUIRE(m(2, 3) == 0);

            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(3, 3) == 1);
        }
    }

    SECTION("Matrix M3") {
        Vector v {1, 2, 3};
        float angle {4};
        Matrix m = VectorRotationUtil::rotateM3(v, angle);

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m == Matrix::createRotationMatrixX(angle));
        }
    }

    SECTION("Matrix M4") {
        Vector v {1, 2, 3};
        float angle {4};
        Matrix m = VectorRotationUtil::rotateM4(v, angle);

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(0, 0) == std::sqrt(v.x * v.x + v.z * v.z) / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(0, 1) == v.y / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(0, 2) == 0);
            REQUIRE(m(0, 3) == 0);

            REQUIRE(m(1, 0) == -v.y / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(1, 1) == std::sqrt(v.x * v.x + v.z * v.z) / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(1, 3) == 0);

            REQUIRE(m(2, 0) == 0);
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(2, 2) == 1);
            REQUIRE(m(2, 3) == 0);

            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(3, 3) == 1);
        }
    }

    SECTION("Matrix M5") {
        Vector v {1, 2, 3};
        float angle {4};
        Matrix m = VectorRotationUtil::rotateM5(v, angle);

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(0, 0) == v.x / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(0, 1) == 0);
            REQUIRE(m(0, 2) == v.z / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(0, 3) == 0);

            REQUIRE(m(1, 0) == 0);
            REQUIRE(m(1, 1) == 1);
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(1, 3) == 0);

            REQUIRE(m(2, 0) == -v.z / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(2, 2) == v.x / std::sqrt((v.x * v.x) + (v.z * v.z)));
            REQUIRE(m(2, 3) == 0);

            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(3, 3) == 1);
        }
    }
}