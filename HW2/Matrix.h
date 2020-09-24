#pragma once
#include <vector>

class Matrix
{
public:
	Matrix(size_t _rows, size_t _cols);
	~Matrix();
	class Row;
	const size_t getRows() const;
	const size_t getColumns() const;

	const Row& operator[](size_t i) const;
	Row& operator[](size_t i);

	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;

	Matrix& operator=(const Matrix& m);

	Matrix operator*(const int k) const;
    Matrix operator*(const Matrix& m) const;
	Matrix operator*=(const int k);

private:
	size_t rows;
	size_t cols;
	std::vector<Row> data;
};

class Matrix::Row {

public:
	Row(size_t _cols)
	{
		data.resize(_cols);
		for (size_t i = 0; i < _cols; ++i)
			data[i] = 0;
	}
	~Row()
	{
	}
	const int& operator[](const int i) const
	{
		if (i < data.size()) return data[i];
		else
			throw std::out_of_range("wrong column index");
	}
	int& operator[](const int i) 
	{
		if (i < data.size()) return data[i];
		else
			throw std::out_of_range("wrong column index");
	}
private:
	std::vector<int> data;
};
