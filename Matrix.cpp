#include "Matrix.h"
#include <stdexcept>


float& Matrix::operator()(size_t r, size_t c)
{
	if (r >= m_rows || c >= m_cols) {
		throw std::out_of_range("Matrix index out of bounds!");
	}

	return m_data[(r * m_cols) + c];
}

float Matrix::operator()(size_t r, size_t c) const
{
	if (r >= m_rows || c >= m_cols) {
		throw std::invalid_argument("Matrix index out of bounds!");
	}

	return m_data[(r * m_cols) + c];
}

Matrix Matrix::operator+(const Matrix& other) const
{
	if (other.m_rows != this->m_rows || other.m_cols != this->m_cols)
		throw  std::invalid_argument("Matrix dimensions must match for addition!");
	Matrix result(m_rows, m_cols);
	for (size_t i = 0; i < m_rows * m_cols; i++)
	{
		result.m_data[i] = this->m_data[i] + other.m_data[i];
	}

	return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	if (this->m_cols != other.m_rows)
		throw std::invalid_argument("Matrix dimensions must match for multiplication!");

	Matrix result(m_rows, other.m_cols);
	for (size_t i = 0; i < m_rows; i++)	{
		for (size_t j = 0; j < m_cols; j++){
			float sum = (*this)(i,j);
			for (size_t k = 0; k < other.m_cols; k++){
				result(i,k) += sum * other(j, k);
			}
		}
	}

	return result;
}

Matrix Matrix::transpose() const
{
	Matrix result(this->m_cols, this->m_rows);
	for (size_t i = 0; i < this->m_rows; i++) {
		for (size_t j = 0; j < this->m_cols; j++){
			result(j, i) = (*this)(i, j);
		}
	}

	return result;
}
