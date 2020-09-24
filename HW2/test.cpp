#include <iostream>
#include <cassert>
#include "Matrix.h"

using std::cout;

void test_init()
{
	const size_t rows = 2;
	const size_t cols = 3;

	Matrix m(rows, cols);
	assert(m.getRows() == 2);
	assert(m.getColumns() == 3);

	m[0][0] = 0;
	m[0][1] = 1;
	m[0][2] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	m[1][2] = 5;

	assert(m[0][0] == 0);
	assert(m[1][0] == 3);
	assert(m[1][2] == 5);

	Matrix m2(0, 0);
	m2 = m;
	assert(m2[1][0] == 3);
	assert(m2 == m);

	m[1][0] *= 3;
	assert(m[1][0] == 9);
	assert(m2[1][0] == 3);
	
	m2[1][0] += 2;
	assert(m2[1][0] == 5);
	assert(m[1][0] == 9);

	assert(m2 != m);
	
	m = m * 10; 
	assert(m[1][0] == 90);
	
	m2 *= 2;
	assert(m2[1][0] == 10);
	return;
}

void test_multiply()
{
	const int size = 2;
	Matrix a(size, size);
	Matrix b(size, size);
	Matrix c(size, size);

	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	
	b[0][0] = 5;
	b[0][1] = 6;
	b[1][0] = 7;
	b[1][1] = 8;

	c[0][0] = 19;
	c[0][1] = 22;
	c[1][0] = 43;
	c[1][1] = 50;

	auto d = a * b;

	// 1 | 2     5 | 6    19 | 22
	// -----  *  -----  = -------
	// 3 | 4     5 | 6    43 | 50

	assert(c == d);

	Matrix vector(size, 1);
	Matrix vector_res(size, 1);

	vector[0][0] = 1;
	vector[1][0] = 2;

	vector_res[0][0] = 5;
	vector_res[1][0] = 11;
	
	auto vector_calc = a * vector;

	// 1 | 2     1      5
	// -----  *  -  =  --
	// 3 | 4     2     11

	assert(vector_calc == vector_res);
	return;
}

int main(int argc, char* argv[]) 
{
	test_init();
	test_multiply();
	cout << "Tests completed successfully!\n";
	return 0;
}
