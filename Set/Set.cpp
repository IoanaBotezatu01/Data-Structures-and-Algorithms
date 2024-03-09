#include "Set.h"
#include "SetITerator.h"

Set::Set() 
{
	 this->firstElement= NULL_TELEM;
	 this->nrElements = 0;
	 this->setElements = new TElem[1];

}


bool Set::add(TElem elem) 
{
	if (search(elem) == true)//if the element is already in the set,return false
		return false;
	if (isEmpty())//if there is no element yet
	{
		this->firstElement = elem;//the added elemnt becomes the first element
		this->nrElements = 1;
		this->setElements[0] = true;//setElements[0] will always be true
	}

	if (elem < this->firstElement)
	{
		int difference = this->firstElement - elem, i;
		int* array = new TElem[this->nrElements];
		for (i = 0; i < this->nrElements; i++)
			array[i] = this->setElements[i];//copy the set into a new array so we can modify the values for the numbers smaller than the first element
		this->firstElement = elem;
		this->nrElements = this->nrElements + difference;
		delete[] this->setElements;
		this->setElements = new TElem[this->nrElements];
		this->setElements[0] = true;//the first element is always true
		for (i = 1; i < difference; i++)
			this->setElements[i] = false;//all the elements between the new "firstElem"and the old one will be false
		for (i = difference; i < this->nrElements; i++)
			this->setElements[i] = array[i - difference];
		delete[] array;
	}
	else if (elem < this->firstElement + this->nrElements - 1)//if the element is in range (the number of elements doesn't modify)
		this->setElements[elem - this->firstElement] = true;
	else//if the element we want to add is greater than any from the set
	{
		int oldSize = this->nrElements, i;
		int* array = new TElem[this->nrElements];
		for (i = 0; i < this->nrElements; i++)
			array[i] = this->setElements[i];//copy the set so we can modify it later
		this->nrElements = elem - this->firstElement + 1;//the number of elements is the difference between the smaller and the greatest number
		delete[] this->setElements;
		this->setElements = new TElem[this->nrElements];
		for (i = 0; i < oldSize; i++)
			this->setElements[i] = array[i];
		for (i = oldSize; i < this->nrElements; i++)
			this->setElements[i] = false;
		this->setElements[this->nrElements-1] = true;
		delete[] array;

	}
	return true;//returns true if the element is added 

}


bool Set::remove(TElem elem)
{
	 if (search(elem) == false)//if the element is not in set,it can't be deleted
		return false;
	/*if (elem == this->firstElement)
	 {
		 int i;
		 int* array = new TElem[this->nrElements];
		 for (i = 0; i < this->nrElements; i++)
			 array[i] = this->setElements[i];//copy the set into the array
		 this->firstElement = this->firstElement + 1;
		 this->nrElements = this->nrElements - 1;
		 delete[] this->setElements;
		 this->setElements = new TElem[this->nrElements];
		 for (i = 0; i < this->nrElements; i++)
			 this->setElements[i] = array[i + 1];
		 delete[] array;
	 }
	*/
	 /*if (elem = this->setElements[this->nrElements - 1])//if it's the last element
	 {
		 this->setElements[this->nrElements - 1] = false;
		 while (this->setElements[this->nrElements - 1] == false)
		 {
			 this->nrElements--;
		 }
	 }
	 else
	 */
		 this->setElements[elem - this->firstElement] = false;
	 return true;
}

bool Set::search(TElem elem) const 
{
	if (elem < this->firstElement)//if is smaller than the first element
		return false;
	if (elem > this->firstElement + this->nrElements - 1)//if is greater than all the elements
		return false;
	return  this->setElements[elem - this->firstElement];//return true or false depending on the value of the element in the set
}


int Set::size() const 
{
	int nrElem = 0, i;
	for (i = 0; i <= this->nrElements;i++)
		if (this->setElements[i]==true)
			nrElem++;
	return nrElem;
}


bool Set::isEmpty() const 
{
	return size() == 0;
}


Set::~Set() 
{
	delete[] this->setElements;
}


SetIterator Set::iterator() const 
{
	return SetIterator(*this);
}


