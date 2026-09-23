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

Matrix Matrix::operator=(const Matrix& other)
{
	if (this != &other) {
		Matrix temp(other);

		std::swap(m_rows, temp.m_rows);
		std::swap(m_cols, temp.m_cols);
		std::swap(m_data, temp.m_data);
	}
	return *this;
}

float& Matrix::operator[](size_t index) {
	if (index >= m_data.size())
		throw std::out_of_range("Matrix index out of bounds!");

	return m_data[index];
}

const float& Matrix::operator[](size_t index) const {
	if (index >= m_data.size())
		throw std::out_of_range("Matrix index out of bounds!");

	return m_data[index];
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

void Matrix::add_bias(const Matrix& bias) {
	if (bias.rows() != 1 || bias.cols() != this->m_cols)
		throw std::invalid_argument("bias must be 1 row and same coloms");
	for (size_t r = 0; r < m_rows; r++) {
		for (size_t c = 0; c < m_cols; c++) {
			(*this)(r, c) += bias(0, c);
		}
	}
}