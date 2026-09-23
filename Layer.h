#pragma once

#include "Matrix.h"

class Layer
{
public:
	virtual Matrix forward(const Matrix& input) = 0;
	virtual Matrix backward(const Matrix& output_grad, float learning_rate) = 0;
	virtual ~Layer() = default;
};