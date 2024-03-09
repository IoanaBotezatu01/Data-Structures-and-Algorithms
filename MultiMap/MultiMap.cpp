#include "MultiMap.h"
#include "MultiMapIterator.h"

MultiMap::MultiMap() 
{
    number_of_pairs = 0;
}

template<typename TElement>
void MultiMap::resize(DLLA<TElement>& dlla) {
    // Resize the dynamic array if needed
    // This implementation is omitted for brevity
}

void MultiMap::add(TKey c, TValue v) {
    vector<TValue> values = search(c);
    if (!values.empty()) {
        // Key already exists, do not add the pair
        return;
    }

    if (number_of_pairs == keys.capacity - 1) {
        resize(keys);
    }

    int newPairPosition = keys.firstFree;
    keys.firstFree = keys.nodes[newPairPosition].next;

    keys.nodes[newPairPosition].info.first = c;
    keys.nodes[newPairPosition].info.second = NULL;

    keys.nodes[newPairPosition].prev = keys.tail;
    keys.nodes[newPairPosition].next = -1;

    if (keys.head == -1 && keys.tail == -1) {
        keys.head = newPairPosition;
        keys.tail = newPairPosition;
    }
    else {
        keys.nodes[keys.tail].next = newPairPosition;
        keys.nodes[newPairPosition].prev = keys.tail;
        keys.tail = newPairPosition;
    }

    number_of_pairs++;
}

bool MultiMap::remove(TKey c, TValue v) {
    vector<TValue> values = search(c);
    if (values.empty()) {
        // Key does not exist, nothing to remove
        return false;
    }

    int position = keys.head;
    while (position != -1) {
        if (keys.nodes[position].info.first == c) {
            if (keys.nodes[position].info.second == v) {
                // Key-value pair found, remove it
                if (position == keys.head) {
                    keys.head = keys.nodes[position].next;
                }
                if (position == keys.tail) {
                    keys.tail = keys.nodes[position].prev;
                }
                if (keys.nodes[position].prev != -1) {
                    keys.nodes[keys.nodes[position].prev].next = keys.nodes[position].next;
                }
                if (keys.nodes[position].next != -1) {
                    keys.nodes[keys.nodes[position].next].prev = keys.nodes[position].prev;
                }

                keys.nodes[position].next = keys.firstFree;
                keys.firstFree = position;
                number_of_pairs--;
                return true;
            }
        }
        position = keys.nodes[position].next;
    }

    // Key-value pair not found
    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> values;
    int currentPair = keys.head;
    while (currentPair != -1) {
        if (keys.nodes[currentPair].info.first == c) {
            const vector<TValue>& pairValues = keys.nodes[currentPair].info.second;
            values.insert(values.end(), pairValues.begin(), pairValues.end());
        }
        currentPair = keys.nodes[currentPair].next;
    }
    return values;
}

int MultiMap::size() const {
    return number_of_pairs;
}

bool MultiMap::isEmpty() const {
    return (number_of_pairs == 0);
}

MultiMap::~MultiMap() {
    delete[] keys.nodes;
}
