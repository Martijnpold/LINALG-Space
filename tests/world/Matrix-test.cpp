#include "world/Matrix.hpp"

#include <catch.hpp>

using namespace space::world;

TEST_CASE("Matrix data access", "[Matrix]") {

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