#pragma once



#include <vector>
#include <utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	template<typename TElem>
	struct DLLANode {
		pair<TKey,TValue> info;
		int next;
		int prev;
	};
	template <typename TElem>
	struct DLLA {
		DLLANode<TElem>* nodes;
		int capacity;
		int size;
		int firstFree;
		int head;
		int tail;

		DLLA() {
			capacity = 2;
			size = 0;
			first_free = 0;
			head = -1;
			tail = -1;
			nodes = new DLLANode<TElem>[capacity];
			for (int i = 0; i < capacity - 1; i++)
			{
				nodes[i].next = i + 1;
				nodes[i].prev = i - 1;
			}
			nodes[capacity - 1].next = -1;
			nodes[capacity - 1].prev = capacity - 2;
		}
		~DLLA() {
			if (nodes == nullptr)
				return;
			nodes = nullptr;
		}
	};
	DLLA<pair<TKey, DLLA<TValue>>>keys;
	int number_of_pairs;

public:
	//constructor
	MultiMap();

	template <typename TElem>
	void resize(DLLA<TElem>& dlla);

	//template<typename TElem,typename TVal>
	//void addToDLLA(DLLA<TElem>& dlla, TVal v);

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//template<typename TElem>
	//bool removeFromDLLA(DLLA<TElem>& dlla,int position);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//destructor
	~MultiMap();


};