#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);

	MatrixIterator it = m.iterator();
	it.first();
	int sum = 0;
	while (it.valid()==true)
	{
		it.next();
		if (it.getCurrent() != NULL_TELEM)
			sum += it.getCurrent();
		else
			sum -= 1;
	}
	assert(sum == -8);
}