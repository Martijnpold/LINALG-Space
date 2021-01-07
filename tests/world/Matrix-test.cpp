#include "math/Matrix.hpp"

#include <catch.hpp>

using namespace space::world;

TEST_CASE("Matrix data access & construction", "[Matrix]") {

    SECTION("Default Matrices are filled with '0' as the value") {
        Matrix m {2, 2};
        REQUIRE(m(0, 0) == 0);
        REQUIRE(m(1, 0) == 0);
        REQUIRE(m(0, 1) == 0);
        REQUIRE(m(1, 1) == 0);
    }

    SECTION("Matrices can be created from a list of values") {
        Matrix m {2, 2, {1, 2, 3, 4}};
        REQUIRE(m(0, 0) == 1);
        REQUIRE(m(1, 0) == 2);
        REQUIRE(m(0, 1) == 3);
        REQUIRE(m(1, 1) == 4);
    }

    SECTION("Matrices can be filled from a list of values") {
        Matrix m {2, 2};
        m.fill({1, 2, 3, 4});
        REQUIRE(m(0, 0) == 1);
        REQUIRE(m(1, 0) == 2);
        REQUIRE(m(0, 1) == 3);
        REQUIRE(m(1, 1) == 4);
    }

    SECTION("Matrix values can be set by coordinate") {
        float value = 3;
        Matrix m {2, 2};
        m.set(0, 0, value);
        REQUIRE(m(0, 0) == value);
    }
}

TEST_CASE("Matrix arithmetic", "[Matrix]") {

    SECTION("Adding same-sized matrices") {
        Matrix m1 {2, 2, {2, 2, 2, 2}};
        Matrix m2 {2, 2, {1, 1, 1, 1}};
        Matrix r = m1 + m2;
        REQUIRE(r(0, 0) == 3);
        REQUIRE(r(1, 0) == 3);
        REQUIRE(r(0, 1) == 3);
        REQUIRE(r(1, 1) == 3);
    }

    SECTION("Subtracting same-sized matrices") {
        Matrix m1 {2, 2, {2, 2, 2, 2}};
        Matrix m2 {2, 2, {1, 1, 1, 1}};
        Matrix r = m1 - m2;
        REQUIRE(r(0, 0) == 1);
        REQUIRE(r(1, 0) == 1);
        REQUIRE(r(0, 1) == 1);
        REQUIRE(r(1, 1) == 1);
    }

    SECTION("Multiplying properly sized matrices") {
        Matrix m1 {3, 2, {1, 1, 1, 1, 1, 1}};
        Matrix m2 {2, 3, {1, 1, 1, 1, 1, 1}};
        Matrix r = m1 * m2;

        REQUIRE(r.height() == m1.height());
        REQUIRE(r.width() == m2.width());

        REQUIRE(r(0, 0) == (m1(0, 0) * m2(0, 0) + m1(1, 0) * m2(0, 1) + m1(2, 0) * m2(0, 2)));
        REQUIRE(r(1, 0) == (m1(0, 0) * m2(1, 0) + m1(1, 0) * m2(1, 1) + m1(2, 0) * m2(1, 2)));
        REQUIRE(r(0, 1) == (m1(0, 1) * m2(0, 0) + m1(1, 1) * m2(0, 1) + m1(2, 1) * m2(0, 2)));
        REQUIRE(r(1, 1) == (m1(0, 1) * m2(1, 0) + m1(1, 1) * m2(1, 1) + m1(2, 1) * m2(1, 2)));
    }

    SECTION("Multiplying properly sized Matrix with a Vector") {
        Matrix m {4, 4};
        m.set(0, 0, 3);
        m.set(1, 1, 2);
        m.set(2, 2, -2);
        m.set(3, 3, 1);

        Vector v {3, -1, 3};

        Vector r = m * v;

        REQUIRE(r.x == 9);
        REQUIRE(r.y == -2);
        REQUIRE(r.z == -6);
    }
}

