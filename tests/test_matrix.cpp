#include <doctest/doctest.h>

#include <stdexcept>

#include "nn/Matrix.h"

TEST_CASE("Matrix initializes with fill value")
{
    Matrix m(2, 3, 1.5f);
    CHECK(m.rows() == 2);
    CHECK(m.cols() == 3);
    CHECK(m.size() == 6);
    for (size_t i = 0; i < m.size(); i++)
        CHECK(m[i] == 1.5f);
}

TEST_CASE("Matrix bounds checks throw")
{
    Matrix m(2, 2);
    CHECK_THROWS_AS(m(2, 0), std::out_of_range);
    CHECK_THROWS_AS(m[4], std::out_of_range);
}

TEST_CASE("Matrix addition")
{
    Matrix a(2, 2, 1.0f);
    Matrix b(2, 2, 2.0f);
    Matrix c = a + b;
    for (size_t i = 0; i < c.size(); i++)
        CHECK(c[i] == 3.0f);

    CHECK_THROWS_AS(a + Matrix(3, 2), std::invalid_argument);
}

TEST_CASE("Matrix multiplication")
{
    // [1 2 3]   [ 7  8]   [ 58  64]
    // [4 5 6] x [ 9 10] = [139 154]
    //           [11 12]
    Matrix a(2, 3);
    Matrix b(3, 2);
    for (size_t i = 0; i < a.size(); i++)
        a[i] = static_cast<float>(i + 1);
    for (size_t i = 0; i < b.size(); i++)
        b[i] = static_cast<float>(i + 7);

    Matrix c = a * b;
    REQUIRE(c.rows() == 2);
    REQUIRE(c.cols() == 2);
    CHECK(c(0, 0) == 58.0f);
    CHECK(c(0, 1) == 64.0f);
    CHECK(c(1, 0) == 139.0f);
    CHECK(c(1, 1) == 154.0f);

    CHECK_THROWS_AS(a * a, std::invalid_argument);
}

TEST_CASE("Matrix transpose")
{
    Matrix a(2, 3);
    for (size_t i = 0; i < a.size(); i++)
        a[i] = static_cast<float>(i);

    Matrix t = a.transpose();
    REQUIRE(t.rows() == 3);
    REQUIRE(t.cols() == 2);
    for (size_t r = 0; r < a.rows(); r++)
        for (size_t c = 0; c < a.cols(); c++)
            CHECK(t(c, r) == a(r, c));
}

TEST_CASE("Matrix add_bias broadcasts row")
{
    Matrix m(2, 2, 1.0f);
    Matrix bias(1, 2);
    bias(0, 0) = 10.0f;
    bias(0, 1) = 20.0f;

    m.add_bias(bias);
    CHECK(m(0, 0) == 11.0f);
    CHECK(m(1, 0) == 11.0f);
    CHECK(m(0, 1) == 21.0f);
    CHECK(m(1, 1) == 21.0f);

    CHECK_THROWS_AS(m.add_bias(Matrix(2, 2)), std::invalid_argument);
}

TEST_CASE("Matrix move leaves source empty")
{
    Matrix a(2, 2, 1.0f);
    Matrix b(std::move(a));
    CHECK(b.size() == 4);
    CHECK(a.rows() == 0);
    CHECK(a.cols() == 0);
}
