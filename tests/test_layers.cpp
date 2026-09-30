#include <doctest/doctest.h>

#include "Dense.h"
#include "MSELoss.h"
#include "ReLU.h"
#include "Sigmoid.h"

TEST_CASE("ReLU forward and backward")
{
    Matrix x(1, 3);
    x[0] = -1.0f;
    x[1] = 0.0f;
    x[2] = 2.0f;

    ReLU relu;
    Matrix y = relu.forward(x);
    CHECK(y[0] == 0.0f);
    CHECK(y[1] == 0.0f);
    CHECK(y[2] == 2.0f);

    Matrix grad = relu.backward(Matrix(1, 3, 1.0f), 0.0f);
    CHECK(grad[0] == 0.0f);
    CHECK(grad[1] == 0.0f);
    CHECK(grad[2] == 1.0f);
}

TEST_CASE("Sigmoid forward and backward")
{
    Sigmoid sigmoid;
    Matrix y = sigmoid.forward(Matrix(1, 1, 0.0f));
    CHECK(y[0] == doctest::Approx(0.5f));

    Matrix grad = sigmoid.backward(Matrix(1, 1, 1.0f), 0.0f);
    CHECK(grad[0] == doctest::Approx(0.25f));
}

TEST_CASE("Sigmoid clamps large inputs")
{
    Sigmoid sigmoid;
    Matrix x(1, 2);
    x[0] = 1000.0f;
    x[1] = -1000.0f;
    Matrix y = sigmoid.forward(x);
    CHECK(y[0] < 1.0f);
    CHECK(y[1] > 0.0f);
}

TEST_CASE("Dense output shape and bias gradient step")
{
    Dense dense(3, 2);
    Matrix y = dense.forward(Matrix(4, 3, 1.0f));
    CHECK(y.rows() == 4);
    CHECK(y.cols() == 2);

    Matrix grad_in = dense.backward(Matrix(4, 2, 1.0f), 0.1f);
    CHECK(grad_in.rows() == 4);
    CHECK(grad_in.cols() == 3);

    // Bias grad sums over 4 rows of 1.0 -> 4.0; step = 0.1 * 4.0
    for (size_t i = 0; i < dense.get_biases().size(); i++)
        CHECK(dense.get_biases()[i] == doctest::Approx(-0.4f));
}

TEST_CASE("MSELoss forward and backward")
{
    Matrix pred(1, 2);
    pred[0] = 1.0f;
    pred[1] = 3.0f;
    Matrix target(1, 2, 2.0f);

    MSELoss loss;
    CHECK(loss.forward(pred, target) == doctest::Approx(1.0f));

    Matrix grad = loss.backward(pred, target);
    CHECK(grad[0] == doctest::Approx(-1.0f));
    CHECK(grad[1] == doctest::Approx(1.0f));
}
