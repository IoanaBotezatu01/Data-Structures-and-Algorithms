#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#include "MatrixIterator.h";

struct Node {
	int line;
	int col;
	TElem value;
	Node* next;
};
class Matrix {
	friend class MatrixIterator;
private:
	int lines;
	int cols;

	Node* list; /// a list of elements


	Node* insert_node(Node** node, int i, int j, TElem value);
	Node* search_node(Node* node, int i, int j) const;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);
	MatrixIterator iterator() const;

};
