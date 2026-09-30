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
	Matrix& operator=(const Matrix& other);

	Matrix(Matrix&& other) noexcept;
	Matrix& operator=(Matrix&& other) noexcept;

	float& operator()(size_t r, size_t c);
	float operator()(size_t r, size_t c) const;
	float& operator[](size_t index);
	const float& operator[](size_t index) const;
	float* data() { return m_data.data(); }
	const float* data() const { return m_data.data(); }

	Matrix operator+(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix transpose() const;

	size_t rows() const { return m_rows; }
	size_t cols() const { return m_cols; }
	size_t size() const { return m_rows * m_cols; }

	//void save(std::ofstream& out) const;
	//void load(std::ifstream& in);

	void add_bias(const Matrix& bias);
};