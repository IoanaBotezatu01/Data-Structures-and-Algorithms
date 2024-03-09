#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->elems = this->set.setElements;
	this->firstElement = 0;
}


void SetIterator::first() 
{
	this->firstElement = 0;
}


void SetIterator::next() 
{
	do
	{
		this->firstElement++;
	} while (valid()==true && this->elems[this->firstElement] == false);	
}


TElem SetIterator::getCurrent()
{
	return this->set.firstElement + this->firstElement;
}

bool SetIterator::valid() const 
{
	if (this->set.size() == 0)
		return false;
	if (this->firstElement == this->set.nrElements)
		return false;
	return true;
}

void SetIterator::previous()
{
	if(this->firstElement>0)
	do {
		this->firstElement--;
	} while (valid_p() == true && this->elems[this->firstElement] == false);
	
}

bool SetIterator::valid_p() const
{
	if (this->set.size() == 0)
		return false;
	if (this->firstElement==0)
		return false;
	return true;
}



