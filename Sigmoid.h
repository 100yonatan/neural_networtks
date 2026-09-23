#pragma once
#include "Layer.h"
class Sigmoid : public Layer
{
private:
	Matrix m_output_cache;

public:
	Sigmoid() : m_output_cache(0,0) {}

	Matrix forward(const Matrix& input) override;
	Matrix backward(const Matrix& output_grad, float learning_rate) override;
};

