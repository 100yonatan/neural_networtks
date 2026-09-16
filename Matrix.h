#pragma once

#include <vector>

class Matrix
{
private:
	size_t m_rows;
	size_t m_cols;
	std::vector<float> m_data;
public:
	Matrix(size_t row, size_t col) : m_rows(row), m_cols(col), m_data(row * col, 0.0f) {}
	Matrix(size_t row, size_t col, float initialValue) : m_rows(row), m_cols(col), m_data(row* col, initialValue){}
	Matrix(const Matrix& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_data(other.m_data) {}

	float& operator()(size_t r, size_t c);
	float operator()(size_t r, size_t c) const;
	Matrix operator+(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix transpose() const;

	size_t rows() const { return m_rows; }
	size_t cols() const { return m_cols; }
};

