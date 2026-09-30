#pragma once
#include "Layer.h"
class ReLU : public Layer
{
private:
    Matrix m_input_cache;

public:
    ReLU() : m_input_cache(0, 0) {}

    Matrix forward(const Matrix& input) override;
    Matrix backward(const Matrix& output_grad, float learning_rate) override;
};