#pragma once

#include "nn/Layer.h"
#include "nn/Matrix.h"

class Dense : public Layer
{
private:
    Matrix m_weights;
    Matrix m_biases;
    Matrix m_input_cache;

public:
    Dense(size_t in_features, size_t out_features);
    Matrix forward(const Matrix& input) override;
    Matrix backward(const Matrix& output_grad, float learning_rate) override;

    const Matrix& get_weights() const { return m_weights; }
    const Matrix& get_biases() const { return m_biases; }
};