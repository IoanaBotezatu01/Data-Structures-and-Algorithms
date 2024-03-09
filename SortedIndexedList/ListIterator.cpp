#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->currentPosition = 0;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void ListIterator::first(){
	this->currentPosition = 0;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void ListIterator::next(){
	if (!this->valid()) {
		throw exception();
	}

	this->currentPosition++;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool ListIterator::valid() const
{
	return (this->currentPosition < list.size());
}

//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
TComp ListIterator::getCurrent() const{
	if (!this->valid()) {
		throw exception();
	}
	return list.getElement(this->currentPosition);
}

TPosition ListIterator::lastIndexOf(TElem elem) const {
	TPosition lastIndex = -1;

	for (int i = list.size() - 1; i >= 0; i--) {
		if (list.getElement(i) == elem) {
			lastIndex = i;
			break;
		}
	}

	return lastIndex;
}
