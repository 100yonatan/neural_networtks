#pragma once

#include "Matrix.h"
//#include "Layer.h"


class MSELoss
{
public:
	float forward(const Matrix& predictions, const Matrix& targets);
	Matrix backward(const Matrix& predictions, const Matrix& targets);
};

