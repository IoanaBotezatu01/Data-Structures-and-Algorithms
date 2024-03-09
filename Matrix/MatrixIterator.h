#pragma once
#include "Matrix.h";
class MatrixIterator
{
	friend class Matrix;
private:
	const Matrix& matrix;
	MatrixIterator(const Matrix& m);

	
	int firstElement;
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid();
};