TEST_CASE("Utility Matrix construction") {

    SECTION("Scaling matrix") {
        float xScale {2};
        float yScale {4};
        float zScale {6};
        Matrix m = Matrix::createScalingMatrix(xScale, yScale, zScale);

        SECTION("is properly sized to be multiplied with a Vector") {
            REQUIRE(m.width() == 4);
            REQUIRE(m.height() == 4);
        }

        SECTION("contains scaling values in the correct positions") {
            REQUIRE(m(0, 0) == xScale);
            REQUIRE(m(1, 1) == yScale);
            REQUIRE(m(2, 2) == zScale);
            REQUIRE(m(3, 3) == 1);
        }

        SECTION("contains 0 in all other positions") {
            REQUIRE(m(1, 0) == 0);
            REQUIRE(m(2, 0) == 0);
            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(0, 1) == 0);
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(0, 2) == 0);
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(0, 3) == 0);
            REQUIRE(m(1, 3) == 0);
            REQUIRE(m(2, 3) == 0);
        }
    }

    SECTION("Translation matrix") {
        float xTranslation {2};
        float yTranslation {4};
        float zTranslation {6};
        Matrix m = Matrix::createTranslationMatrix(xTranslation, yTranslation, zTranslation);

        SECTION("is properly sized to be multiplied with a Vector") {
            REQUIRE(m.width() == 4);
            REQUIRE(m.height() == 4);
        }

        SECTION("contains translation values in the correct positions") {
            REQUIRE(m(3, 0) == xTranslation);
            REQUIRE(m(3, 1) == yTranslation);
            REQUIRE(m(3, 2) == zTranslation);
            REQUIRE(m(0, 0) == 1);
            REQUIRE(m(1, 1) == 1);
            REQUIRE(m(2, 2) == 1);
            REQUIRE(m(3, 3) == 1);
        }

        SECTION("contains 0 in all other positions") {
            REQUIRE(m(1, 0) == 0);
            REQUIRE(m(2, 0) == 0);
            REQUIRE(m(0, 1) == 0);
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(0, 2) == 0);
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(0, 3) == 0);
            REQUIRE(m(1, 3) == 0);
            REQUIRE(m(2, 3) == 0);
        }
    }

    SECTION("X rotation matrix") {
        float a = 5;
        Matrix m = Matrix::createRotationMatrixX(a);

        SECTION("is properly sized to be multiplied with a Vector") {
            REQUIRE(m.width() == 4);
            REQUIRE(m.height() == 4);
        }

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(1, 1) == std::cos(a));
            REQUIRE(m(2, 1) == -std::sin(a));
            REQUIRE(m(1, 2) == std::sin(a));
            REQUIRE(m(2, 2) == std::cos(a));

            REQUIRE(m(0, 0) == 1);
            REQUIRE(m(3, 3) == 1);
        }

        SECTION("contains 0 in all other positions") {
            REQUIRE(m(1, 0) == 0);
            REQUIRE(m(2, 0) == 0);
            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(0, 1) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(0, 2) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(0, 3) == 0);
            REQUIRE(m(1, 3) == 0);
            REQUIRE(m(2, 3) == 0);
        }
    }

    SECTION("Y rotation matrix") {
        float a = 5;
        Matrix m = Matrix::createRotationMatrixY(a);

        SECTION("is properly sized to be multiplied with a Vector") {
            REQUIRE(m.width() == 4);
            REQUIRE(m.height() == 4);
        }

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(0, 0) == std::cos(a));
            REQUIRE(m(2, 0) == std::sin(a));
            REQUIRE(m(0, 2) == -std::sin(a));
            REQUIRE(m(2, 2) == std::cos(a));

            REQUIRE(m(1, 1) == 1);
            REQUIRE(m(3, 3) == 1);
        }

        SECTION("contains 0 in all other positions") {
            REQUIRE(m(1, 0) == 0);
            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(0, 1) == 0);
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(0, 3) == 0);
            REQUIRE(m(1, 3) == 0);
            REQUIRE(m(2, 3) == 0);
        }
    }

    SECTION("Z rotation matrix") {
        float a = 5;
        Matrix m = Matrix::createRotationMatrixZ(a);

        SECTION("is properly sized to be multiplied with a Vector") {
            REQUIRE(m.width() == 4);
            REQUIRE(m.height() == 4);
        }

        SECTION("contains rotation values in the correct positions") {
            REQUIRE(m(0, 0) == std::cos(a));
            REQUIRE(m(1, 0) == -std::sin(a));
            REQUIRE(m(0, 1) == std::sin(a));
            REQUIRE(m(1, 1) == std::cos(a));

            REQUIRE(m(2, 2) == 1);
            REQUIRE(m(3, 3) == 1);
        }

        SECTION("contains 0 in all other positions") {
            REQUIRE(m(2, 0) == 0);
            REQUIRE(m(3, 0) == 0);
            REQUIRE(m(2, 1) == 0);
            REQUIRE(m(3, 1) == 0);
            REQUIRE(m(0, 2) == 0);
            REQUIRE(m(1, 2) == 0);
            REQUIRE(m(3, 2) == 0);
            REQUIRE(m(0, 3) == 0);
            REQUIRE(m(1, 3) == 0);
            REQUIRE(m(2, 3) == 0);
        }
    }

    SECTION("Vector rotation matrix") {
//        Vector v {1, 2, 3};
//        float a = 4;
//        Matrix m = Matrix::createRotationMatrixVec(a);
//
//        SECTION("is properly sized to be multiplied with a Vector") {
//            REQUIRE(m.width() == 4);
//            REQUIRE(m.height() == 4);
//        }
    }
}