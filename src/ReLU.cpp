#include "ReLU.h"

Matrix ReLU::forward(const Matrix& input)
{
    m_input_cache = input;

    Matrix result(input.rows(), input.cols());

    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] > 0.0f)
            result[i] = input[i];
    }

    return result;
}

Matrix ReLU::backward(const Matrix& output_grad, float learning_rate)
{
    (void)learning_rate;

    Matrix grad_input(output_grad.rows(), output_grad.cols());

    for (size_t i = 0; i < output_grad.size(); i++) {
        if (m_input_cache[i] > 0.0f)
            grad_input[i] = output_grad[i];
    }

    return grad_input;
}
