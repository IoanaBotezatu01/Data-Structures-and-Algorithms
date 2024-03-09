
#include "MatrixIterator.h"

MatrixIterator::MatrixIterator(const Matrix& m) :matrix(m)
{
	this->firstElement = 0;
}

void MatrixIterator::first()
{
	this->firstElement = 0;
}

void MatrixIterator::next()
{
	//if (valid())
	this->firstElement++;
}

TElem MatrixIterator::getCurrent()
{
	return this->matrix.element(this->firstElement/matrix.nrColumns(),this->firstElement%matrix.nrColumns());
}

bool MatrixIterator::valid()
{
	if (this->firstElement / matrix.nrColumns() > matrix.nrLines())
		return false;
	if (this->firstElement == matrix.nrColumns() * matrix.nrLines()-1)
		return false;
	return true;

}
