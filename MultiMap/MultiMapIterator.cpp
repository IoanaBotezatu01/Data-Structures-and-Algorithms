#include "MultiMapIterator.h"


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) 
{
   
    this->key_index = this->col.keys.head;
    this->value_index = this->col.keys.nodes[this->key_index].info.second;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
TElem MultiMapIterator::getCurrent() const 
{
   
    if (!this->valid()) 
    {
        throw exception();
    }
    return pair<TKey, TValue>(this->col.keys.nodes[this->key_index].info.first,
        this->col.keys.nodes[this->key_index].info.second);
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
bool MultiMapIterator::valid() const {
    
    if (this->key_index == -1) {
        return false;
    }
    if (this->value_index == -1) {
        return false;
    }
    return true;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void MultiMapIterator::next() {
 
    if (this->valid() == 0) {
        throw exception();
    }
    this->value_index = this->col.keys.nodes[this->key_index].info.second;
    if (this->value_index == -1) {
        this->key_index = this->col.keys.nodes[this->key_index].next;
        this->value_index = this->col.keys.nodes[this->key_index].info.second;
    }
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
void MultiMapIterator::first() {
   
    this->key_index = this->col.keys.head;
    this->value_index = this->col.keys.nodes[key_index].info.second;
}
