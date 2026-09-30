#include <doctest/doctest.h>

#include <memory>

#include "Dense.h"
#include "MSELoss.h"
#include "Sequential.h"
#include "Sigmoid.h"

TEST_CASE("Sequential rejects null and empty use")
{
    Sequential model;
    CHECK_THROWS(model.forward(Matrix(1, 1)));
    CHECK_THROWS(model.add(nullptr));
}

TEST_CASE("Sequential learns 2-bit XOR")
{
    Matrix x(4, 2);
    Matrix y(4, 1);
    const float inputs[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const float targets[4] = {0, 1, 1, 0};
    for (size_t i = 0; i < 4; i++) {
        x(i, 0) = inputs[i][0];
        x(i, 1) = inputs[i][1];
        y(i, 0) = targets[i];
    }

    Sequential model;
    model.add(std::make_unique<Dense>(2, 8));
    model.add(std::make_unique<Sigmoid>());
    model.add(std::make_unique<Dense>(8, 1));
    model.add(std::make_unique<Sigmoid>());

    MSELoss criterion;
    const float initial_loss = criterion.forward(model.forward(x), y);

    for (int epoch = 0; epoch < 5000; epoch++) {
        Matrix pred = model.forward(x);
        model.backward(criterion.backward(pred, y), 1.0f);
    }

    Matrix pred = model.forward(x);
    CHECK(criterion.forward(pred, y) < initial_loss);
    for (size_t i = 0; i < 4; i++)
        CHECK((pred(i, 0) >= 0.5f) == (targets[i] == 1.0f));
}
