#include "Sequential.h"
#include <stdexcept>

void Sequential::add(std::unique_ptr<Layer> layer) {
	if (!layer) 
		throw std::invalid_argument("Cannot add a null layer to Sequential model!");

	m_layers.push_back(std::move(layer));
}

Matrix Sequential::forward(const Matrix& input) {
	if (m_layers.empty())
		throw std::runtime_error("Cannot run forward on an empty Sequential model!");

	Matrix current_result = input;

	for (auto& layer_ptr : m_layers) {
		if (layer_ptr != nullptr)
			current_result = layer_ptr->forward(current_result);
	}

	return current_result;
}

void Sequential::backward(const Matrix& loss_grad, float learning_rate) {
	if (m_layers.empty())
		throw std::runtime_error("Cannot run backward on an empty Sequential model!");

	Matrix current_grad = loss_grad;

	for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
		if (*it != nullptr) {
			current_grad = (*it)->backward(current_grad, learning_rate);
		}
	}
}