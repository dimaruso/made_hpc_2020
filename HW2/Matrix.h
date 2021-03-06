#pragma once
#include <vector>
#include <stdexcept>

class Matrix
{
public:
	Matrix(const size_t& _rows, const size_t& _cols, const int& default_value = 0);
	~Matrix();
	class Row;
	const size_t getRows() const;
	const size_t getColumns() const;

	const Row& operator[](const size_t& i) const;
	Row& operator[](const size_t& i);

	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;

	Matrix& operator=(const Matrix& m);

	Matrix operator*(const Matrix& m) const;
	Matrix operator*(const int& k) const;
	Matrix operator*=(const int& k);

private:
	size_t rows;
	size_t cols;
	std::vector<Row> data;
};

class Matrix::Row 
{
public:
	Row(size_t _cols, const int& default_value = 0):
		data(std::vector<int>(_cols, default_value))
	{
	}
	~Row()
	{
	}
	const int& operator[](const size_t& i) const
	{
		if (i < data.size()) 
			return data[i];
		else
			throw std::out_of_range("wrong column index");
	}
	int& operator[](const size_t& i) 
	{
		if (i < data.size()) 
			return data[i];
		else
			throw std::out_of_range("wrong column index");
	}
private:
	std::vector<int> data;
};
