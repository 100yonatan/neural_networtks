#include "MSELoss.h"
#include <stdexcept>

float MSELoss::forward(const Matrix& predictions, const Matrix& targets)
{
    if (predictions.rows() != targets.rows() || predictions.cols() != targets.cols())
        throw std::invalid_argument("Matrix dimensions must match!");

    const size_t total_elements = predictions.size();
    if (total_elements == 0)
        return 0.0f;

    float sum = 0.0f;

    for (size_t i = 0; i < total_elements; i++) {
        float diff = predictions[i] - targets[i];
        sum += diff * diff;
    }

    return sum / predictions.size();
}

Matrix MSELoss::backward(const Matrix& predictions, const Matrix& targets)
{
    if (predictions.rows() != targets.rows() || predictions.cols() != targets.cols())
        throw std::invalid_argument("Matrix dimensions must match!");

    const size_t total_elements = predictions.size();
    Matrix grad_loss(predictions.rows(), predictions.cols());

    if (total_elements == 0)
        return grad_loss;

    float factor = 2.0f / static_cast<float>(total_elements);

    for (size_t i = 0; i < total_elements; i++) {
        grad_loss[i] = factor * (predictions[i] - targets[i]);
    }

    return grad_loss;
}
