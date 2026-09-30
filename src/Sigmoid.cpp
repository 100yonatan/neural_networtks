#include "Sigmoid.h"
#include <cmath>

Matrix Sigmoid::forward(const Matrix& input)
{
    m_output_cache = Matrix(input.rows(), input.cols());

    for (size_t i = 0; i < input.size(); i++) {
        float x = input[i];
        if (x > 15.0f)
            x = 15.0f;
        if (x < -15.0f)
            x = -15.0f;

        m_output_cache[i] = 1.0f / (1.0f + std::exp(-x));
    }
    return m_output_cache;
}

Matrix Sigmoid::backward(const Matrix& output_grad, float learning_rate)
{
    (void)learning_rate;

    Matrix grad_input(output_grad.rows(), output_grad.cols());

    for (size_t i = 0; i < output_grad.size(); i++) {
        float s = m_output_cache[i];
        float deriv = s * (1.0f - s);
        grad_input[i] = output_grad[i] * deriv;
    }

    return grad_input;
}
