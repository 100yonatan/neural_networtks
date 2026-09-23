#include "Dense.h"
#include <cmath>
#include <random>

Dense::Dense(size_t in_features, size_t out_features) :
	m_weights(in_features, out_features),
	m_biases(1, out_features, 0.0f),m_input_cache(0,0)
{
	float limit = std::sqrt(1.0f / static_cast<float>(in_features));
	std::mt19937 gen(1337);
	std::uniform_real_distribution<float> dist(-limit, limit);

	for (size_t r = 0; r < in_features; r++) {
		for (size_t c = 0; c < out_features; c++) {
			m_weights(r, c) = dist(gen);
		}
	}
}

Matrix Dense::forward(const Matrix& input)
{
	m_input_cache = input;
	Matrix result = input * m_weights;
	result.add_bias(m_biases);
	return result;
}

Matrix Dense::backward(const Matrix& output_grad, float learning_rate)
{
	return output_grad;
	(void)learning_rate;
}
