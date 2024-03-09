#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) 
{
	this->r = r;
	this->root = -1;
	this->size_bst = 0;
	this->capacity = 10;  
	this->bst = new Node[capacity];
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int SortedIndexedList::size() const
{
	return size_bst;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool SortedIndexedList::isEmpty() const 
{
	return (this->size_bst == 0);
}

//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
TComp SortedIndexedList::getElement(int pos) const
{
	if (pos < 0 || pos >= this->size_bst) 
	{
		throw exception();
	}

	int current = root;
	while (current != -1) 
	{
		int left_size = bst[current].nr_left;
		if (left_size == pos)
			return bst[current].info;

		if (left_size > pos)
			current = bst[current].left;
		else
		{
			current = bst[current].right;
			pos -= left_size + 1;
		}
	}
	return NULL_TCOMP;
}

//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
TComp SortedIndexedList::remove(int pos) {
	if (pos < 0 || pos >= size_bst) {
		throw exception();
	}

	int prev = -1;
	int current = root;
	int position = 0;
	while (current != -1) {
		if (pos == (position + bst[current].nr_left)) {
			break;
		}
		if (pos < (position + bst[current].nr_left)) {
			prev = current;
			current = bst[current].left;
		}
		else {
			prev = current;
			position += bst[current].nr_left + 1;
			current = bst[current].right;
		}
	}

	TComp deleted = bst[current].info;
	if (bst[current].left == -1 && bst[current].right == -1) {
		decrease(pos);
		if (prev == -1) {
			root = -1;
		}
		else {
			if (r(bst[current].info, bst[prev].info)) {
				bst[prev].left = -1;
			}
			else {
				bst[prev].right = -1;
			}
		}
		this->size_bst--;
	}
	else {
		if (bst[current].left == -1 || bst[current].right == -1) {
			decrease(pos);

			int descendant;
			if (bst[current].left == -1) {
				descendant = bst[current].right;
			}
			else {
				descendant = bst[current].left;
			}

			if (prev == -1) {
				root = descendant;
			}
			else {
				if (r(bst[current].info, bst[prev].info)) {
					bst[prev].left = descendant;
				}
				else {
					bst[prev].right = descendant;
				}
			}
			this->size_bst--;
		}
		else {
			TComp n_successor = successor(bst[current].info);
			int index = search(n_successor);
			remove(index);
			bst[current].info = n_successor;
		}
	}

	return deleted;
}

//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
int SortedIndexedList::search(TComp e) const 
{
	int current = root;
	int position = 0;

	while (current != -1) {
		if (bst[current].info == e) {
			return (position + bst[current].nr_left);
		}
		if (r(e, bst[current].info)) {
			current = bst[current].left;
		}
		else {
			position += bst[current].nr_left + 1;
			current = bst[current].right;
		}
	}

	return -1;
}



//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
void SortedIndexedList::add(TComp e)
{
	if (size_bst == capacity)
	{
		capacity *= 2;
		Node* newBst = new Node[capacity];
		for (int i = 0; i < size_bst; i++) {
			newBst[i] = bst[i];
		}
		delete[] bst;
		bst = newBst;
	}

	Node newNode;
	newNode.info = e;
	newNode.left = -1;
	newNode.right = -1;
	newNode.nr_left = 0;

	if (root == -1) {
		root = 0;
		bst[root] = newNode;
	}
	else {
		int current = root;
		while (true) {
			if (r(e, bst[current].info)) {
				bst[current].nr_left++;
				if (bst[current].left == -1) {
					bst[current].left = size_bst;
					bst[size_bst] = newNode;
					break;
				}
				else {
					current = bst[current].left;
				}
			}
			else {
				if (bst[current].right == -1) {
					bst[current].right = size_bst;
					bst[size_bst] = newNode;
					break;
				}
				else {
					current = bst[current].right;
				}
			}
		}
	}
	size_bst++;
}


//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
TComp SortedIndexedList::successor(TComp e) {
	int current = root;
	while (bst[current].info != e) {
		if (r(e, bst[current].info)) {
			current = bst[current].left;
		}
		else {
			current = bst[current].right;
		}
	}

	if (bst[current].right != -1) {
		current = bst[current].right;
		while (bst[current].left != -1) {
			current = bst[current].left;
		}
		return bst[current].info;
	}
	else {
		int p = get_parent(bst[current].info);
		int parent = root;

		while (bst[parent].info != p) {
			if (r(p, bst[parent].info)) {
				parent = bst[parent].left;
			}
			else {
				parent = bst[parent].right;
			}
		}

		while (parent != -1 && bst[parent].left != current) {
			current = parent;
			int n_p = get_parent(bst[current].info);
			int n_parent = root;

			while (bst[n_parent].info != n_p) {
				if (r(n_p, bst[n_parent].info)) {
					n_parent = bst[n_parent].left;
				}
				else {
					n_parent = bst[n_parent].right;
				}
			}

			parent = n_parent;
		}
		return bst[parent].info;
	}
}


//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
void SortedIndexedList::decrease(int pos) {
	if (pos >= size_bst || pos < 0) {
		throw std::exception();
	}

	int current = root;
	int position = 0;
	while (current != -1) {
		if (pos == (position + bst[current].nr_left)) {
			return;
		}
		if (pos < (position + bst[current].nr_left)) {
			bst[current].nr_left--;
			current = bst[current].left;
		}
		else {
			position += bst[current].nr_left + 1;
			current = bst[current].right;
		}
	}
}


//BC: Theta(1)
//WC: O(H), where H is the height of the BST
//Total: O(H)
TComp SortedIndexedList::get_parent(TComp e) {
	if (root == -1 || bst[root].info == e) {
		return -1;
	}

	int current = root;
	int parent = -1;

	while (current != -1 && bst[current].info != e) {
		parent = current;

		if (r(bst[current].info, e)) {
			current = bst[current].left;
		}
		else {
			current = bst[current].right;
		}
	}

	if (current == -1) {
		throw std::exception();
	}

	return bst[parent].info;
}



ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}



//destructor
SortedIndexedList::~SortedIndexedList() 
{
	while (!this->isEmpty()) {
		this->remove(0);
	}
}
