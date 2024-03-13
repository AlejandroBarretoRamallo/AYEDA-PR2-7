#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Sequence.h"
#include "DispersionFunction.h"
#include "ExplorationFunction.h"

template <class key, class Container = staticSequence<key> >

class HashTable {
  public:
    HashTable(unsigned,DispersionFunction<key>&, ExplorationFunction<key>&,unsigned);
    bool search(const key&)const;
    bool insert(const key&)const; // hacer
    bool isFull()const;
  private:
    unsigned tableSize_;
    DispersionFunction<key>& fd_;
    ExplorationFunction<key>& fe_;
    unsigned blockSize_;
    Container* table_;
};

template <class key>

class HashTable <key> {
  public:
    HashTable(unsigned, DispersionFunction<key>&);
    bool search(const key&)const;
    bool insert(const key&)const; // hacer
    bool isFull()const;
  private:
    dynamicSequence<key>* table_;
    unsigned tableSize_;
    DispersionFunction<key> fd_;
};

#endif