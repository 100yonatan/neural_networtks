#pragma once

#include "Layer.h"
#include "Matrix.h"
#include <vector>
#include <memory>


class Sequential
{
private:
	std::vector<std::unique_ptr<Layer>> m_layers;
public:
	Sequential() = default;
	~Sequential() = default;
	Sequential(const Sequential&) = delete;
	Sequential& operator=(const Sequential&) = delete;

	void add(std::unique_ptr<Layer> layer);
	Matrix forward(const Matrix& input);
	void backward(const Matrix& loss_grad, float learning_rate);
};

