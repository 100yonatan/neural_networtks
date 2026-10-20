#pragma once

#include "nn/Matrix.h"
// #include "nn/Layer.h"

class MSELoss
{
public:
    float forward(const Matrix& predictions, const Matrix& targets);
    Matrix backward(const Matrix& predictions, const Matrix& targets);
};
